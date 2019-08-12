#ifndef MOTOR_H
#define MOTOR_H

#include "hal.h"

typedef struct Motor {
	PWMDriver *pwmd;			// A pointer to the pwm driver
	pwmchannel_t channel;		// Uniquely identifies the motor, since multiple motors should share the same pwm driver
	const ioline_t pwm;			// References the line outputting a PWM signal to the motor (controlling power)
	const ioline_t dir;			// References the I/O line controlling the motor direction
	int power;					// Stores the absolute value of the last power value assigned to the motor
	bool dir;					// True if the motor was last assigned to move forward, false if backward
} Motor;

/*
 * @brief			Initializes and configures a motor object
 *
 * @param m			Pointer to a Motor object
 * @param pwmd		Pointer to a PWMDriver object mapped to the timer shared between the motors 
 * @param pwm		References the line controlling the power of the motor via a PWM signal
 * @param dir		References the line controlling the direction of the motor 
 * @param pwmc		Configuration of the PWM system (multiple motors may share this)
 */
void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, const ioline_t pwm, const ioline_t dir, const PWMConfig *pwmc);

/*
 * @brief			Start the motor or change speed to the given power (converted to duty cycle for PWM)
 *
 * @param m			Pointer to a Motor object
 * @param power		Ranges from -10000 to 10000, as a percentage of the maximum duty cycle
 *					Ex: 4750 -> 47.5%; -10000 -> 100%, reversed
 * @return			Error state (0 - SUCCESS, 1 - ERROR)
 *					Returns error if power exceeds allotted range
 */
int motor_start(Motor *m, int power);

/*
 *	@brief			Stops the motor
 *	@note			Currently disables pwm signals but leaves timer on. For extended periods of inactivity,
 *					disable the pwm driver itself to conserve power.
 */
int motor_stop(Motor *m);

/*
 * @brief			Getter for motor's power
 * 
 * @param m			Pointer to a Motor object
 * @return			Magnitude of last assigned power value
 */
int motor_getPower(Motor *m);

/*
 * @brief			Getter for motor's direction
 *
 * @param m			Pointer to a Motor object
 * @return			true if last assigned to go forward, false if not 
 */
bool motor_getDirection(Motor *m);


#endif  // MOTOR_H
