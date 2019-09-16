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
#include "pkttypes.h"
#include "ax25_pad.h"
#include "types.h"
#include "aprs.h"
#include "radio.h"
#include "debug.h"
#include "si446x.h"

/*
 * The code responsible for APRS implements a task manager to allow parallel
 * processes to use the radio asynchronously. Currently, posting a task is
 * equivalent to feeding a FIFO, which the manager reads. The current issue is
 * that if a thread dynamically created by the manager posts a task to the FIFO, 
 * the program crashes.
 *
 * Therefore, we will recreate these conditions to try to reproduce the error.
 * We need a thread that processes events coming from a FIFO and dynamically 
 * starts a child process upon certain events. The child process then writes to 
 * that same FIFO upon completion to notify the manager that the process is 
 * complete.
 */

// Posts a message to FIFO
static void send_message(uint8_t *msg, dyn_objects_fifo_t* task_fifo) {
	objects_fifo_t *task_queue = chFactoryGetObjectsFIFO(task_fifo);
	chFifoSendObject(task_queue, msg);
}

// Child thread spawned by manager
static THD_FUNCTION(child, arg) {
	TRACE_INFO("Child > Started");
	dyn_objects_fifo_t *task_fifo = arg;
	chThdSleepMilliseconds(3000);
	TRACE_INFO("Child > Finished");
	uint8_t message = 1;
	send_message(&message, task_fifo);
	chThdSleepMilliseconds(3000);
}

// Main manager thread, structured like Sven's
static THD_FUNCTION(manager, arg) {
	TRACE_INFO("Started manager");

	dyn_objects_fifo_t *task_fifo = arg;
	objects_fifo_t *task_queue = chFactoryGetObjectsFIFO(task_fifo);

	while(true) {
		// Wait for object coming from fifo
		uint8_t* task;
		chFifoReceiveObjectTimeout(task_queue, (void *)&task, TIME_INFINITE);

		TRACE_INFO("Received message %d", *task);

		switch((*task)) {
			case 0: {
				TRACE_INFO("Spawned new thread");
				chThdCreateFromHeap(NULL,
					THD_WORKING_AREA_SIZE(4096),
					"child",
					NORMALPRIO,
					child,
					NULL);
				continue;
			}

			case 1:	{
				// Do nothing
				TRACE_INFO("Do nothing");
				continue;
			}
		}
	}

	chThdExit(0);
}

int main(void) {
	halInit();
	chSysInit(); 

	debug_init();
	TRACE_INFO("Begin");

	// FIFO accepts 1 byte objects
	dyn_objects_fifo_t *task_fifo = chFactoryCreateObjectsFIFO("tasks", 
		8, 10, 1);
	
	TRACE_INFO("Created task_fifo");
	
	chDbgAssert(task_fifo != NULL, "fifo not created");

	thread_t* manager_thd = chThdCreateFromHeap(NULL,
				THD_WORKING_AREA_SIZE(4096),
				"manager",
				NORMALPRIO,
				manager,
				task_fifo);
	
	uint8_t message = 0;
	send_message(&message, task_fifo);
	
	msg_t msg = chThdWait(manager_thd);

	TRACE_INFO("Manager terminated with exit status 0x%x", msg);

	return 0;
}
