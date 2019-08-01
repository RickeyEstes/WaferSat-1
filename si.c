#include "ch.h"
#include "hal.h"
#include "hal_spi.h"
#include "si.h"
#include "si_cmd.h"
#include "log.h"
#include "si_prop.h" 

si_err_t si_spi(const uint8_t* tx_buf, size_t tx_len, uint8_t* rx_buf, size_t rx_len) {
    // Thread lock SPI driver
    spiAcquireBus(&SI_SPID);
	 
    uint8_t rx_ready = SI_CMD_READ_CMD_BUFF;
    uint8_t cts = 0;

    // Poll radio's command buffer for CTS signal
    for(unsigned int i = 0; i < SI_TIMEOUT; i++) {
		spiSelect(&SI_SPID);
        spiExchange(&SI_SPID, 1, &rx_ready, &cts);
		spiUnselect(&SI_SPID);
        // Break when the microcontroller sends CTS
        if(cts == 0xFF) {
            break;
        }
        chThdSleep(TIME_MS2I(1));
	}
	if(cts != 0xFF) {
		spiReleaseBus(&SI_SPID);
		log(ERR, "Timed out while sending command: ");
		for(unsigned int q = 0; q < tx_len; q++) log(ERR, "%02X ", tx_buf[q]);
		log(ERR, "\n\r");
        return SI_ERR_TIMEOUT;
    } 

	//Send TX buffer
	spiSelect(&SI_SPID);
	spiSend(&SI_SPID, tx_len, tx_buf);
	spiUnselect(&SI_SPID);
	 
	// Poll for CTS again, which will come when the rx buffer is full
	cts = 0;
	for(unsigned int i = 0; i < SI_TIMEOUT; i++) {
		chThdSleep(TIME_MS2I(1));
		spiSelect(&SI_SPID);
		spiExchange(&SI_SPID, 1, &rx_ready, &cts);
		spiUnselect(&SI_SPID);
		if(cts == 0xFF) {
			break;
		}
	}
	if(cts != 0xFF) {
		spiReleaseBus(&SI_SPID);
		log(ERR, "Timed out while waiting for reply after: ");
		for(unsigned int q = 0; q < tx_len; q++) log(ERR, "%02X ", tx_buf[q]);
		log(ERR, "\n\r");
        return SI_ERR_TIMEOUT;
    } 

	for(unsigned int i = 0; i < SI_TIMEOUT; i++) {
		chThdSleep(TIME_MS2I(1));
		spiSelect(&SI_SPID);
		//FIXME sktch af
		uint8_t rx_extra[rx_len + 1];
		spiExchange(&SI_SPID, rx_len + 1, &rx_ready, rx_extra);
		spiUnselect(&SI_SPID);
		for(unsigned int j = 0; j < rx_len; j++) {
			rx_buf[j] = rx_extra[j + 1];
		}
		if(rx_buf[0] == 0xFF) {
			break;
		}
		chThdSleep(TIME_MS2I(1));
	}
	log(VRB, "Transmitted: ");
	for(unsigned int q = 0; q < tx_len; q++) log(VRB, "%02X ", tx_buf[q]);
	log(VRB, "\n\rReceived: ");
	for(unsigned int q = 0; q < rx_len; q++) log(VRB, "%02X ", rx_buf[q]);
	log(VRB, "\n\r");
	 
    spiReleaseBus(&SI_SPID);
    return SI_ERR_SUCCESS;
}

si_err_t si_get_prop(si_prop_t prop, uint32_t* value, size_t len) {
	/*
	Get a config property on the SI4464.
		@arg prop 	property from the enum defined in si_prop.h
		@arg value 	memory to store value of property
		@arg len	length of property in bits (e.g. 8, 16, 32). 
	Returns err/success
	*/
	//Round len up to nearest multiple of, then convert to bytes
	len = (len + 7) / 8;
	if(len < 1 || len > 4) {
		log(ERR, "Invalid length when attempting to set property.");
		return SI_ERR_INV_ARG;
	}
	//Need room for command, group, number of properties, and property + the actual values
	uint8_t message[4];
	message[0] = SI_CMD_GET_PROPERTY;
	message[1] = SI_GRP(prop);
	message[2] = (uint8_t) len;
	message[3] = SI_PROP(prop);
	uint8_t reply[len + 1];
	si_err_t err = si_spi(message, 4, reply, len + 1);
	*value = 0;
	//Skip the first value of reply because it’s CTS
	for(size_t i = 0; i < len; i++) {
		*value |= (reply[i + 1] << ((len - i - 1) * 8));
	}	
	return err;
}

