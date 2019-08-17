/*
* imu.h
* Library for MPU9250 accelerometers
*
* Created on: Nov 8, 2018
* 	Author: Peter Krogen
* Reorganized on: 2019-08-13
* 	Author: Varun Iyer <varun_iyer@protonmail.ch>
*/

#ifndef __IMU_H__
#define __IMU_H__

#include "ch.h"
#include "hal.h"

#define IMU_ADDR					0x68 //ad0 low
#define IMU_WHO_AM_I				0x75

#define IMU_ACCEL_XOUT_H			0x3b
#define IMU_ACCEL_XOUT_L			0x3c

#define IMU_ACCEL_YOUT_H			0x3d
#define IMU_ACCEL_YOUT_L			0x3e

#define IMU_ACCEL_ZOUT_H			0x3f
#define IMU_ACCEL_ZOUT_L			0x40

#define IMU_ACK_ID					0x71

#include "common.h"

/**
 * @struct  imu_t
 * @brief	    Stores acceleration data from the IMU along 3 axes
 * @note	    Units unknown
 */
struct imu_t {
	int16_t x;		/**< Acceleration in the x direction */
	int16_t y;		/**< Acceleration in the y direction */
	int16_t z;		/**< Acceleration in the z direction */
	enum SensorErr err;	/**< Error state */
};
#define IMU_HUMAN_STR "x:%i y:%i z:%i err:%u"
#define IMU_CSV_STR "%i,%i,%i,%u"
#define IMU_T_FIELDS(dptr) ((dptr)->x), ((dptr)->y), ((dptr)->z), ((dptr)->err)
#define imu_t_init() ((struct imu_t){0, 0, 0, SENSOR_OK})

enum SensorErr imu_init(void);
struct imu_t imu_get(void);

#endif /* __IMU_H__ */
