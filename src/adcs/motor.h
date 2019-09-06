#ifndef MOTOR_H
#define MOTOR_H

#include "ch.h"
#include "hal.h"

typedef enum MotorState {
	UNINIT,			// Motor has not yet been initialized
	DISABLED,		// In low power mode
	CLOCKWISE,	    	// Actively turning clockwise
	COUNTER-CLOCKWISE,  	// Actively turning counter-clockwise
	ACTIVE_BRAKE,	    	// Actively stopping the motor
	IDLE		    	// No work being put into motor, but PWM is enabled 
} MotorState; 

typedef enum MotorErr {
	MOTOR_OK,
	MOTOR_STATE_ERR,	// Motor is not in a valid state to perform 
				// the desired operation
	MOTOR_INPUT_ERR		// Motor operation was given an invalid input
} MotorErr;

typedef struct Motor {
	/*
	 *  A pointer to the pwm driver
	 */
	PWMDriver *pwmd;

	/*
	 *  Uniquely identifies the motor, since multiple motors should share 
	 *  the same pwm driver
	 */
	pwmchannel_t channel;	

	/*
	 *  References the line outputting a PWM signal to the 
	 *  motor (controlling power)
	 */
	ioline_t pwm;

	/*
	 *  References the CLOCKWISE line on the H Bridge controlling the 
	 *  motor's direction
	 */
	ioline_t cw;

	/*
	 *  References the COUNTER-CLOCKWISE line on the H Bridge controlling 
	 *  the motor's direction
	 */
	ioline_t ccw;

	/*
	 *  Enables/Disables the H Bridge (active low)
	 */
	ioline_t sleep;
	/*
	 *  Stores the absolute value of the last power value assigned 
	 *  to the motor
	 */
	int power;			/// TODO Necessary?
	
	/*
	 * Represents the current state of the motor
	 */
	MotorState state;			
} Motor;

void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, ioline_t pwm,
    ioline_t cw, ioline_t ccw, const PWMConfig *pwmc);

int motor_startCW(Motor *m, int power);

int motor_startCCW(Motor *m, int power);

int motor_brake(Motor *m);

int motor_ready(Motor *m);

int motor_stop(Motor *m);

int motor_getPower(Motor *m);

bool motor_getDirection(Motor *m);


#endif  // MOTOR_H
