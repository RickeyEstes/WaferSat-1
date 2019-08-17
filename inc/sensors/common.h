#ifndef __COMMON_H__
#define __COMMON_H__

#include "ch.h"
#include "hal.h"

enum SensorErr {
	SENSOR_OK		= 0x00,
	SENSOR_INV_DATA	= 0x00, /* Default data value, NOT an error code */
	SENSOR_COMM_ERR	= 0x01,
	SENSOR_INV_RESP	= 0x01 << 1,
	SENSOR_INV_CS	= 0x01 << 2,
};

enum SensorErr sensor_init(void);
size_t sensor_cnprintf(char *buf, size_t n);
size_t sensor_hnprintf(char *buf, size_t n);

#endif /* COMMON_H_ */

