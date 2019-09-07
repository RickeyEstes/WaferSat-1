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
#include "wss_shell.h"
#include "dram_config.h"

static const ShellConfig shell_cfg1 = {
		(BaseSequentialStream *)&SD1, \
			shell_commands };

#define SHELL_THREAD_WA_SIZE 2048
static THD_WORKING_AREA (shell_thread_wa, SHELL_THREAD_WA_SIZE);
//static thread_t *logger_thread;
static thread_t *shell_thread = NULL;


int main(void)
{
	halInit();
	chSysInit();

	log_init();

	sensor_init();
	sd_init();
	shellInit();
	OV5640_init();
	fsmcSdramInit();
	fsmcSdramStart(&SDRAMD, &sdram_cfg);

	while (TRUE)
	{
		if (shell_thread == NULL)
		{
			log_set_level(LOG_WARN);
			shell_thread = chThdCreateStatic(shell_thread_wa, SHELL_THREAD_WA_SIZE,
					NORMALPRIO, shellThread, (void*)(&shell_cfg1));
		}
		else if(chThdTerminatedX(shell_thread))
		{
			chThdRelease(shell_thread);
			shell_thread = NULL;
			log_set_level(LOG_TRACE);
		}
		//chEvtDispatch(evhndl, chEvtWaitOneTimeout(ALL_EVENTS, TIME_MS2I(500)));
		chThdYield();
	}
}
