#ifndef __SI_CMD_H__
#define __SI_CMD_H__

typedef enum si_cmd_t {
	// No Operation command.
	SI_CMD_NOP						= 0x00,
	// Reports basic information about the device.
	SI_CMD_PART_INFO				= 0x01,
	// Turn the darn thing on
	SI_CMD_POWER_UP					= 0x02,
	// Returns the Function revision information of the device.
	SI_CMD_FUNC_INFO				= 0x10,
	// Sets the value of one or more properties.
	SI_CMD_SET_PROPERTY				= 0x11,
	// Retrieves the value of one or more properties
	SI_CMD_GET_PROPERTY				= 0x12,
	// Configures the GPIO pins.
	SI_CMD_GPIO_PIN_CFG				= 0x13,
	// Access the current byte counts in the TX and RX FIFOs, and provide for resetting the FIFOs.
	SI_CMD_FIFO_INFO				= 0x15,
	// Returns the interrupt status of ALL the possible interrupt events (both STATUS and PENDING).  Optionally, it may be used to clear latched (PENDING) interrupt  events.
	SI_CMD_GET_INT_STATUS			= 0x20,
	// Request current device state and channel.
	SI_CMD_REQUEST_DEVICE_STATE		= 0x33,
	// Manually switch the chip to a desired operating state.
	SI_CMD_CHANGE_STATE				= 0x34,
	// Used to read CTS and the command response.
	SI_CMD_READ_CMD_BUFF			= 0x44,
	// Reads the fast response registers (FRR) starting with FRR_A.
	SI_CMD_FRR_A_READ				= 0x50,
	// Reads the fast response registers (FRR) starting with FRR_B.
	SI_CMD_FRR_B_READ				= 0x51,
	// Reads the fast response registers (FRR) starting with FRR_C.
	SI_CMD_FRR_C_READ				= 0x53,
	// Reads the fast response registers (FRR) starting with FRR_D.
	SI_CMD_FRR_D_READ				= 0x57,
	// Image rejection calibration.
	SI_CMD_IRCAL					= 0x17,
	// Image rejection calibration.
	SI_CMD_IRCAL_MANUAL				= 0x1a,
	// Switches to TX state and starts transmission of a packet.
	SI_CMD_START_TX					= 0x31,
	// Writes data byte(s) to the TX FIFO.
	SI_CMD_WRITE_TX_FIFO			= 0x66,
	// Returns information about the length of the variable field in the last packet received, and (optionally) overrides field  length. ,
	SI_CMD_PACKET_INFO				= 0x16,
	// Returns the interrupt status of the Modem Interrupt Group (both STATUS and PENDING).  Optionally, it may be used to clear latched (PENDING) interrupt  events.,
	SI_CMD_GET_MODEM_STATUS			= 0x22,
	// Switches to RX state and starts reception of a packet.
	SI_CMD_START_RX					= 0x32,
	// Manually hop to a new frequency while in RX mode. 
	SI_CMD_RX_HOP					= 0x36,
	// Reads data byte(s) from the RX FIFO.
	SI_CMD_READ_RX_FIFO				= 0x77,
	// Performs conversions using the Auxiliary ADC and returns the results of those conversions.
	SI_CMD_GET_ADC_READING			= 0x14,
	// Returns the interrupt status of the Packet Handler Interrupt Group (both STATUS and PENDING).  Optionally, it may be used to clear latched (PENDING) interrupt  events.,
	SI_CMD_GET_PH_STATUS			= 0x21,
	// Returns the interrupt status of the Chip Interrupt Group (both STATUS and PENDING).  Optionally, it may be used to clear latched (PENDING) interrupt  events.,
	SI_CMD_GET_CHIP_STATUS			= 0x23,
} si_cmd_t;


#endif /* __SI_CMD_H__ */
