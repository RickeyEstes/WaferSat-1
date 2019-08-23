/*
    Copyright (C) 2013-2015 Andrea Zoppi

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "hal_sdc.h"
#include "chprintf.h"
#include "chevents.h"
#include "string.h"
#include "hal_fsmc_sdram.h"
#include "log.h"
#include "ff.h"
#include "sd.h"

#define SD_POLLING_INTERVAL 10
#define SD_POLLING_DELAY 10
#define SD_TIMEOUT 500
//20 because this is greater than all FRESULT integers
#define SD_PARTIAL_WRITE 20

static FATFS SDC_FS;

bool sd_fs_ready = FALSE;
bool sd_block_ready = FALSE;
static int cnt = 0;
static virtual_timer_t tmr;

static void sd_insert_handler(eventid_t id) {
	FRESULT err;
	
	chprintf((BaseSequentialStream*) &SD1, "sd.c: SD card inserted\n");

	(void) id;
#if HAL_USE_SDC
	if (sdcConnect(&SDCD1)) {
#else
	if (mmcConnect(&MMCD1)) {
#endif
	  chprintf((BaseSequentialStream*) &SD1, "sd.c: Error connecting to SD card\n");
	  return;
	}
	//We have a usable block device
	sd_block_ready = TRUE;

	err = f_mount(&SDC_FS, "/", 1);
	if (err != FR_OK) {
	    chprintf((BaseSequentialStream*) &SD1, "sd.c: SD card connected but mount failed, error %d\n", err);
	    //leave device connected so shell could format, for example
		return;
	}

	chprintf((BaseSequentialStream*) &SD1, "sd.c: SD card mounted successfully\n");
	sd_fs_ready = TRUE;
}

static void sd_remove_handler(eventid_t id) {
	(void) id;
	chprintf((BaseSequentialStream*) &SD1, "sd.c: SD card removed\n");

#if HAL_USE_SDC
	sdcDisconnect(&SDCD1);
#else
	mmcDisconnect(&MMCD1);
#endif
	sd_fs_ready = FALSE;
}

static event_source_t sd_inserted_event, sd_removed_event;

static void tmrfunc(void *p) {
	BaseBlockDevice *bbdp = p;
	
	chSysLockFromISR();
	if (cnt > 0) {
		if (blkIsInserted(bbdp)) {
			if (--cnt == 0) {
				chEvtBroadcastI(&sd_inserted_event);
			}
		}
		else cnt = SD_POLLING_INTERVAL;
	}
	else if (!blkIsInserted(bbdp)) {
		cnt = SD_POLLING_INTERVAL;
		chEvtBroadcastI(&sd_removed_event);
	}
	chVTSetI(&tmr, TIME_MS2I(SD_POLLING_DELAY), tmrfunc, bbdp);
	chSysUnlockFromISR();
}

static void sd_tmr_init(void *p) {
	chEvtObjectInit(&sd_inserted_event);
	chEvtObjectInit(&sd_removed_event);
	chSysLock();
	cnt = SD_POLLING_INTERVAL;
	chVTSetI(&tmr, TIME_MS2I(SD_POLLING_DELAY), tmrfunc, p);
	chSysUnlock();
}

static uint8_t sdc_driver_scratchpad[512];
static const SDCConfig sdc_config = {
  sdc_driver_scratchpad,
  SDC_MODE_4BIT
};


uint8_t sd_init(void) {
	/*
	* On insertion SDC initialization and FS mount.
	*/
	static const evhandler_t sd_evhndl[] = {sd_insert_handler, sd_remove_handler};
	event_listener_t sd_inserted_listener, sd_removed_listener;
	sdcStart(&SDCD1, &sdc_config);
	// Activate card insertion monitor
	sd_tmr_init(&SDCD1);
	chEvtRegister(&sd_inserted_event, &sd_inserted_listener, 0);
	chEvtRegister(&sd_removed_event, &sd_removed_listener, 0);
	chEvtDispatch(sd_evhndl, chEvtWaitOneTimeout(ALL_EVENTS, TIME_MS2I(SD_TIMEOUT)));
	return sd_fs_ready ? 0 : 1;
}

uint8_t sd_write(FIL* fil, char* string) {
	unsigned int len = strlen(string);
	unsigned int written;
	FRESULT failure = f_write(fil, string, len, &written);
	if(failure) {
		//TODO handle error
		return failure;
	}
	if(len < written) {
		//TODO handle error
		return SD_PARTIAL_WRITE;
	}
	return FR_OK;
}

uint8_t sd_test(void) {
	FIL f;
	FRESULT open_err = f_open(&f, "testing123.txt", FA_CREATE_NEW);

	f_close(&f);
	open_err = f_open(&f, "testing123.txt", FA_OPEN_APPEND);

	if(open_err != FR_OK) {
		f_close(&f);
		return open_err;
	}	

	FRESULT write_err = sd_write(&f, "testing\n");
	if(write_err) {
		f_close(&f);
		return write_err;
	}
	f_close(&f);
	return FR_OK;
}

void sd_mkfs(void)
{
	chprintf(&SD1, "Disk Status: %u\n", disk_status(1));
	chprintf(&SD1, "Disk Init: %u\n", disk_initialize(1));
	chprintf(&SD1, "Disk Status: %u\n", disk_status(1));


	BYTE work[FF_MAX_SS];
	FRESULT f;
	//If we're building FATFS without multiple parititon support (as we
	// currently are) then mkfs makes a suitable single-entry partition table
	f = f_mkfs("/", FM_ANY, 0, work, sizeof work);

	chprintf(&SD1, "Attempted to create filesystem; success %u\n", f);
 }
