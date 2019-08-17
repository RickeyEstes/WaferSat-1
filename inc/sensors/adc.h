#ifndef __PADC_H__
#define __PADC_H__

#include "ch.h"
#include "hal.h"
#include "common.h"

// We need a struct because different calls to get_vbat/temp are different 
// readings

/** @struct adc_t
 *  @brief	    Stores data coming from the Analog to Digital Converter (ADC) 
 *  @note	    Readings are coming from the sensors on the microcontroller (MCU), 
 *		    not any external peripherals.
 */
struct adc_t {
	uint16_t vbat;	    /**< Stores the MCU battery voltage */
	uint16_t therm;	    /**< Stores the MCU temperature */
	enum SensorErr err; /**< Stores the ADC error state */
};
#define adc_t_init() ((struct adc_t){0, 0, SENSOR_OK})
#define ADC_T_FIELDS(dptr) ((dptr)->vbat), ((dptr)->therm), ((dptr)->err)
#define ADC_CSV_STR "%u,%u,%u"
#define ADC_HUMAN_STR "vbat:%u therm:%u err:%u"

enum SensorErr adc_init(void);
enum SensorErr adc_shutdown(void);
struct adc_t adc_get(void);

#endif /* __ADC_H__ */

