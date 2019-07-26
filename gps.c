#include "hal.h"
#include "hal_serial.h"
#include "gps.h"
#include "stdio.h"
#include "log.h"

uint8_t gps_init() {
	/**
	Initializes GPIO and SerialDriver to communicate with GPS.
	Returns 0 on success and 1 on failure.
	**/
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
	sdStart(&SD_GPS, &gps_conf);
	return (SD_GPS.state == SD_READY) ? 0 : 1;	
}

int gps_receive(uint8_t* buf, uint16_t buflen) {
	/**
	Receive a SerialDriver message from the GPS module.
	Return 0 upon success and a number according to the kind of failure.
	Error Codes:
		1 Failed to read start-of-sequence/no message available
		2 Msg too long/read buffer too small
		3 Incorrect checksum
		4 Failed to read end-of-sequence (message might still be okay)
	**/
	// Read start-of-sequence 
	uint8_t startbuf[GPS_START_LEN];
	uint8_t gpsbuf[100];
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t i = 0;
	while((	c = gps_get()) &&
			i < 100 &&
			!(b == 0xA0 &&
			c == 0xA1)) {
		b = c;
		gpsbuf[i] = c;
		i++;
	}
	if(i == 100) {
		log_message("Failed to receive start of sequence!", LOG_ERR);
		return -1;
	}
	 
	char log_msg[MAX_LOG_LEN];
	char* ptr = log_msg;
	ptr += snprintf(log_msg, log_msg + MAX_LOG_LEN - ptr, "Skipped: ");
	for(int q = 0; q < i; q++) {
		ptr += snprintf(ptr, log_msg + MAX_LOG_LEN - ptr, "%02X ", gpsbuf[q]);
	}
	log_message(log_msg, LOG_CRITICAL);
		
	// Read msg-length
	uint8_t msg_len_buf[2];
	uint16_t read = gps_read(msg_len_buf, 2);
	uint16_t msg_len = (msg_len_buf[0] << 8) | msg_len_buf[1];

	snprintf(log_msg, MAX_LOG_LEN, "Length: %u", msg_len);
	log_message(log_msg, LOG_CRITICAL);
	 
	if(read != 2) {
		log_message("Did not read payload length from GPS.", LOG_ERR);
		return -1;
	}
	if(msg_len > buflen) {
		log_message("GPS read buffer is too small.", LOG_ERR);
		return -2;
	}

	//read mesage
	read = gps_read(buf, msg_len);
	int bytes_read = read;
	if(read != msg_len) {
		log_message("Failed to read complete message from GPS.", LOG_ERR);
		return -1;
	}

	// read/verify checksum
	uint8_t recv_cs = gps_get();
	uint8_t calc_cs = 0;	
	for(int i = 0; i < msg_len; i++) calc_cs ^= buf[i];
	if(calc_cs != recv_cs) {
		log_message("Failed checksum verification of GPS message.", LOG_ERR);
	}
	
	// read end-of-sequence
	uint8_t endbuf[GPS_END_LEN];
	read = gps_read(endbuf, GPS_END_LEN);
	if(read != GPS_END_LEN || endbuf[0] != end_seq[0] || endbuf[1] != end_seq[1]) {
		snprintf(log_msg, MAX_LOG_LEN, "Read %02X %02X instead of 0x0D 0x0A.", endbuf[0], endbuf[1]);
		log_message(log_msg, LOG_ERR);
		return -1;
	}

	return bytes_read;
}

uint8_t gps_send(uint8_t* msg, uint16_t msg_len) {
	/**
	Transmit a message to the GPS according to the Skytraq binary protocol.
	The message **should include** the msg_id
	Return 0 on success, a number indicating position of failure upon failure
	**/
 
	// Transmit start-of-sequence to GPS
	int transmitted = gps_write(start_seq, GPS_START_LEN);
	if(transmitted != GPS_START_LEN) {
		log_message("Failed to write start-of-sequence to GPS.", LOG_ERR);
		return 1;
	}
 
	//transmit payload length
	//you need to add one to include the length of the message id
	uint8_t pl[] = {(uint8_t) (msg_len >> 8), (uint8_t) (msg_len & 0xFF)};
	transmitted = gps_write(pl, 2);
	if(transmitted != 2) {
		log_message("Failed to write payload length to GPS.", LOG_ERR);
		return 2;
	}

	//transmit message
	transmitted = gps_write(msg, msg_len);
	if(transmitted != msg_len) {
		log_message("Failed to write message to GPS.", LOG_ERR);
		return 4;
	}
 
	//transmit checksum
	uint8_t checksum = 0;
	for(int i = 0; i < msg_len; i++) checksum ^= msg[i];
	transmitted = gps_write(&checksum, 1);
	if(transmitted != 1) {
		log_message("Failed to write checksum to GPS.", LOG_ERR);
		return 5;
	}
 
	// Transmit end-of-sequence to GPS
	transmitted = gps_write(end_seq, GPS_END_LEN);
	if(transmitted != GPS_END_LEN) {
		log_message("Failed to write end-of-sequence to GPS.", LOG_ERR);
		return 6;
	}

	return 0;
}
 
uint8_t gps_ping() {	
	/**
	Asks the GPS its software version in order to confirm communication.
	0 if succesful comm, 1 if otherwise.
	**/ 
	uint8_t buf[GPS_MSG_SIZE];
	// Unique ID and payload for ping message
	uint8_t ping_msg[2] = {0x03, 0x00};
	uint8_t ping_len = 2;
	uint8_t err = gps_send(ping_msg, ping_len);
	if(err) return err;

	// This should return an ACK
	int bread = gps_all(buf, GPS_MSG_SIZE);
	if(bread < 0) {
		return 1;
	}
	char log_msg[MAX_LOG_LEN];
	char* ptr = log_msg;
	ptr += snprintf(ptr, log_msg + MAX_LOG_LEN - ptr, "Read from GPS: ");
	for(int q = 0; q < bread; q++) {
		ptr += snprintf(ptr, log_msg + MAX_LOG_LEN - ptr, "%02X ", buf[q]);
	}
	log_message(log_msg, LOG_VERBOSE);

	return 0;
}

uint16_t gps_all(uint8_t* msg, uint16_t max_len) {
	/**
		Reads all bytes from GPS and returns the number of bytes read.
	**/
	uint8_t c = 0;
	uint16_t i = 0;
	while((c = gps_get()) && i < max_len) {
		msg[i] = c;
		i++;
	}
	return i;
}	
 
uint8_t gps_listen() {	
	uint8_t buf[GPS_MSG_SIZE + 1];
	int bread = gps_all(buf, GPS_MSG_SIZE);
	buf[GPS_MSG_SIZE] = 0x00;
	if(bread < 0) {
		return 1;
	}
	char log_msg[MAX_LOG_LEN];
	char* ptr = log_msg;
	ptr += snprintf(ptr, log_msg + MAX_LOG_LEN - ptr, "Read %u characters from GPS: %s", bread, (char*) buf);
	/*
	for(int q = 0; q < bread; q++) {
		ptr += snprintf(ptr, log_msg + MAX_LOG_LEN - ptr, "%02X ", buf[q]);
	}
	*/
	log_message(log_msg, LOG_VERBOSE);

	return 0;
}
