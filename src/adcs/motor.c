#ifndef MOTOR_C
#define MOTOR_C
#include "motor.h"

#include <stdlib.h>

/**
 * @brief		Initializes and configures a motor object
 *
 * @param m		Pointer to a Motor object
 * @param pwmd		Pointer to a PWMDriver object mapped to the timer shared between the motors 
 * @param pwm		References the line controlling the power of the motor via a PWM signal
 * @param cw		References the clockwise line on the H Bridge controlling the motor's direction
 * @param ccw		References the counter-clockwise line on the H Bridge controlling the motor's direction
 * @param pwmc		Configuration of the PWM system (multiple motors may share this)
 */
void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, ioline_t pwm,
    ioline_t cw, ioline_t ccw, const PWMConfig *pwmc) {
	// Init motor object
	m->pwmd = pwmd;  
	m->channel = channel;
	m->pwm = pwm;
	m->dir = dir;
	
	// TODO 
	// Right now the pwm pin is arbitrarily set to AF1 (alternate function 1) to connect to timers 1 and 2
	// If that should change, set to AF2 for timers 3, 4, 5 or AF3 for timers 8, 9, 10, 11
	palSetLineMode(m->pwm, PAL_MODE_ALTERNATE(1));
	palSetLineMode(m->dir, PAL_MODE_OUTPUT_PUSHPULL);	
	
	// Ensures that the pwm driver only gets activated once, to avoid disabling the other channels
	if(pwmd->state != PWM_READY) {
		pwmStart(pwmd, pwmc);	
	}
	
}

/**
 * @brief		Start the motor or change speed to the given power (converted to duty cycle for PWM)
 *
 * @param m	    	Pointer to a Motor object
 * @param power		Ranges from -10000 to 10000, as a percentage of the maximum duty cycle
 *			 - 4750 -> 47.5%; -10000 -> 100%, reversed
 * @return		Error state (0 - SUCCESS, 1 - ERROR)
 *			 - Returns error if power exceeds allotted range
 */
int motor_start(Motor *m, int power) {
	if(abs(power) > 10000) {
		return 1;	
	}

	// Assigns HIGH to forward and LOW to backwards
	if(power > 0) {
	    palSetLine(m->dir);
	} else {
	    palClearLine(m->dir); 
	}

	// Sends pwm signals
	pwmEnableChannel(m->pwmd, m->channel, PWM_PERCENTAGE_TO_WIDTH(m->pwmd, abs(power)));

	// Updates motor object state 
	m->power = abs(power);	
	m->dir = power > 0;
	
	return 0;
}

/**
 *  @brief		Disables the motor
 *  @note		Currently disables pwm signals but leaves timer on. For extended periods of inactivity,
 *			disable the pwm driver itself to conserve power.
 */
int motor_disable(Motor *m) {
	motor->state = DISABLED;	
	pwmDisableChannel(m->pwmd, m->channel);
	return 0;
}

/**
 * @brief	    	Getter for motor's power
 * 
 * @param m		Pointer to a Motor object
 * @return		Magnitude of last assigned power value
 */
int motor_getPower(Motor *m) {
	return m->power;
}

/**
 * @brief		Getter for motor's direction
 *
 * @param m		Pointer to a Motor object
 * @return		true if last assigned to go forward, false if not 
 */
bool motor_getDirection(Motor *m) {
	return m->last_dir;
}


#endif	// MOTOR_C
