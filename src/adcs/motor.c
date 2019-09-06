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
 * @brief		Start the motor or change speed to the given power (converted to duty cycle for PWM)
 *
 * @param m	    	Pointer to a Motor object
 * @param power		Ranges from -10000 to 10000, as a percentage of the maximum duty cycle
 *			 - 4750 -> 47.5%; -10000 -> 100%, reversed
 * @return		Error state 
 *			 - Returns an input error if power exceeds allotted range
 *			 - Returns a state error if motor is not in the idle
 *			   state
 */
int motor_start(Motor *m, int power) {
	if(m->state != IDLE) {
		log_error("Motor must be in an idle state before being driven");
	}

	if(abs(power) > 10000) {
		return MOTOR_INPUT_ERR;
	}

	// TODO Change motor direction based on power	

	// Sends pwm signals
	pwmEnableChannel(m->pwmd, m->channel, PWM_PERCENTAGE_TO_WIDTH(m->pwmd, abs(power)));

	// Updates motor object state 
	// TODO Change motor state field
	m->power = abs(power);	
	m->dir = power > 0;
	
	return 0;
}

/**
 * @brief		Put the motor into its idle state.
 * @note		This prepares the motor for active driving. 
 *
 * @param m		Pointer to a Motor object
 */
MotorErr motor_idle(Motor *m) {
	if(motor->state = UNINIT) {
		
	}
}

/**
 *  @brief		Disables the motor
 *  @note		Currently disables pwm signals but leaves timer on. For extended periods of inactivity,
 *			disable the pwm driver itself to conserve power.
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
 *  @brief		Enables the motor
 *  @note		Puts the motor into its idle state, making it ready to
 *			be actively driven
 *  
 *  @pre		Motor is initialized
 */
MotorErr motor_enable(Motor *m) {
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
	
	// TODO Start PWM timer, with a duty cycle of 0
	
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