si_err_t si_set_prop(si_prop_t prop, uint32_t value, size_t len) {
	/*
	Set a config property on the SI4464.
		@arg prop 	property from the enum defined in si_prop.h
		@arg value 	desired value to set the property to
		@arg len	length of property in bits (e.g. 8, 16, 32). 
	Returns err/success
	*/
	//Round len up to nearest multiple of, then convert to bytes
	len = (len + 7) / 8;
	if(len < 1 || len > 4) {
		log(ERR, "Invalid length when attempting to set property.");
		return SI_ERR_INV_ARG;
	}
	//Need room for command, group, number of properties, and property + the actual values
	uint8_t message[4 + len];
	message[0] = SI_CMD_SET_PROPERTY;
	message[1] = SI_GRP(prop);
	message[2] = (uint8_t) len;
	message[3] = SI_PROP(prop);
	for(size_t i = 0; i < len; i++) {
		message[4 + i] = (value >> ((len - i - 1) * 8)) & 0xFF;
	}	
	log(VRB, "Setting group %u property %u to value %u.\n\r", SI_GRP(prop), SI_PROP(prop), value);
	uint8_t cts = 0;
	return si_spi(message, 4 + len, &cts, 1);
}

si_err_t si_init(void) {
	/* 
		Initialize SI module by starting SPI and sending power up sequence (including clock config).
		Then set transmission frequency field values.
		Configured through si_cfg.h
		Returns success/error code
	*/

	si_err_t err = SI_ERR_SUCCESS;

	//Intialize PADs
	palSetPadMode(SI_SSPORT, SI_SSPAD, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOG, 12, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOG, 13, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOG, 14, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
	spiStart(&SI_SPID, &SI_SPI_CFG);
	if(SI_SPID.state != SPI_READY) {
		log(ERR, "SPI Driver not ready!\r\n");
		return SI_ERR_NOT_READY;
	}
	 
	// Send data configuration array
	uint8_t cts = 0;
	uint8_t length = SI_CFG[0];
	uint8_t* ptr = SI_CFG + 1;
	while(length != 0) {
		uint8_t tx[length];
		for(int i = 0; i < length; i++) {
			tx[i] = *ptr;
			ptr++;
		}
		err |= si_spi(tx, length, &cts, 1);
		length = *ptr;
		ptr++;
	}
	 
	if(err != SI_ERR_SUCCESS) {
		log(ERR, "Did not successfully init!\r\n");
	}

	uint32_t cnt1 = 0;
	uint32_t misc = 0;
	uint32_t search = 0;
	uint32_t control = 0;
	si_get_prop(SI_MODEM_OOK_CNT1, &cnt1, 8);
	si_get_prop(SI_MODEM_OOK_MISC, &misc, 8);
	si_get_prop(SI_MODEM_RAW_SEARCH, &search, 8);
	si_get_prop(SI_MODEM_RAW_CONTROL, &control, 8);
		
	return err;
}

si_err_t si_rx(uint8_t* buf, size_t max_buflen, uint16_t* b_read) {
	/* 
		Enters RX mode and attempts to receive a packet and read it into the buffer.
		Returns error. Loads bytes read into b_read
	*/
	si_err_t err = SI_ERR_SUCCESS;
	 
	//Clear RX FIFO
	//TODO At higher bitrates, messages are captured in non-rx parts of the loop so we lose information
	uint8_t fifo_info[] = {SI_CMD_FIFO_INFO, 0x02};
	uint8_t throw[3];
	err |= si_spi(fifo_info, 2, throw, 3);
	 
	//Start RX Mode
	uint8_t cts = 0;
	err |= si_set_prop(SI_PKT_FIELD_1_LENGTH, (uint32_t) max_buflen, 13);
	uint8_t start_rx[8] = { SI_CMD_START_RX, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00 };
	err |= si_spi(start_rx, 8, &cts, 1);
	chThdSleep(TIME_MS2I(10));
	
	//Check interrupt status (wait for packet to arrive)
	uint8_t get_int_status[4] = {SI_CMD_GET_INT_STATUS, 0x00, 0x00, 0x00};
	uint8_t int_status[9] = {0};
	err |= si_spi(get_int_status, 4, int_status, 9);
	uint8_t packet_rx_pend = 0;
	uint8_t packet_rx = 0;
	uint32_t q = 0;
	while(!(packet_rx || packet_rx_pend) && q++ < SI_TIMEOUT) {
		err |= si_spi(get_int_status, 4, int_status, 9);
		packet_rx_pend = (int_status[3] >> 4) & 0x01;
		packet_rx = (int_status[4] >> 4) & 0x01;
		log(VRB, "Waiting to receive packet...\r");
	}
	if(!(packet_rx || packet_rx_pend)) {
		log(ERR, "Failed to receive packet!\r\n");
		err |= SI_ERR_TXRX;
	}

	//Get buffer from fifo
	//check fifo
	fifo_info[1] = 0x00;
	err |= si_spi(fifo_info, 2, throw, 3);
	log(VRB, "FIFO length is %u\r\n", throw[1]);
	//*b_read = throw[1] - 1;
	*b_read = 8;
	 
	uint8_t read_rx_fifo = SI_CMD_READ_RX_FIFO;
	spiSelect(&SI_SPID);
	spiSend(&SI_SPID, 1, &read_rx_fifo);
	spiReceive(&SI_SPID, *b_read, buf);
	spiUnselect(&SI_SPID);
	 
	return err;
}

si_err_t si_tx(uint8_t* buf, size_t buflen) {
	/*
	 
		Transmits a variable-length buffer over radio
		Uses Preamble + SYNC + CRC
	*/
	if (buflen > 62) {
		// The tx fifo size max is 64
		//TODO there should be a way to load longer payloads but I'm not sure how
		log(ERR, "Argument of size %u exceeds maximum capacity of TX_FIFO (2 byte length + 62 byte data).", buflen);
		return SI_ERR_INV_ARG;
	}
	si_err_t err = SI_ERR_SUCCESS;
	// clear FIFO buf
	uint8_t fifo_info[] = {SI_CMD_FIFO_INFO, 0x01};
	uint8_t cts = 0;
	err |= si_spi(fifo_info, 2, &cts, 1);
	uint8_t write = SI_CMD_WRITE_TX_FIFO;
	 
	spiSelect(&SI_SPID);
	spiSend(&SI_SPID, 1, &write);
	spiSend(&SI_SPID, buflen, buf);
	spiUnselect(&SI_SPID);
	//transmit the tx fifo buffer
	//Returns to ready state after
	//						CMD					CHAN	COND	TX_LEN (UINT12)	
	err |= si_set_prop(SI_PKT_FIELD_1_LENGTH, (uint32_t) buflen, 13);
	uint8_t start_tx[] = {	SI_CMD_START_TX,	0x00,	0x30,	0x00,	0x00};
	cts = 0;
	err |= si_spi(start_tx, 5, &cts, 1);

	chThdSleep(TIME_MS2I(1));
	//Check interrupt status
	uint8_t get_int_status[4] = {SI_CMD_GET_INT_STATUS, 0x00, 0x00, 0x00};
	uint8_t int_status[9] = {0};
	err |= si_spi(get_int_status, 4, int_status, 9);
	uint8_t packet_sent_pend = 0x00;
	uint8_t packet_sent = 0x00;
	uint32_t i = 0;
	while(!(packet_sent || packet_sent_pend) && i++ < SI_TIMEOUT) {
		log(VRB, "Waiting for packet to send...\r");
		err |= si_spi(get_int_status, 4, int_status, 9);
		packet_sent_pend = (int_status[3] >> 5) & 0x01;
		packet_sent = (int_status[4] >> 5) & 0x01;
		chThdSleep(TIME_MS2I(1));
	}
	if(packet_sent || packet_sent_pend) {
		log(VRB, "Packet sent succesfully.\n\r");
	}
	else {
		log(ERR, "Timed out waiting for packet to send!\n\r");
		err |= SI_ERR_TXRX;
	}
	return err;
}

si_err_t si_check(void) {
	/*
		Returns success if the part no of the chip is correct
	*/
	uint8_t part_info = SI_CMD_PART_INFO;
	uint8_t reply[9];
	si_spi(&part_info, 1, reply, 9);
	log(VRB, "Chip part info: %02X %02X\n\r", reply[2], reply[3]);
	if(reply[2] == 0x44 && reply[3] == 0x64) {
		return SI_ERR_SUCCESS;
	} else return SI_ERR_INV_REPLY;
}
