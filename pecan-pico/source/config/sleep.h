#ifndef __SLEEP_H__
#define __SLEEP_H__

#include "ch.h"
#include "hal.h"
#include "types.h"

#define WAIT_FOR_DATA_POINT		trigger_new_data_point
#define TX_CONTINUOSLY			trigger_immediately

bool p_sleep(const sleep_conf_t *config);
sysinterval_t waitForTrigger(sysinterval_t prev, sysinterval_t timeout);
void trigger_new_data_point(void);
void trigger_immediately(void);

#endif /* __SLEEP_H__ */

