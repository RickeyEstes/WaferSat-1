#ifndef MOTOR_H
#define MOTOR_H

#include "hal.h"

typedef struct Motor {
	PWMDriver *pwmd;		// A pointer to the pwm driver
	pwmchannel_t channel;		// Uniquely identifies the motor, since multiple motors should share the same pwm driver
	const ioline_t pwm;		// References the line outputting a PWM signal to the motor (controlling power)
	const ioline_t dir;		// References the I/O line controlling the motor direction
	int power;			// Stores the absolute value of the last power value assigned to the motor
	bool dir;			// True if the motor was last assigned to move forward, false if backward
} Motor;

void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, const ioline_t pwm, const ioline_t dir, const PWMConfig *pwmc);

int motor_start(Motor *m, int power);

int motor_stop(Motor *m);

int motor_getPower(Motor *m);

bool motor_getDirection(Motor *m);


#endif  // MOTOR_H
