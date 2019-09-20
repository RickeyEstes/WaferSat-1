#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "portab.h"
#include "stdio.h"

#define SD_console	    SD1

mutex_t mtx; // Used internal to synchronize multiple chprintf in debug.h

char error_list[ERROR_LIST_SIZE][ERROR_LIST_LENGTH];
uint8_t error_counter;

static const SerialConfig debug_config = {
	38400,
	0,
	0,
	0
};

#ifdef USB_TRACE_LEVEL
uint8_t usb_trace_level = USB_TRACE_LEVEL; // Set in makefile UDEFS
#else
uint8_t usb_trace_level = 5; // Level: Print all 
#endif


void debug_init(void) {
	chMtxObjectInit(&mtx);

	sdStart(&SD_console, &debug_config);
	palSetLineMode(LINE_IO_TXD, PAL_MODE_ALTERNATE(7));
	palSetLineMode(LINE_IO_RXD, PAL_MODE_ALTERNATE(7));
}

void debug_print(char *type, char* filename, uint32_t line, char* format, ...)
{
	chMtxLock(&mtx);

	uint8_t str[256];

	va_list args;
	va_start(args, format);

	// We can get away with using stdlib since we're just writing to a buffer
	vsnprintf((char*)str, sizeof(str), format, args);

	va_end(args);

	chprintf((BaseSequentialStream*)&SD_console, "[%s]", type);
	chprintf((BaseSequentialStream*)&SD_console, " %s\r\n", str);
	chMtxUnlock(&mtx);
}

