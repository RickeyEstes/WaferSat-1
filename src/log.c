/*
 * Copyright (c) 2017 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Modified by varun-iyer for ChibiOS/MCU usage
 *
 *
 */

#include "hal.h"
#include "string.h"
#include "sd.h"
#include "chprintf.h"
#include "ov5640.h"
#include "ch.h"
#include "sensors/common.h"
#include "ff.h"
#include "log.h"

static struct {
	mutex_t mtx;
	char log_dirname[MAX_FILENAME];
	FIL fp;
	int level;
} L;


static const char *level_names[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#ifdef LOG_USE_COLOR
static const char *level_colors[] = {
	"\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif
#if LOG_MEM && LOG_SERIAL
#define lprintf(...) do{ \
		 chprintf((BaseSequentialStream*) &LOG_SD, __VA_ARGS__); \
		 f_printf(&(L.fp), __VA_ARGS__); \
	} while(0)
#elif LOG_MEM /* && !LOG_SERIAL */
#define lprintf(...) f_printf(&(L.fp), __VA_ARGS__)
#elif LOG_SERIAL /* && !LOG_MEM */
#define lprintf(...) chprintf((BaseSequentialStream*) &LOG_SD, __VA_ARGS__)
#else /* !LOG_MEM && !LOG_SERIAL */
#define lprintf(...) do{ } while(0)
#endif /* LOG_MEM && LOG_SERIAL */

void log_init(void) {
	chMtxObjectInit(&(L.mtx));
#if LOG_MEM
	// TODO name log with gps date
	FRESULT mk_err = 1;
	int test_no = 0;
	// Find unique directory
	while(mk_err && test_no < 100000) {
		chsnprintf(L.log_dirname, MAX_FILENAME, "test%d", test_no);
		mk_err = f_mkdir(L.log_dirname);
		test_no++;
	}
	if(mk_err != 0) {
		LED_ERR();
		// return mk_err;
	}
	
	char log_filename[MAX_FILENAME];
	chsnprintf(log_filename, MAX_FILENAME, "%s/%s", L.log_dirname, LOG_FILENAME);
 
	FRESULT f_err;
	f_err = f_open(&(L.fp), log_filename, FA_CREATE_NEW);
	if(f_err) {
		LED_ERR();
		//TODO error handling system
		// return f_err;
	}
	f_err = f_close(&(L.fp));
	if(f_err) {
		LED_ERR();
		// return f_err;
	}
	f_err = f_open(&(L.fp), log_filename, FA_WRITE);
	if(f_err) {
		LED_ERR();
		// return f_err;
	}
#endif /* LOG_MEM */
#if LOG_SERIAL
	sdStart(&LOG_SD, &LOG_CFG);
#endif /* LOG_SERIAL */

	log_set_level(LOG_LEVEL);
}


void log_set_level(int level) {
	L.level = level;
}

void log_data(void) {

	char log[1024];
	sensor_hnprintf(log, 1024);
	
	chMtxLock(&(L.mtx));
	long int ms = log_ms();
	long int s = (ms / 1000) % 60;
	long int m = (ms / (60 * 1000)) % 60;
	long int h = ms / (3600 * 1000);
	ms = ms % 1000;
	
	lprintf("%li:%02li:%02li.%03li DATA:\r\n", h, m, s, ms);
	lprintf(log);
	lprintf("\r\n");
	
#if LOG_MEM
	f_sync(&(L.fp));
#endif /* LOG_MEM */
	chMtxUnlock(&(L.mtx));
}

void log_image(void) {
#if LOG_MEM
	chMtxLock(&(L.mtx));
	uint32_t time_s = log_ms()/1000;
	char image_filename[MAX_FILENAME];
	chsnprintf(image_filename, MAX_FILENAME, "%s/img%d.jpg", L.log_dirname, time_s);
	uint32_t err = OV5640_Snapshot2SD(image_filename);
	if(err == FR_EXIST) {
		int img_num = 0;
		while(err == FR_EXIST && img_num++ < 1000) {
			chsnprintf(image_filename, MAX_FILENAME, "%s/img%d_%d.jpg", L.log_dirname, time_s, img_num);
			err = OV5640_Snapshot2SD(image_filename);
		}
	}
	chMtxUnlock(&(L.mtx));
#else /* !LOG_MEM */
	log_warn("Did not save camera data because logging to memory is disabled!");
#endif /* LOG_MEM */
	return;
}

/**
* Logs an array of values to serial or to memory.
* @param buf	the buffer to log
* @param size	size of each buf member in bytes
* @param buflen	the length of the buffer
* @param fmt	format string. the last formatting sign (%...\0) is assumed to be
* 	the formatting of each value in the buffer. Can also contain regular printf
* 	formatting.
*/
void log_buf(int level, const char *file, int line, void *buf, size_t size,
	size_t buflen, const char *fmt, ...) {
  /* Acquire lock */
	chMtxLock(&(L.mtx));
  /* Get current time */
	long int ms = log_ms();
	long int s = (ms / 1000) % 60;
	long int m = (ms / (60 * 1000)) % 60;
	long int h = ms / (3600 * 1000);
	ms = ms % 1000;
	va_list args;
	char* buf_fmt = rindex(fmt, '%');

	uint8_t *bytes = (uint8_t*) buf;

	*buf_fmt = '\0';

#if LOG_SERIAL
	if (level >= L.level) {
#if LOG_USE_COLOR
		chprintf(
			(BaseSequentialStream*) &SD1,
			"%li:%02li:%02li.%03li\t%-5s\x1b[0m \x1b[90m%\ts:%d:\x1b[0m\t",
			h, m, s, ms, level_colors[level], level_names[level], file, line
		);
#else /* !LOG_USE_COLOR */
		chprintf((BaseSequentialStream*) &SD1,
			"%li:%02li:%02li.%03li\t%-5s\t%s:%d:\t",
			h, m, s, ms, level_names[level], file, line
		);
#endif /* LOG_USE_COLOR */
		va_start(args, fmt);
		chvprintf((BaseSequentialStream*) &SD1, fmt, args);
		va_end(args);
		*buf_fmt = '%';
		for(size_t i = 0; i < buflen; i++) {
			chprintf((BaseSequentialStream*) &SD1, buf_fmt,
				*(bytes + (i * size)));
		}
		chprintf((BaseSequentialStream*) &SD1, "\n\r");
	}
#endif /* LOG_SERIAL */

  /* Log to file */
#if LOG_MEM
    f_printf(
		&(L.fp), "%li:%02li:%02li.%03li\t%-5s\t%s:%d:\t",
		h, m, s, ms, level_names[level], file, line
	);
    va_start(args, fmt);
    f_vprintf(&(L.fp), fmt, args);
    va_end(args);
	*buf_fmt = '%';
	for(size_t i = 0; i < buflen; i++) {
		f_printf(&(L.fp), buf_fmt, *(bytes + (i * size)));
	}
    f_printf(&(L.fp), "\n");
    f_sync(&(L.fp));
#endif /* LOG_MEM */

  /* Release lock */
	chMtxUnlock(&(L.mtx));
}

void log_log(int level, const char *file, int line, const char *fmt, ...) {
  /* Acquire lock */
	chMtxLock(&(L.mtx));
  /* Get current time */
	long int ms = log_ms();
	long int s = (ms / 1000) % 60;
	long int m = (ms / (60 * 1000)) % 60;
	long int h = ms / (3600 * 1000);
	ms = ms % 1000;
	va_list args;
	 
#if LOG_SERIAL
	if (level >= L.level) {
#if LOG_USE_COLOR
		chprintf(
			(BaseSequentialStream*) &SD1,
			"%li:%02li:%02li.%03li\t%-5s\x1b[0m \x1b[90m%\ts:%d:\x1b[0m\t",
			h, m, s, ms, level_colors[level], level_names[level], file, line
		);
#else /* !LOG_USE_COLOR */
		chprintf((BaseSequentialStream*) &SD1,
			"%li:%02li:%02li.%03li\t%-5s\t%s:%d:\t",
			h, m, s, ms, level_names[level], file, line
		);
#endif /* LOG_USE_COLOR */
		va_start(args, fmt);
		chvprintf((BaseSequentialStream*) &SD1, fmt, args);
		va_end(args);
		chprintf((BaseSequentialStream*) &SD1, "\n\r");
	}
#endif /* LOG_SERIAL */

  /* Log to file */
#if LOG_MEM
    f_printf(
		&(L.fp), "%li:%02li:%02li.%03li\t%-5s\t%s:%d:\t",
		h, m, s, ms, level_names[level], file, line
	);
    va_start(args, fmt);
    f_vprintf(&(L.fp), fmt, args);
    va_end(args);
    f_printf(&(L.fp), "\n");
    f_sync(&(L.fp));
#endif /* LOG_MEM */

  /* Release lock */
	chMtxUnlock(&(L.mtx));
}
