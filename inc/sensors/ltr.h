/*
* ltr.h
* Library for Lite-On LTR-329ALS-01 ambient light sensor
*
* Created on: Nov 8, 2018
* 	Author: Peter Krogen
* Heavily modified: 2019-08-14
* 	Author: Varun Iyer <varun_iyer@protonmail.ch>
*/

#ifndef __LTR_H__
#define __LTR_H__

#include "ch.h"
#include "hal.h"

#define LTR_ADDR            0x29
#define LTR_CONTR_REG       0x80
#define LTR_MEAS_RATE_REG   0x85
#define LTR_MANUFAC_ID      0x87

#define LTR_DATA_CH1_LOW    0x88
#define LTR_DATA_CH1_HIGH   0x89
#define LTR_DATA_CH0_LOW    0x8A
#define LTR_DATA_CH0_HIGH   0x8B

#define LTR_ACTIVE          0x01
#define LTR_STANDBY         0x00

#define LTR_GAIN_1X         0x00<<2
#define LTR_GAIN_2X         0x01<<2
#define LTR_GAIN_4X         0x02<<2
#define LTR_GAIN_8X         0x03<<2
#define LTR_GAIN_48X        0x06<<2
#define LTR_GAIN_96X        0x07<<2

#define LTR_INT_50          0x01<<3
#define LTR_INT_100         0x00<<3
#define LTR_INT_150         0x04<<3
#define LTR_INT_200         0x02<<3
#define LTR_INT_250         0x05<<3
#define LTR_INT_300         0x06<<3
#define LTR_INT_350         0x07<<3
#define LTR_INT_400         0x03<<3

#define LTR_RATE_50         0x00
#define LTR_RATE_100        0x01
#define LTR_RATE_200        0x02
#define LTR_RATE_500        0x03
#define LTR_RATE_1000       0x04
#define LTR_RATE_2000       0x05

#include "sensors/common.h"

struct ltr_t {
	uint16_t ch0, ch1;
	enum SensorErr err;
};
 
#define LTR_HUMAN_STR "ch0:%i ch1:%i err:%u"
#define LTR_CSV_STR "%i,%i,%u"
#define LTR_T_FIELDS(dptr) ((dptr)->ch0), ((dptr)->ch1), ((dptr)->err)
#define ltr_t_init() ((struct ltr_t){0, 0, SENSOR_OK})

enum SensorErr ltr_init(void);
struct ltr_t ltr_get(void);

#endif /* __LTR_H__ */
