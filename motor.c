#ifndef MOTOR_C
#define MOTOR_C

void motor_init(Motor *m, PWMDriver *pwmd, pwmchannel_t channel, const ioline_t pwm, const ioline_t dir, const PWMConfig *pwmc) {
	// Init motor object
	m->pwmd = pwmd;  
	m->channel = channel;
	m->pwm = pwm;
	m->dir = dir;
	
	// TODO 
	// Right now the pwm pin is arbitrarily set to AF1 (alternate function 1) to connect to timers 1 and 2
	// If that should change, set to AF2 for timers 3, 4, 5 or AF3 for timers 8, 9, 10, 11
	palSetMode(pwm, PAL_MODE_ALTERNATE(1));
	palSetMode(dir, PAL_MODE_OUTPUT_PUSHPULL);	
	
	// Ensures that the pwm driver only gets activated once, to avoid disabling the other channels
	if(pwmd->state != PWM_READY) {
		pwmStart(pwmd, pwmc);	
	}
	
}

int motor_start(Motor *m, int power) {
	if(abs(power) > 10000) {
		return 1;	
	}

	// Assigns HIGH to forward and LOW to backwards
	if(power > 0) {
		palSetLine(dir, PAL_HIGH);
	} else {
		palSetLine(dir, PAL_LOW);
	}

	// Sends pwm signals
	pwmEnableChannel(m->pwmd, m->channel, PWM_PERCENTAGE_TO_WIDTH(abs(power)));

	// Updates motor object state 
	m->power = abs(power);	
	m->dir = power > 0;
	
	return 0;
}

int motor_stop(Motor *m) {
	pwmDisableChannel(m->pwmd, m->channel);
}

int motor_getPower(Motor *m) {
	return m->power;
}

int motor_getDirection(Motor *m) {
	return m->dir;
}


#endif	// MOTOR_C
