#include "ch.h"
#include "hal.h"
#include "log.h"
#include "sd.h"
#include "gps.h"
#include "emmc.h"
#include "hal_fsmc_sdram.h"
#include "is42s16400j.h"
#include "ov5640.h"
#include "stdio.h"
#include "chprintf.h"
#include "membench.h"
#include "log.h"
#include "ff.h"
#include "pi2c.h"

int main(void) {
	int init_err = 0;
	halInit();
	chSysInit();
	log_init();

	init_err &= gps_init();
	sd_init();
	while (true) {
		log_data();
		LED_OK();
		chThdSleepMilliseconds(1000);
		LED_CLEAR();
		chThdSleepMilliseconds(1000);
	}
}
