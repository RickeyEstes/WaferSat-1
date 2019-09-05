#ifndef __IMG_H__
#define __IMG_H__

#include "ch.h"
#include "hal.h"
#include "types.h"

typedef struct {
	uint16_t packet_id;
	uint8_t image_id;
	bool n_done;
} ssdv_packet_t;

extern ssdv_packet_t packetRepeats[16];
extern bool reject_pri;
extern bool reject_sec;

void start_image_thread(img_app_conf_t *conf);
uint32_t takePicture(uint8_t* buffer, uint32_t size, resolution_t resolution, bool enableJpegValidation);
extern mutex_t camera_mtx;
extern uint32_t gimage_id;

#endif

