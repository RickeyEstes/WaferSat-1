#ifndef __TRACE_H__
#define __TRACE_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "ptime.h"
#include "config.h"
#include <string.h>

#define SD_console		SD1
#define ERROR_LIST_LENGTH	64
#define ERROR_LIST_SIZE		32
#define TRACE_TIME	    FALSE
#define TRACE_FILE	    FALSE

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

extern char error_list[ERROR_LIST_SIZE][ERROR_LIST_LENGTH];
extern uint8_t error_counter;
extern uint8_t usb_trace_level;

#define TRACE_DEBUG(...) do { if(usb_trace_level > 4) { debug_print("DEBUG", __FILE__, __LINE__, \
    __VA_ARGS__); } } while(0)
#define TRACE_INFO(...) do { if(usb_trace_level > 3) { debug_print("     ", __FILE__, __LINE__, \
    __VA_ARGS__); } } while(0)
#define TRACE_MON(...)  do { if(usb_trace_level > 2) { debug_print("     ", __FILE__, __LINE__, \
    __VA_ARGS__ ); } } while(0)
#define TRACE_WARN(...)  do { if(usb_trace_level > 1) { debug_print("WARN ", __FILE__, __LINE__, __VA_ARGS__); } } while(0)
#define TRACE_ERROR(...) do { \
	if(usb_trace_level > 0) { \
		debug_print("ERROR", __FILE__, __LINE__, __VA_ARGS__); \
	} \
	\
	uint8_t strcnt = chsnprintf(error_list[error_counter], ERROR_LIST_LENGTH, "[%8d.%03d] ", chVTGetSystemTime()/CH_CFG_ST_FREQUENCY, (chVTGetSystemTime()*1000/CH_CFG_ST_FREQUENCY)%1000); \
	chsnprintf(&error_list[error_counter][strcnt], ERROR_LIST_LENGTH-strcnt, __VA_ARGS__); \
	error_counter = (error_counter+1)%ERROR_LIST_SIZE; \
} while(0)

#if TRACE_TIME && TRACE_FILE
#define TRACE_TAB "                                               "
#elif TRACE_TIME && !TRACE_FILE
#define TRACE_TAB "                            "
#elif !TRACE_TIME && TRACE_FILE
#define TRACE_TAB "                               "
#else
#define TRACE_TAB "              "
#endif


/*
#if USE_CCM_FOR_PKT_POOL == TRUE

static inline struct pool_header *pktSystemCheck(void) {
  extern guarded_memory_pool_t *ccm_pool;
  return ((struct pool_header *)(ccm_pool->pool.next))->next;
}
#elif USE_CCM_HEAP_FOR_PKT ==  TRUE
*/
#if USE_CCM_HEAP_FOR_PKT ==  TRUE
/*
 * Memory heap integrity checking...
 */
static inline heap_header_t *pktSystemCheck(void) {
  extern memory_heap_t *ccm_heap;
  return (heap_header_t *)(ccm_heap->header.free).next;
}
#endif

void debug_init(void);
void debug_print(char *type, char* filename, uint32_t line, char* format, ...);

#endif /* __TRACE_H__ */

