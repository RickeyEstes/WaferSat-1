/***************************************************************************
  This is a library for the BME humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef __BME_H__
#define __BME_H__

#include "ch.h"
#include "hal.h"

#define BME_SEA_PRESS				101325

#define BME_REGISTER_T1				0x88
#define BME_REGISTER_T2				0x8A
#define BME_REGISTER_T3				0x8C

#define BME_REGISTER_P1				0x8E
#define BME_REGISTER_P2				0x90
#define BME_REGISTER_P3				0x92
#define BME_REGISTER_P4				0x94
#define BME_REGISTER_P5				0x96
#define BME_REGISTER_P6				0x98
#define BME_REGISTER_P7				0x9A
#define BME_REGISTER_P8				0x9C
#define BME_REGISTER_P9				0x9E

#define BME_REGISTER_H1				0xA1
#define BME_REGISTER_H2				0xE1
#define BME_REGISTER_H3				0xE3
#define BME_REGISTER_H4				0xE4
#define BME_REGISTER_H5				0xE5
#define BME_REGISTER_H6				0xE7

#define BME_REGISTER_CHIPID			0xD0
#define BME_REGISTER_VERSION		0xD1
#define BME_REGISTER_SOFTRESET		0xE0

#define BME_REGISTER_CAL26			0xE1

#define BME_REGISTER_CONTROLHUMID	0xF2
#define BME_REGISTER_CONTROL		0xF4
#define BME_REGISTER_CONFIG			0xF5
#define BME_REGISTER_PRESSUREDATA	0xF7
#define BME_REGISTER_TEMPDATA		0xFA
#define BME_REGISTER_HUMIDDATA		0xFD

#define BME_CHIPID					0x60
#define BME_ADDR					0x77

// Number of samples from BME or something like that
#define BME_MEANS					32

struct bme_t {
	int16_t therm;
	uint32_t press;
	uint8_t hum;
	uint8_t alt;
	enum SensorErr err;
};
#define BME_HUMAN_STR "therm:%i press:%lu hum:%u alt:%u err:%u"
#define BME_CSV_STR "%i,%lu,%u,%u,%u"
#define BME_T_FIELDS(dptr) ((dptr)->therm), ((dptr)->press), ((dptr)->hum), \
	((dptr)->alt), ((dptr)->err)
#define bme_t_init() ((struct bme_t){0, 0, 0, 0, SENSOR_OK})

enum SensorErr bme_init(void);
struct bme_t bme_get(void);

#endif /* __BME_H__ */
