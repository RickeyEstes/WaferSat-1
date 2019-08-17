#include "hal.h"
#include "hal_serial.h"
#include "sensors/gps.h"
#include "stdio.h"
#include "string.h"
#include "log.h"
 
static volatile struct gps_t gps_protected;
static mutex_t gps_mtx;

/**
* @brief			Thread safe write of stored values.
* @param data		Pointer to gps data struct
* @see				struct gps_t
*/
static void gps_set(struct gps_t *data) {
	chMtxLock(&gps_mtx);
	chSysLock();
	gps_protected = gps_data_cpy(data);
	chSysUnlock();
	chMtxUnlock(&gps_mtx);
}

/**
* @brief		Thread safe read of stored values.
* @return		Stored struct.
*/
struct gps_t gps_get() {
	chMtxLock(&gps_mtx);
	chSysLock();
	struct gps_t data = gps_data_cpy(&gps_protected);
	chSysUnlock();
	chMtxUnlock(&gps_mtx);
	return data;
}
 
/**
* @brief			Reads one line of GPS output into the given buffer
*
* @param buf		Buffer being read into
* @param maxlen	Maximum length of message
* @return			Number of bytes read
*/
static uint16_t gps_readline(char* buf, uint16_t maxlen) {
	char* ptr = buf;
	while(ptr < buf + maxlen && (*ptr = gps_getc()) && *ptr != '\n') if(*ptr != 0xFF) ptr++;
	*ptr = '\0';
	return ptr - buf;
}

/**
* @brief		Calculates the GPS checksum
*
* @param buf	Buffer containing input to checksum
* @return		GPS_OK if valid and GPS_INV if no delims ($ and *) are found 
* 	and GPS_BAD_CS if checksum is wrong
*/
static enum SensorErr gps_checksum(char* buf) {
	char* start = strchr(buf, (int)'$');
	char* end = strchr(buf, (int)'*');
	if(start == NULL || end == NULL) return SENSOR_INV_RESP;
	// We want to be just inside the $ and *
	char calc_cs = 0;
	char* ptr = start;
	// XOR every message character
	while(++ptr < end) calc_cs ^= *ptr;
	// Scan checksum from string
	unsigned int recv_cs;
	int matches = sscanf(end, "*%x", &recv_cs);
	if(matches != 1) {
		return SENSOR_INV_RESP;
	}

	if((uint8_t)recv_cs != (uint8_t) calc_cs) return SENSOR_INV_CS;
	return SENSOR_OK;
}

/**
* @brief		Parse an NMEA line into GPS data.
*
* @param buf	NMEA message
* @param data	GPS Data struct to be filled
* @return		Error code and type of message parsed
* 	if there is a parsing error, leave the GPS data untouched
*/
static enum SensorErr gps_parse(char *buf, struct gps_t *data) {
	enum SensorErr cs = gps_checksum(buf);
	if(cs != SENSOR_OK) {
		return cs;
	}
	struct gps_t test = gps_data_init();
	int found = gps_scan_gga(buf, &test);
	if(found == 9) {
		gps_scan_gga(buf, data);
		data->ms = log_ms();
		return SENSOR_OK;
	}
	found = gps_scan_zda(buf, &test);
	if(found == 4) {
		gps_scan_zda(buf, data);
		return SENSOR_OK;
	}
	return SENSOR_INV_RESP;
}

static THD_WORKING_AREA(gps_serial_wa, GPS_MSG_SIZE * 4);
static THD_FUNCTION(gps_serial_fn, args) {
	while(true) {
		// TODO use events instead of continuous poll
		char line[GPS_MSG_SIZE];
		gps_readline(&line, GPS_MSG_SIZE);
		struct gps_t data = gps_get();
		enum SensorErr err = gps_parse(line, &data);
		if(err == SENSOR_OK) {
			log_trace("Succesfully updated GPS data " GPS_HUMAN_STR,
				GPS_T_FIELDS(&data));
			gps_set(&data);
		}
	}
}
static thread_t* gps_serial_thd;

/**
* @brief	    Initializes GPIO and SerialDriver to communicate with GPS.
*
* @return	    0 on success and 1 on failure.
*/
enum SensorErr gps_init(void) {
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
	sdStart(&SD_GPS, &gps_conf);
	chMtxObjectInit(&gps_mtx);
	struct gps_t data = gps_data_init();
	gps_set(&data);
	gps_serial_thd = chThdCreateStatic(gps_serial_wa, sizeof(gps_serial_wa),
		NORMALPRIO, gps_serial_fn, NULL);
	if(SD_GPS.state == SD_READY) {
		log_trace("Successfully initialized GPS Serial Driver!");
		return SENSOR_OK;
	}
	log_error("Failed to initialize GPS Serial Driver!");
	return SENSOR_COMM_ERR;
}
