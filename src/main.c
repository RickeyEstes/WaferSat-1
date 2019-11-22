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
#include "pi2c.h"
#include "sensors/common.h"
#include "radio/si.h"
#include "membench.h"
#include "sdram.h"

/*
 *  * Memory benchmark definitions
 *   */

static uint8_t int_buf[64*1024];

/*
 *  *
 *   */
static membench_t membench_ext = {
		SDRAM_START,
		SDRAM_SIZE,
};

static membench_t membench_int = {
	    int_buf,
		    sizeof(int_buf),
};

static membench_result_t membench_result_ext2int;
static membench_result_t membench_result_int2ext;
 
static void membench() {
  log_info("Starting External RAM Benchmark....");
  membench_run(&membench_ext, &membench_int, &membench_result_int2ext);
  log_info(".");
  membench_run(&membench_int, &membench_ext, &membench_result_ext2int);
  log_info(".");

  log_info("OK\r\nRAM Performance (MB/s) memset, memcpy, memcpy_dma, memcmp\r\n");
  log_info("int2ext:                 %5D %7D %10D %7D \r\n",
             membench_result_int2ext.memset/1000000,
             membench_result_int2ext.memcpy/1000000,
             membench_result_int2ext.memcpy_dma/1000000,
             membench_result_int2ext.memcmp/1000000);

  log_info("ext2int:                 %5D %7D %10D %7D \r\n",
             membench_result_ext2int.memset/1000000,
             membench_result_ext2int.memcpy/1000000,
             membench_result_ext2int.memcpy_dma/1000000,
             membench_result_ext2int.memcmp/1000000);
}


int main(void) {
	halInit();
	chSysInit();
	fsmcSdramInit();
	fsmcSdramStart(&SDRAMD, &sdram_cfg);
	log_init();
	membench();
}
