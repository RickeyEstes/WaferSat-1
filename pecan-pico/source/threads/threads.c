#include "ch.h"
#include "hal.h"

#include "watchdog.h"
#include "pi2c.h"
#include "pac1720.h"
#include "radio.h"
#include "si446x.h"
#include "image.h"
//#include "position.h"
#include "beacon.h"
#include "log.h"
#include "radio.h"
#include "ax25_pad.h"
#include "flash.h"

sysinterval_t watchdog_tracking;

void start_essential_threads(void)
{
	init_watchdog();				// Init watchdog
	pac1720_init();					// Initialize current measurement
	chThdSleep(TIME_MS2I(300));		// Wait for tracking manager to initialize
}

void start_user_threads(void) {
	// Copy 
	memcpy(&conf_sram, &conf_flash_default, sizeof(conf_t));

	/* TODO: Implement scheduler that will run threads based on schedule. */
	if(conf_sram.pos_pri.beacon.active)
	  start_beacon_thread(&conf_sram.pos_pri, "POS1");
	if(conf_sram.pos_sec.beacon.active)
	  start_beacon_thread(&conf_sram.pos_sec, "POS2");

	if(conf_sram.img_pri.svc_conf.active)
	  start_image_thread(&conf_sram.img_pri);
	if(conf_sram.img_sec.svc_conf.active)
	  start_image_thread(&conf_sram.img_sec);

	if(conf_sram.log.svc_conf.active)
	  start_logging_thread(&conf_sram.log);

    if(conf_sram.aprs.rx.svc_conf.active
        && conf_sram.aprs.digi
        && conf_sram.aprs.tx.beacon.active) {
      start_beacon_thread(&conf_sram.aprs.tx, "BCN");
    }

	if(conf_sram.aprs.rx.svc_conf.active) {
	  chThdSleep(conf_sram.aprs.rx.svc_conf.init_delay);
	  start_aprs_threads(PKT_RADIO_1,
	                  conf_sram.aprs.rx.radio_conf.freq,
	                  0,
	                  0,
	                  conf_sram.aprs.rx.radio_conf.rssi);
	}
}

/**
 * General thread termination and cleanup.
 * Called by the thread that is terminating.
 * A message is posted to the idle thread.
 * Idle then releases the calling thread.
 */
void pktThdTerminateSelf(void) {
  /* Post self thread to idle for termination cleanup. */
  msg_t msg = chMsgSend(chSysGetIdleThreadX(), MSG_OK);
  chThdExit(msg);
}

/**
 * General thread termination and cleanup.
 * Called from the idle thread hook.
 */
void pktIdleThread(void) {
  chSysLock();
  if(!chMsgIsPendingI(chThdGetSelfX())) {
    chSysUnlock();
    return;
  }
  /* Get the message from the terminating thread. */
  chSysUnlock();
  thread_t *tp = chMsgWait();
  (void)chMsgGet(tp);
  chMsgRelease(tp, MSG_OK);
  (void)chThdWait(tp);
}

