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

int main(void) {
    halInit();
    chSysInit();

    // Initialize pecan system
    debug_init();

    if(!pktSystemInit()) {
	TRACE_ERROR("PACKET_SYSTEM_NOT_INITIALIZED");
	return 1;
    }

    TRACE_INFO("\n\rBEGIN THE RADIO TEST");

    /*while(true) {
	// Test SPI
	uint8_t tx_buf[] = {0x33};
	uint8_t rx_buf[3] = {0x00};

	Si446x_conditional_init(PKT_RADIO_1);
	Si446x_read(PKT_RADIO_1, tx_buf, 1, rx_buf, 9);
	TRACE_INFO("Got {%#x, %#x, %#x}", rx_buf[0], rx_buf[1], rx_buf[2]); 
	chThdSleepMilliseconds(3000);
    }*/

    pktServiceCreate(PKT_RADIO_1);

    // APRS message parameters 
    const char *call_sign = "N6RAJ";
    const char *path = "WIDE";	    // TODO Change for testing
    const char *recipient = "N6RAJ";
    const char *text = "WAFERTEST";
    const bool ack = false;

    radio_freq_t frequency = (uint32_t) 144390000;
    channel_hz_t step = 0;
    radio_ch_t channel = 0;

    // Magic number used by Pecan Pico for power, need to figure out units
    radio_pwr_t power = 0x7F;

    // Magic number used by Pecan Pico for Clear Channel Assessment (If channel is below this threshold, it is likely
    // clear)
    radio_squelch_t cca = 0x4F;
    mod_t modulation = MOD_AFSK;
    
    packet_t msg = aprs_format_transmit_message(call_sign, path, recipient, text, ack);

    while(true) {
	if(msg == NULL) {
	    TRACE_ERROR("Invalid message");
	    continue;
	}

	transmitOnRadio(msg, frequency, step, channel, power, modulation, cca);

	chThdSleepMilliseconds(10000);
    }
}
