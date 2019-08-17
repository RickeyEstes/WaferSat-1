/*
* IMU.c
* Library for IMU accelerometer
*
* 	Created on: Nov 8, 2018
* 		Author: Peter Krogen
* 	Reorganized on 2019-08-13
		Author: Varun Iyer <varun_iyer@protonmail.ch>
*/

#include "ch.h"
#include "hal.h"
#include "sensors/imu.h"
#include "pi2c.h"
#include "log.h"
#include <math.h>

/**
 * @brief	Initializes Inertial Measurement Unit (IMU)
 * @note	Basically just ensures that we can talk to it
 *
 * @return	Error state
 * @see		SensorErr
 */
enum SensorErr imu_init(void)
{
	uint8_t val;
	if(I2C_read8(IMU_ADDR, IMU_WHO_AM_I, &val)) {
		if(val != IMU_ACK_ID) {
			log_error("Failed to init IMU; read unexpected value %u!", val);
			return SENSOR_COMM_ERR | SENSOR_INV_RESP;
		}
		log_trace("Successfully intialized IMU.");
		return SENSOR_OK;
	} else {
		log_error("Failed to init IMU; did not read any response!");
		return SENSOR_COMM_ERR; // imu not found
	}
}

/**
 * @brief	Gets data from the Inertial Measurement Unit (IMU)
 * @note	Data comes from the accelerometers, units currently unknown
 * 
 * @return	Accelerometer data in the x, y, and z directions; and the error state
 * @see		imu_t
 */
struct imu_t imu_get(void)
{
	// TODO Figure out units and document
	uint16_t val;
	struct imu_t data = imu_t_init();
	if(I2C_read16(IMU_ADDR, IMU_ACCEL_XOUT_H, &val)) {
		data.x = (int16_t) val * 1000 / 16384;
	} else {
		data.err |= SENSOR_COMM_ERR;
		data.x = SENSOR_INV_DATA;
	}
	if(I2C_read16(IMU_ADDR, IMU_ACCEL_YOUT_H, &val)) {
		data.y = (int16_t) val * 1000 / 16384;
	} else {
		data.err |= SENSOR_COMM_ERR;
		data.y = SENSOR_INV_DATA;
	}
	if(I2C_read16(IMU_ADDR, IMU_ACCEL_ZOUT_H, &val)) {
		data.z = (int16_t) val * 1000 / 16384;
	} else {
		data.err |= SENSOR_COMM_ERR;
		data.z = SENSOR_INV_DATA;
	}
	log_trace("Succesfully read IMU data " IMU_HUMAN_STR, IMU_T_FIELDS(&data));
	return data;
}
