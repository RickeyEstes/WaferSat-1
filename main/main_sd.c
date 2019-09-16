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

	while (true) {
		log_data();
		 
		char log[1024];
		char* ptr = log;
		ptr += snprintf(ptr, log + 1024 - ptr, "I2C Scan:");
		uint8_t addresses[127];
		uint8_t numd = I2C_scan(addresses);
		for(int i = 0; i < numd; i++) {
			ptr += snprintf(ptr, log + 1024 - ptr, " %02X", addresses[i]);
		}
		log_debug(log);
		 
		LED_OK();
		chThdSleepMilliseconds(1000);
		LED_CLEAR();
		chThdSleepMilliseconds(1000);
	}
}
