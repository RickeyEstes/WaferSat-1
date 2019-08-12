#ifndef MOTOR_H
#define MOTOR_H

#include "ch.h"
#include "hal.h"

typedef struct Motor {
	PWMDriver *pwmd;		// A pointer to the pwm driver
	pwmchannel_t channel;		// Uniquely identifies the motor, since multiple motors should share the same pwm driver
	ioline_t pwm;			// References the line outputting a PWM signal to the motor (controlling power)
	ioline_t dir;			// References the I/O line controlling the motor direction
	int power;			// Stores the absolute value of the last power value assigned to the motor
	bool last_dir;			// True if the motor was last assigned to move forward, false if backward
} Motor;

void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, ioline_t pwm, ioline_t dir, const PWMConfig *pwmc);

int motor_start(Motor *m, int power);

int motor_stop(Motor *m);

int motor_getPower(Motor *m);

bool motor_getDirection(Motor *m);


#endif  // MOTOR_H
