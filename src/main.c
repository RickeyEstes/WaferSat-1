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
#include "log.h"
#include "sd.h"
#include "emmc.h"
#include "hal_fsmc_sdram.h"
#include "ov5640.h"
#include "stdio.h"
#include "chprintf.h"
#include "log.h"
#include "ff.h"
#include "wdg.h"
#include "sdram.h"
#include "pi2c.h"
#include "sensors/common.h"
#include "sensors/ltr.h"
#include "radio/si.h"

int main(void) {
	halInit();
	chSysInit();
	// initialize watchdog first
	sd_init();
	log_init();
	log_info("help\r\n");
	sensor_init();
	//fsmcSdramInit();
	//fsmcSdramStart(&SDRAMD, &sdram_cfg);
	// OV5640_init();
	palSetPadMode(GPIOE, GPIOE_HEADER_PINE2, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPad(GPIOE, GPIOE_HEADER_PINE2);
	palSetPadMode(GPIOI, 8U, PAL_MODE_OUTPUT_PUSHPULL);
	palClearPad(GPIOI, 8U);
	//si_err_t error = si_init();
	//log_info("Initialized with err %u.", error);
	log_info("Initialized with err .");

	wdg_init();

	uint32_t count = 0;
	 
	while (true) {

		if(true) {
			uint8_t err = 0;
			err += log_data();
			struct ltr_t light = ltr_get();
			if(light.ch0 > 50 || light.ch1 > 50 || (count % 3600) == 0) {
				err += log_image();
			}
			count = 0;
			wdg_reset();
			if(err) {
				LED_ERR();
			}
			else {
				LED_OK();
			}
		}
		else {
			LED_INFO();
		}

		count++;

		// chThdSleepMilliseconds(500);
		LED_CLEAR();
		// chThdSleepMilliseconds(500);
		wdg_reset();
	}
}
