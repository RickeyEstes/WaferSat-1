/*
	Wrapper for si spi communication.
	Includes basic radio tx and rx; read attached documentation for more specific/efficient communication methods
*/
#ifndef __SI_H__
#define __SI_H__
#include "hal_spi.h"
#include "si_cmd.h"
#include "si_prop.h"
#include "si_cfg.h"

static const uint8_t SI_CFG[] = RADIO_CONFIGURATION_DATA_ARRAY;
 
//Time to wait for CTS in ms
#define SI_TIMEOUT 2000

#define SI_SSPORT GPIOA
#define SI_SSPAD 15
// Look at ./ChibiOS/os/hal/ports/STM32/LLD/SPIv2/hal_spi_lld.h for definition of struct/explanation of registers
static const SPIConfig SI_SPI_CFG = {
	.circular = false,
	.end_cb = NULL,
	// .ssline = LINE_SPI6_CS2,
	.ssport = SI_SSPORT,
	.sspad = SI_SSPAD,
	.cr1 = SPI_CR1_BR_2,
	.cr2 = 0
};

// SPI driver for SI4464
#define SI_SPID SPID6

// Return code error flags
typedef enum si_err_t {
	SI_ERR_SUCCESS 	= 0x00,
	SI_ERR_TIMEOUT 	= 0x01,
	SI_ERR_NO_CTS  	= 0x01 << 1,
	SI_ERR_NOT_READY= 0x01 << 2,
	SI_ERR_INV_ARG	= 0x01 << 3,
	SI_ERR_INV_REPLY= 0x01 << 4,
	SI_ERR_TXRX		= 0x01 << 4,
} si_err_t;
 
//Communicate with module over spi
si_err_t si_spi(const uint8_t* tx_buf, size_t tx_len, uint8_t* rx_buf, size_t rx_len);
//set a config property
si_err_t si_set_prop(si_prop_t prop, uint32_t value, size_t len);
// get a config property value 
si_err_t si_get_prop(si_prop_t prop, uint32_t* value, size_t len);
//Radio boot sequence
si_err_t si_init(void);
// Transmit buffer over radio
si_err_t si_tx(uint8_t* buf, size_t max_buflen);
// Read out rx into buf 
si_err_t si_rx(uint8_t* buf, size_t maxbuflen, uint16_t* b_read);

si_err_t si_check(void);
 
#endif /* _SI_H__ */
