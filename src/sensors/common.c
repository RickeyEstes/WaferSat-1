#include "sensors/common.h"
#include "sensors/adc.h"
#include "sensors/bme.h"
#include "sensors/gps.h"
#include "sensors/imu.h"
#include "sensors/ltr.h"
#include "sensors/therm.h"

#define all_sensors(macro) \
	macro(adc); \
	macro(bme); \
	macro(gps); \
	macro(imu); \
	macro(ltr); \
	macro(therm) \

#define all_sensors(macro) \
	macro(adc); \
	macro(bme); \
	macro(gps); \
	macro(imu); \
	macro(ltr); \
	macro(therm) \

#define sensor_init_(sensor) err |= sensor ## _init()
/**
* Initializes all of the sensors available; returns success.
* @return success
* @see enum SensorErr
**/
enum SensorErr sensor_init(void) {
	enum SensorErr err = SENSOR_OK;
	all_sensors(sensor_init_);
	return err;
}
#undef sensor_init_

#define sensor_data_(sns) struct sns ## _t sns ## _data = sns ## _get()
/**
* Gets all sensor data and formats it into a csv
* @return number of bytes expected to be written into string
**/
size_t sensor_cnprintf(char* buf, size_t n) {
	all_sensors(sensor_data_);
	
	return snprintf(buf, n,
		ADC_CSV_STR "," BME_CSV_STR "," GPS_CSV_STR "," IMU_CSV_STR ","
		LTR_CSV_STR "," THERM_CSV_STR,
		ADC_T_FIELDS(&adc_data), BME_T_FIELDS(&bme_data), 
		GPS_T_FIELDS(&gps_data), IMU_T_FIELDS(&imu_data), 
		LTR_T_FIELDS(&ltr_data), THERM_T_FIELDS(&therm_data));
}

/**
* Gets all sensor data and formats it into a human-readable data string
* @return number of bytes expected to be written into string
**/
size_t sensor_hnprintf(char* buf, size_t n) {
	all_sensors(sensor_data_);
	
	return snprintf(buf, n,
		"\t" ADC_HUMAN_STR "\r\n\t" BME_HUMAN_STR "\r\n\t"
		GPS_HUMAN_STR "\r\n\t" IMU_HUMAN_STR "\r\n\t" LTR_HUMAN_STR "\r\n\t"
		THERM_HUMAN_STR,
		ADC_T_FIELDS(&adc_data), BME_T_FIELDS(&bme_data), 
		GPS_T_FIELDS(&gps_data), IMU_T_FIELDS(&imu_data), 
		LTR_T_FIELDS(&ltr_data), THERM_T_FIELDS(&therm_data));
}
