#ifndef MOTOR_C
#define MOTOR_C
#include "motor.h"

#include <stdlib.h>

/**
 * Used internally to control state transitions
 */
typedef enum MotorState {
	UNINIT,			// Motor has not yet been initialized
	DISABLED,		// In low power mode
	CLOCKWISE,	    	// Actively turning clockwise
	COUNTER-CLOCKWISE,  	// Actively turning counter-clockwise
	ACTIVE_BRAKE,	    	// Actively stopping the motor
	IDLE		    	// No work being put into motor, but PWM is enabled 
} MotorState; 

/**
 * @brief		Initializes and configures a motor object
 *
 * @param m		Pointer to a Motor object
 * @param pwmd		Pointer to a PWMDriver object mapped to the timer shared between the motors 
 * @param channel	Channel of the motor on the timer sending pwm signal
 * @param pwm		References the line controlling the power of the motor via a PWM signal
 * @param cw		References the clockwise line on the H Bridge controlling the motor's direction
 * @param ccw		References the counter-clockwise line on the H Bridge controlling the motor's direction
 * @param sleep		References the line enabling/disabling the h bridge
 * @param pwmc		Configuration of the PWM system (multiple motors may share this)
 */
void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, ioline_t pwm,
    ioline_t cw, ioline_t ccw, ioline_t sleep, const PWMConfig *pwmc) {
	// Init motor object
	m->pwmd = pwmd;  
	m->channel = channel;	// TODO Can we infer this from driver and line?
	m->pwm = pwm;
	m->cw = cw;
	m->ccw = ccw;
	m->sleep = sleep;

	// TODO 
	// Right now the pwm pin is set to AF9 (alternate function 9) to connect to timers 13 and 14
	// If that should change, set to AF2 for timers 3, 4, 5 or AF3 for timers 8, 9, 10, 11
	palSetLineMode(m->pwm, PAL_MODE_ALTERNATE(9));
	palSetLineMode(m->cw, PAL_MODE_OUTPUT_PUSHPULL);	
	palSetLineMode(m->ccw, PAL_MODE_OUTPUT_PUSHPULL);	
	palSetLineMode(m->sleep, PAL_MODE_OUTPUT_PUSHPULL);	
	
	// Ensures that the pwm driver only gets activated once, to avoid disabling the other channels
	// TODO Make sure this will work with multiple motors on independent
	// timers
	if(pwmd->state != PWM_READY) {
		pwmStart(pwmd, pwmc);	
	}
	
}

/**
 * @brief		Start motor going clockwise at the given power 
 *			(converted to duty cycle for PWM)
 *
 * @pre			Motor is either already turning clockwise or in its idle state
 *
 * @param m	    	Pointer to a Motor object
 * @param power		Ranges from 0 to 10000, as a percentage of the maximum duty cycle
 *			 - 4750 -> 47.5%; -10000 -> 100%
 * @return		Error state 
 *			 - Returns an input error if power exceeds allotted range
 *			 - Returns a state error if motor is not in the idle
 *			   state
 */
MotorErr motor_startCW(Motor *m, uint16_t power) {
	if(!(m->state == IDLE || m->state == CLOCKWISE)) {
		log_error("Motor must already be turning clockwise or idle before being driven");
		return MOTOR_STATE_ERROR;
	}

	if(power > 10000 || power < 0) {
		log_error("Input power exceeds range");
		return MOTOR_INPUT_ERR;
	}

	// Change motor direction
	palClearLine(m->ccw);
	palSetLine(m->cw);

	// Sends pwm signals
	pwmEnableChannel(m->pwmd, m->channel, PWM_PERCENTAGE_TO_WIDTH(m->pwmd, abs(power)));

	// Updates motor object state 
	m->power = abs(power);	
	m->state = CLOCKWISE;
	
	return MOTOR_OK;
}

