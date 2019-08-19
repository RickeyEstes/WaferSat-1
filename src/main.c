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
#include "pi2c.h"
#include "sensors/common.h"
#include "radio/si.h"

int main(void) {
	halInit();
	chSysInit();
	log_init();
	sensor_init();
	si_err_t error = si_init();
	log_info("Initialized with err %u.", error);

	while (true) {
		uint16_t test[] = {484, 1964, 1237};
		logb_info(test, sizeof(test[0]), sizeof(test)/sizeof(test[0]),
			"TESTING %u %i %f: %u ", 1, -2, 3.0);
		LED_OK();
		chThdSleepMilliseconds(1000);
		LED_CLEAR();
		chThdSleepMilliseconds(1000);
	}
}
