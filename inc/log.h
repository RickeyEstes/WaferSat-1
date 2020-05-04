/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 *
 * Modified by varun-iyer
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

#define LOG_VERSION "0.1.0"

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define log_trace(...)	log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)	log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)	log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)	log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)	log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...)	log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)


#define LED_OK() palSetPad(GPIOD, GPIOD_LED_GREEN)
#define LED_INFO() palSetPad(GPIOD, GPIOD_LED_BLUE)
#define LED_WARN() do{ palSetPad(GPIOD, GPIOD_LED_BLUE); palSetPad(GPIOD, GPIOD_LED_GREEN); } while(0)
#define LED_ERR() do { \
		 palSetPad(GPIOD, GPIOD_LED_RED); \
	 } while(0)
#define LED_FATAL() do { palSetPad(GPIOD, GPIOD_LED_RED); } while(1)
#define LED_CLEAR() do { \
		 palClearPad(GPIOD, GPIOD_LED_RED); \
		 palClearPad(GPIOD, GPIOD_LED_BLUE); \
		 palClearPad(GPIOD, GPIOD_LED_GREEN); \
	 } while(0)
#define log_ms() TIME_I2MS(chVTGetSystemTime())


#define LOG_MEM 0
#define LOG_SERIAL 1

#define log_printf

#define MAX_FILENAME 127
#define LOG_FILENAME "out.log"


#define LOG_LEVEL LOG_TRACE


#define LOG_USE_COLOR 0


#define LOG_SD SD1
static const SerialConfig LOG_CFG = {38400, 0, 0, 0};


void log_init(void);
void log_set_level(int level);
void log_log(int level, const char *file, int line, const char *fmt, ...);
uint8_t log_image(void);
uint8_t log_data(void);

#endif
