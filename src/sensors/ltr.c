/*
* ltr.c
* Library for Lite-On LTR-329ALS-01 ambient light sensor
*
* Created on: Nov 8, 2018
* 	Author: Peter Krogen
* Heavily modified on: 2019-08-14
* 	Author: Varun Iyer
*/

#include "ch.h"
#include "hal.h"
#include "sensors/ltr.h"
#include "sensors/common.h"
#include "log.h"
#include "pi2c.h"
#include <math.h>

enum SensorErr ltr_init(void){
	enum SensorErr err = SENSOR_OK;
	err |= I2C_write8(LTR_ADDR, LTR_CONTR_REG, LTR_GAIN_1X | LTR_ACTIVE) ?
		SENSOR_OK : SENSOR_COMM_ERR;
	err |= I2C_write8(LTR_ADDR, LTR_MEAS_RATE_REG, LTR_INT_400 | LTR_RATE_500)
		? SENSOR_OK : SENSOR_COMM_ERR;
	chThdSleepMilliseconds(10);
	if(err & SENSOR_COMM_ERR) {
		log_error("Failed to communicate with LTR!");
	} else {
		log_trace("Succesfully initialized LTR.");
	}
	return err;
}

#define swap_byte(val) (((val >> 8) & 0xFF) | ((val & 0xFF) << 8))

struct ltr_t ltr_get(void) {
	struct ltr_t data = ltr_t_init();
	
	uint8_t val;
	if(I2C_read8(LTR_ADDR, LTR_MANUFAC_ID, &val)) {
		data.err |= (val == 0x05) ? SENSOR_OK : SENSOR_INV_RESP;
	} else {
		data.err |= SENSOR_COMM_ERR;
		return data;
	}

	data.err |= I2C_read16(LTR_ADDR, LTR_DATA_CH0_LOW, &(data.ch0)) ?
		SENSOR_OK : SENSOR_COMM_ERR;
	data.err |= I2C_read16(LTR_ADDR, LTR_DATA_CH1_LOW, &(data.ch1)) ?
		SENSOR_OK : SENSOR_COMM_ERR;
	data.ch0 = swap_byte(data.ch0);
	data.ch1 = swap_byte(data.ch1);

	log_trace("Succesfully read LTR data " LTR_HUMAN_STR, LTR_T_FIELDS(&data));
	return data;
}

#undef swap_byte
