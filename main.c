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
#include "./pecan-pico/source/config/types.h"
#include "types.h"

int main(void) {
    halInit();
    chSysInit();

    char *call_sign = "N6RAJ";
    char *path = "WIDE";	    // TODO Change for testing
    char *recipient = "N6RAJ";
    char *message = "WAFERTEST";
    bool ack = false;

    radio_freq_t frequency = 144000000;
    channel_hz_t step = 0;
    radio_ch_t channel = 0;

    // Magic number used by Pecan Pico for power, need to figure out units
    radio_pwr_t power = 0x7F;

    // Magic number used by Pecan Pico for Clear Channel Assessment (If channel is below this threshold, it is likely
    // clear)
    radio_squelch_t cca = 0x4F;
    mod_t modulation = MOD_AFSK;
    
    packet_t msg = aprs_format_transmit_message(call_sign, path, recipient, message, ack);
    transmitOnRadio(msg, frequency, step, channel, power, modulation, cca);
}
