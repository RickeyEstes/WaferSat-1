/*
 * therm.h
 * Library for TI TMP100 temperature sensor
 *
 * Created on: 2018-11-08:
 * 	Author: Peter Krogen
 *  Reformatted on 2019-08-12:
 * 	Author: Varun Iyer <varun_iyer@protonmail.ch>
 */

#ifndef __THERM_H__
#define __THERM_H__

#include "ch.h"
#include "hal.h"
#include "common.h"

#define THERM_ADDR                     0x48
#define THERM_TEMP_REG                 0x00
#define THERM_CONTR_REG                0x01
#define THERM_TEMP_THRESH_HIGH_REG     0x02
#define THERM_TEMP_THRESH_LOW_REG      0x03

#define THERM_ENABLE_SHUTDOWN          0x01
#define THERM_DISABLE_SHUTDOWN         0x00

//Thermostat mode
#define THERM_COMPARATOR_MODE          0x00
#define THERM_INTERRUPT_MODE           0x02

//Polarity
#define THERM_POLARITY_LOW             0x00        //Active Low
#define THERM_POLARITY_HIGH            0x04        //Active High

//Fault queue
#define THERM_CONSECUTIVE_FAULTS_1     0x00
#define THERM_CONSECUTIVE_FAULTS_2     0x08
#define THERM_CONSECUTIVE_FAULTS_4     0x10
#define THERM_CONSECUTIVE_FAULTS_6     0x18

//Converter Resolution
#define THERM_RESOLUTION_9_BIT         0x00        //0.5 degC
#define THERM_RESOLUTION_10_BIT        0x20        //0.25 degC
#define THERM_RESOLUTION_11_BIT        0x40        //0.125 degC
#define THERM_RESOLUTION_12_BIT        0x60        //0.0625 degC

struct therm_t {
	uint16_t therm_0;
	uint16_t therm_1;
	enum SensorErr err;
};
#define THERM_HUMAN_STR "therm0:%u therm1:%u err:%u"
#define THERM_CSV_STR "%u,%u,%u"
#define THERM_T_FIELDS(dptr) ((dptr)->therm_0), ((dptr)->therm_1), ((dptr)->err)
#define therm_t_init() ((struct therm_t){0, 0, SENSOR_OK})
 
enum SensorErr therm_init(void);
struct therm_t therm_get(void);

#endif /* __THERM_H__ */
