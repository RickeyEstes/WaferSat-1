#include "ch.h"
#include "hal.h"

#include "config.h"
#include "pac1720.h"
#include "pi2c.h"
#include <stdlib.h>
#include "portab.h"

#define ADC_NUM_CHANNELS	4		/* Amount of channels (solar, battery, temperature) */
#define VCC_REF				3100	/* mV */

#define DIVIDER_VSOL		205/64	/* VSol -- 22kOhm -- ADC -- 10kOhm -- GND */
#define DIVIDER_VBAT		205/64	/* VBat -- 22KOhm -- ADC -- 10kOhm -- GND */
#define DIVIDER_VUSB		205/64	/* VUSB -- 22KOhm -- ADC -- 10kOhm -- GND */

static adcsample_t samples[ADC_NUM_CHANNELS]; // ADC sample buffer

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void)adcp;
	(void)buffer;
	(void)n;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 4 samples of 4 channels, SW triggered.
 * Channels:    Solar voltage divider    ADC1_IN12
 *              USB voltage divider      ADC1_IN14
 *              Battery voltage divider  ADC1_IN9
 *              Temperature sensor       ADC1_IN16
 */
static const ADCConversionGroup adcgrpcfg = {
	FALSE,
	ADC_NUM_CHANNELS,
	adccb,
	NULL,
	/* HW dependent part.*/
	0,
	ADC_CR2_SWSTART,
	ADC_SMPR1_SMP_AN14(ADC_SAMPLE_144) | ADC_SMPR1_SMP_AN12(ADC_SAMPLE_144) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144),
	ADC_SMPR2_SMP_AN9(ADC_SAMPLE_144),
	ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
	0,
	ADC_SQR3_SQ1_N(ADC_CHANNEL_IN12) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN14)  | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN9) | ADC_SQR3_SQ4_N(ADC_CHANNEL_SENSOR)
};

void initADC(void)
{
	adcStart(&ADCD1, NULL);
	adcSTM32EnableTSVREFE();
	palSetLineMode(LINE_ADC_VSOL, PAL_MODE_INPUT_ANALOG); // Solar panels
	palSetLineMode(LINE_ADC_VBAT, PAL_MODE_INPUT_ANALOG); // Battery
	palSetLineMode(LINE_ADC_VUSB, PAL_MODE_INPUT_ANALOG); // USB
}

void deinitADC(void)
{
	adcStop(&ADCD1);
}

void doConversion(void)
{
	initADC();
	adcStartConversion(&ADCD1, &adcgrpcfg, samples, 1);
	chThdSleep(TIME_MS2I(50)); // Wait until conversion is finished
	deinitADC();
}

uint16_t stm32_get_vbat(void)
{
	doConversion();
	return samples[2] * VCC_REF * DIVIDER_VBAT / 4096;
}

uint16_t stm32_get_vsol(void)
{
	doConversion();
	return samples[0] * VCC_REF * DIVIDER_VSOL / 4096;
}

uint16_t stm32_get_vusb(void)
{
	doConversion();
	return samples[1] * VCC_REF * DIVIDER_VUSB / 4096;
}

uint16_t stm32_get_temp(void)
{
	doConversion();
	return (((int32_t)samples[3]*40 * VCC_REF / 4096)-30400) + 2500 + 850/*Calibration*/;
}

