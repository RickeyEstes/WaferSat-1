#ifndef __GPS_H__
#define __GPS_H__
#include "hal.h" 
#include "hal_serial.h"
#include "stdio.h"

#define SD_GPS SD2
#define GPS_TIMEOUT TIME_MS2I(50)
#define GPS_LOOPOUT 50
#define GPS_MSG_SIZE 1024

static const SerialConfig gps_conf = {9600, 0, 0, 0};

static const uint8_t start_seq[] = {0xA0, 0xA1};
#define GPS_START_LEN 2
static const uint8_t end_seq[] = {0x0D, 0x0A};
#define GPS_END_LEN 2
#define GPS_ACK_ID 0x83

#define gps_read(buf, len) sdReadTimeout(&SD_GPS, buf, len, GPS_TIMEOUT)
#define gps_write(buf, len) sdWriteTimeout(&SD_GPS, buf, len, GPS_TIMEOUT)
#define gps_getc() sdGetTimeout(&SD_GPS, GPS_TIMEOUT)
#define gps_putc(c) sdPutTimeout(&SD_GPS, c, GPS_TIMEOUT)
// Scan definitions for GPS message types
#define gps_data_fields(data) 	(data)->dd, (data)->mm, (data)->yyyy, \
	(data)->time, (data)->lat, (data)->ns, \
	(data)->lon, (data)->ew, (data)->alt, \
	(data)->fix, (data)->satellites, \
	(data)->dilution, (data)->ms, (data)->err

// FIXME rename macros in gps.c and h instead of hiding them
#define GPS_T_FIELDS gps_data_fields

/*
	$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
		GGA          Global Positioning System Fix Data
		123519       Fix taken at 12:35:19 UTC
		4807.038,N   Latitude 48 deg 07.038' N
		01131.000,E  Longitude 11 deg 31.000' E
		1            Fix quality:
						0 = invalid     1 = GPS fix (SPS)       2 = DGPS fix
						3 = PPS fix     4 = Real Time Kinematic 5 = Float RTK
						6 = estimated   7 = Manual input mode   8 = Simulation mode
		08           Number of satellites being tracked
		0.9          Horizontal dilution of position
		545.4,M      Altitude, Meters, above mean sea level
		46.9,M       Height of geoid (mean sea level) above WGS84 ellipsoid
		(empty field) time in seconds since last DGPS update
		(empty field) DGPS station ID number
		*47          the checksum data, always begins with *
*/
#define gps_scan_gga(buf, data) sscanf( \
		buf, "$GNGGA,%lf,%lf,%c,%lf,%c,%u,%u,%lf,%lf,M,%*s,M,%*s,%*s*%*s", \
		&((data)->time), &((data)->lat), &((data)->ns), &((data)->lon), \
		&((data)->ew), (unsigned int*) &((data)->fix), \
		(unsigned int*) &((data)->satellites),  &((data)->dilution), \
		&((data)->alt) \
	)

#define gps_scan_zda(buf, data) sscanf( \
		buf, "$GNZDA,%lf,%u,%u,%u,%*s,%*s)", &(((data))->time), \
		(unsigned int*) &(((data)->dd)), (unsigned int*) &(((data)->mm)), \
		(unsigned int*) &(((data)->yyyy)) \
	)

#define GPS_HUMAN_STR "dd:%u mm:%u yyyy:%u time:%f lat:%fdeg%c lon:%fdeg%c alt:%f fix:%u sat:%u dil:%f ms:%lu err:%u"
#define GPS_CSV_STR "%u,%u,%u,%f,%f,%c,%f,%c,%f,%u,%u,%f,%lu,%u"
		 
// Returns a new struct with values from the one passed in
#define gps_data_cpy(data) ((struct gps_t){ gps_data_fields(data) })

#include "sensors/common.h"

/**
 * @brief GPS Fix status
 */
enum gps_fix_t {
	GPS_FIX_NONE,
	// ~100yard precision
	GPS_FIX_SPS,
	// Regular GPS
	GPS_FIX_GPS
};

/**
 * @struct  gps_t
 * @brief   Stores Global Positioning System (GPS) data
 * @note    Time is in UTC
 */
struct gps_t {
	//TODO we can probably get even more 
	// ddmmyyyy
	uint8_t dd;								/**< Day */
	uint8_t mm;								/**< Month */
	uint16_t yyyy;							/**< Year */
	// UTC hhmmss.ss
	double time;							/**< UTC time in hhmmss.ss */
	double lat;								/**< Latitude */
	char ns;								/**< North/South */
	double lon;								/**< Longitude */
	char ew;								/**< East/West */
	double alt;								/**< Altitude */
	enum gps_fix_t fix;						/**< GPS Fix status */
	uint8_t satellites; 					/**< Number of satellites */
	double dilution;						/**< Dilution of precision */
	uint32_t ms;							/**< time of last position update*/
	enum SensorErr err;
};
#define gps_data_init() ((struct gps_t){0, 0, 0, 0.0, 0.0, '0', 0.0, '0', \
	0.0, GPS_FIX_NONE, 0, 0.0, 0, SENSOR_OK})

// TODO remove GPS error enum

// All error bits
#define GPS_ERR_MSK (GPS_INV | GPS_BAD_CS | GPS_BAD_TYPE)
// all message bits
#define GPS_MSG_MSK (GPS_ZDA | GPS_GGA)

enum SensorErr gps_init(void);
struct gps_t gps_get(void);

#endif
