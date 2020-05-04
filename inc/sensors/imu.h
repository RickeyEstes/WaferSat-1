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

#define IMU_ADDR					0xD0 //ad0 low
#define IMU_WHO_AM_I				0x75

#define IMU_ACCEL_XOUT_H			0x3b
#define IMU_ACCEL_XOUT_L			0x3c

#define IMU_ACCEL_YOUT_H			0x3d
#define IMU_ACCEL_YOUT_L			0x3e

#define IMU_ACCEL_ZOUT_H			0x3f
#define IMU_ACCEL_ZOUT_L			0x40

#define IMU_ACCEL_SCALE				(1.0f / 16384.0f)

#define IMU_THERM_OUT_H				0x41
#define IMU_THERM_OUT_L				0x42
 
// FIXME this scale seems to be problematic
#define IMU_THERM_SCALE				(1.0f / 333.87f)
#define IMU_THERM_OFFSET			21.0f
 
#define IMU_GYRO_XOUT_H				0x41
#define IMU_GYRO_XOUT_L				0x42

#define IMU_GYRO_YOUT_H				0x43
#define IMU_GYRO_YOUT_L				0x44

#define IMU_GYRO_ZOUT_H				0x45
#define IMU_GYRO_ZOUT_L				0x46
 
// FIXME scaling is questionable
#define IMU_GYRO_SCALE				(1.0f / 131.0f)

#define IMU_ACK_ID					0x71

#include "common.h"

/**
 * @struct  imu_t
 * @brief	    Stores acceleration data from the IMU along 3 axes
 * @note	    Units unknown
 */
struct imu_t {
	float ax;		/**< Acceleration in the x direction in m/s^2 */
	float ay;		/**< Acceleration in the y direction in m/s^2 */
	float az;		/**< Acceleration in the z direction in m/s^2 */
	float gx;		/**< rotation degrees/s in the x direction */
	float gy;		/**< rotation degrees/s in the y direction */
	float gz;		/**< rotation degrees/s in the z direction */
	float therm;	/**< temperature in C */
	enum SensorErr err;	/**< Error state */
};
#define IMU_HUMAN_STR "ax:%f ay:%f az:%f gx:%f gy:%f gz:%f therm:%f err:%u"
#define IMU_CSV_STR "%f,%f,%f,%f,%f,%f,%f,%u"
#define IMU_T_FIELDS(dptr) ((dptr)->ax), ((dptr)->ay), ((dptr)->az), \
	((dptr)->gx), ((dptr)->gy), ((dptr)->gz), ((dptr)->therm), ((dptr)->err)
#define imu_t_init() ((struct imu_t){0.0, 0.0, 0.0, 0.0, 0.0, \
	0.0, 0.0, SENSOR_OK})

enum SensorErr imu_init(void);
struct imu_t imu_get(void);

#endif /* __IMU_H__ */
