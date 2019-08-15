#ifndef __CAMERA_TYPES_H__
#define __CAMERA_TYPES_H__

#include "ch.h"

//OV5640
typedef enum {
	RES_NONE = 0,
	RES_QQVGA,
	RES_QVGA,
	RES_VGA,
	RES_VGA_ZOOMED,
	RES_XGA,
	RES_UXGA,
	RES_5MP,
	RES_MAX
} resolution_t;


#endif /* __CAMERA_TYPES_H__ */