// DESIGN NOTE: Separate from startCW to enforce state changes
/**
 * @brief		Start motor going counter-clockwise at the given power 
 *			(converted to duty cycle for PWM)
 *
 * @pre			Motor is either already turning counter-clockwise or in its idle state
 *
 * @param m	    	Pointer to a Motor object
 * @param power		Ranges from 0 to 10000, as a percentage of the maximum duty cycle
 *			 - 4750 -> 47.5%; -10000 -> 100%
 * @return		Error state 
 *			 - Returns an input error if power exceeds allotted range
 *			 - Returns a state error if motor is not in the idle
 *			   state
 */
MotorErr motor_startCCW(Motor *m, uint16_t power) {
	if(!(m->state == IDLE || m->state == COUNTER_CLOCKWISE)) {
		log_error("Motor must already be turning counter-clockwise or idle before being driven");
		return MOTOR_STATE_ERROR;
	}

	if(power > 10000 || power < 0) {
		log_error("Input power exceeds range");
		return MOTOR_INPUT_ERR;
	}

	// Change motor direction
	palClearLine(m->cw);
	palSetLine(m->ccw);

	// Sends pwm signals
	pwmEnableChannel(m->pwmd, m->channel, PWM_PERCENTAGE_TO_WIDTH(m->pwmd, abs(power)));

	// Updates motor object state 
	m->power = abs(power);	
	m->state = COUNTER_CLOCKWISE;
	
	return MOTOR_OK;
}

/**
 * @brief		Start actively braking the motor
 *
 * @pre			Motor is in its idle state
 *
 * @param m		Pointer to a Motor object
 * @return		Error state
 */
MotorErr motor_brake(Motor *m) {
	if(!(m->state == IDLE || m->state == ACTIVE_BRAKE)) {
		log_error("Motor must be in its idle state before braking");
		return MOTOR_STATE_ERROR;
	}

	// Enable both switches on the H Bridge to brake
	palSetLine(m->cw);
	palSetLine(m->ccw);

	// TODO We do nothing about pwm currently; ensure this is fine when
	// testing

	// Update motor object state
	m->state = ACTIVE_BRAKE;

	return MOTOR_OK;
}

/**
 *  @brief		Disables the motor
 *  @note		Currently disables pwm signals but leaves timer on. 
 *			For extended periods of inactivity, disable the pwm 
 *			driver itself to conserve power.
 *
 *  @pre		Motor should be in its idle state before disabling. This
 *			ensures that the H Bridge controlling the motor is not being 
 *			actively driven while it gets forced into a sleep state.
 *
 *  @return		Error state
 */
MotorErr motor_disable(Motor *m) {
	if(motor->state != IDLE) {
		log_error("Motor must be in an idle state before disabling");
		return MOTOR_STATE_ERROR;
	}

	// Pull sleep line HIGH to disable H Bridge
	palSetLine(m->sleep);

	// Ensures the motor is in a known state when reenabling
	palClearLine(m->cw);
	palClearLine(m->ccw);

	// Turns off PWM for minor power conservation
	pwmDisableChannel(m->pwmd, m->channel);

	motor->state = DISABLED;	
	return MOTOR_OK;
}

/**
 *  @brief		Puts the motor into its idle state and enables it
 *  @note		Use to move between active states and prepare for
 *			active driving
 *  
 *  @pre		Motor is initialized
 */
MotorErr motor_ready(Motor *m) {
	// Check to make sure motor has been initialized
	if(m->state == UNINIT) {
		log_error("Motor has not been initialized!");
		return MOTOR_STATE_ERROR;
	}
	
	// Take H Bridge out of sleep mode
	palClearLine(m->sleep);
	
	// Keep CW and CCW pins are low to prevent undefined behavior 
	palClearLine(m->cw);
	palClearLine(m->cw);

	// Ensures lines are fully set before continuing
	chThdSleepMilliseconds(10);
	
	m->state = IDLE;
	return MOTOR_OK;
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
