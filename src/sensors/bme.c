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

	Edited substantially for use with WAFERSAT by Varun Iyer
 ***************************************************************************/

#include "ch.h"
#include "hal.h"
#include "pi2c.h"
#include "sensors/common.h"
#include "sensors/bme.h"
#include "log.h"
#include <math.h>

static struct {
	uint16_t T1;
	int16_t T2, T3;
	
	uint16_t P1;
	int16_t P2, P3, P4, P5, P6, P7, P8, P9;

	uint8_t H1, H3;
	int16_t H2, H4, H5;
	int8_t H6;
	
	int32_t t_fine;
} calib;

#define reg16(r) (I2C_read16_LE( \
	BME_ADDR, BME_REGISTER_ ## r, (uint16_t*) &calib.r) ? \
	SENSOR_OK : SENSOR_COMM_ERR)
#define reg8(r) (I2C_read8( \
	BME_ADDR, BME_REGISTER_ ## r, (uint8_t*) &calib.r) ? \
	SENSOR_OK : SENSOR_COMM_ERR)
enum SensorErr bme_init(void)
{
	enum SensorErr err = SENSOR_OK;
	err |= reg16(T1);
	err |= reg16(T2);
	err |= reg16(T3);

	err |= reg16(P1);
	err |= reg16(P2);
	err |= reg16(P3);
	err |= reg16(P4);
	err |= reg16(P5);
	err |= reg16(P6);
	err |= reg16(P7);
	err |= reg16(P8);
	err |= reg16(P9);

	err |= reg8(H1);
	err |= reg16(H2);
	err |= reg8(H3);

	err |= reg8(H4);
	err |= reg8(H5);
	err |= reg8(H6);
	calib.H4 = (((int8_t) calib.H4) << 4) | (calib.H5 >> 4 & 0x0F);
	calib.H5 = (((int8_t) calib.H6) << 4) | (calib.H5 >> 4 & 0x0F);
	
	// Set before CONTROL (DS 5.4.3)
	//Register setting from Adafruit lib, I’m leaving it alone.
	err |= I2C_write8(BME_ADDR, BME_REGISTER_CONTROLHUMID, 0x03) ?
		SENSOR_OK : SENSOR_COMM_ERR;
	err |= I2C_write8(BME_ADDR, BME_REGISTER_CONTROL, 0x3F) ?
		SENSOR_OK : SENSOR_COMM_ERR;
	if(err != SENSOR_OK) {
		log_error("Failed to read calibration values from BME!");
		return err;
	}
	log_trace("Successfully initialized BME!");
	chThdSleep(TIME_MS2I(50)); // Wait for BME
	return err;
}
#undef reg8
#undef reg16

/**
* Reads temperature
* private function
* @return temperature in degC * 100
*/
static uint16_t therm(void)
{
	int32_t adc;
	uint16_t tmp;
	I2C_read16(BME_ADDR, BME_REGISTER_TEMPDATA, &tmp);
	adc = tmp;
	I2C_read8(BME_ADDR, BME_REGISTER_TEMPDATA + 2, (uint8_t*) &tmp);
	adc <<= 8;
	adc |= tmp & 0xFF;
	adc >>= 4;
	//Magic code from the adafruit repo
	int32_t v1 = ((((adc>>3) - ((int32_t)calib.T1 << 1))) * ((int32_t)calib.T2));
	v1 >>= 11;
	
	int32_t v2 = ((adc>>4) - ((int32_t)calib.T1))
					* ((adc>>4) - ((int32_t)calib.T1));
	v2 >>= 12;
	v2 *= ((int32_t) calib.T3);
	v2 >>= 14;
	calib.t_fine = v1 + v2;
	return (calib.t_fine * 5 + 128) >> 8;
}

/**
* Reads the barometric pressure
* @param Values to be sampled
* @return Pressure in Pa * 10
*/
static uint32_t press(void)
{
	// Magic code from adafruit 
	int64_t var1, var2, p;
	uint16_t tmp;

	uint64_t sum = 0;
	 
	for(uint16_t i = 0; i < BME_MEANS; i++) {
		int32_t adc_P;
		I2C_read16(BME_ADDR, BME_REGISTER_PRESSUREDATA, &tmp);
		adc_P = tmp;
		I2C_read8(BME_ADDR, BME_REGISTER_PRESSUREDATA + 2,
			(uint8_t*)&tmp);
		adc_P <<= 8;
		adc_P |= tmp & 0xFF;
		adc_P >>= 4;

		var1 = ((int64_t) calib.t_fine) - 128000;
		var2 = var1 * var1 * (int64_t) calib.P6;
		var2 = var2 + ((var1 * (int64_t) calib.P5) << 17);
		var2 = var2 + (((int64_t)calib.P4) << 35);
		var1 = ((var1 * var1 * (int64_t)calib.P3) >> 8) 
				+ ((var1 * (int64_t)calib.P2) << 12);
		var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)calib.P1) >> 33;

		if (var1 == 0) {
			return 0;  // avoid exception caused by division by zero
		}

		p = 1048576 - adc_P;
		p = (((p << 31) - var2) * 3125) / var1;
		var1 = (((int64_t)calib.P9) * (p>>13) * (p>>13)) >> 25;
		var2 = (((int64_t)calib.P8) * p) >> 19;

		sum += ((p + var1 + var2) >> 8) + (((int64_t)calib.P7) << 4);
	}

	return sum / (BME_MEANS * 26);
}

/**
  * Reads the relative humidity
  * @return rel. humidity in % * 10
  */
static uint8_t hum(void)
{
	// magic adafruit code
	int32_t adc_H;
	uint16_t tmp;
	I2C_read16(BME_ADDR, BME_REGISTER_HUMIDDATA, &tmp);
	adc_H = tmp;

	int32_t v_x1_u32r;

	v_x1_u32r = (calib.t_fine - ((int32_t)76800));

	v_x1_u32r = (((((adc_H << 14) - (((int32_t)calib.H4) << 20) -
		(((int32_t)calib.H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
		(((((((v_x1_u32r * ((int32_t)calib.H6)) >> 10) *
		(((v_x1_u32r * ((int32_t)calib.H3)) >> 11) + ((int32_t)32768))) >> 10) +
		((int32_t)2097152)) * ((int32_t)calib.H2) + 8192) >> 14));

	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calib.H1)) >> 4));

	v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
	v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
	float h = (v_x1_u32r>>12);
	return h / 1020;
}
 
/**
  * Calculates the altitude (in meters) from the specified atmospheric
  * pressure (in Pa*10), and sea-level pressure (in Pa).
  * @param press Airpressure in Pa*10
  * @return altitude in cm
  */
static int32_t alt(uint32_t press)
{
	return (1.0-pow((float)press/(float)(BME_SEA_PRESS*10), 1.0/5.255)) 
			* 288150000 / 65;
}

 
struct bme_t bme_get(void)
{
	struct bme_t data = bme_t_init();
	uint8_t val = 0;
	if(!I2C_read8(BME_ADDR, BME_REGISTER_CHIPID, &val)) {
		data.err |= SENSOR_COMM_ERR;
		log_error("Failed to communicate with BME chip!");
		return data;
	}
	if(val != BME_CHIPID) {
		data.err |= SENSOR_INV_RESP;
		log_error("Received invalid chipID %u from BME chip!", val);
		return data;
	}
	
	data.therm = therm();
	data.press = press();
	data.hum = hum();
	data.alt = alt(data.press);
	log_trace("Succesfully read BME data " BME_HUMAN_STR, BME_T_FIELDS(&data));
	return data;
}
