#ifndef __SI_PROP_H__
#define __SI_PROP_H__

#define SI_PROP(prop) (prop & 0xFF)
#define SI_GRP(prop) ((prop >> 8) & 0xFF)

// For multi-field length properties, this table gives the first index
// Contains group in first 8 bits and property in last 8 bits
typedef enum si_prop_t {
	// Default: 0x40 Configure the internal capacitor frequency tuning bank for the crystal oscillator.
	SI_GLOBAL_XO_TUNE							= (0x00 << 8) | 0x00,
	// Default: 0x00 Clock configuration options.
	SI_GLOBAL_CLK_CFG							= (0x00 << 8) | 0x01,
	// Default: 0x18 Configures the threshold voltage for low-battery detection.
	SI_GLOBAL_LOW_BATT_THRESH					= (0x00 << 8) | 0x02,
	// Default: 0x20 Global configuration settings.
	SI_GLOBAL_CONFIG							= (0x00 << 8) | 0x03,
	// Default: 0x00 General Wakeup Timer feature configuration.
	SI_GLOBAL_WUT_CONFIG						= (0x00 << 8) | 0x04,
	// Default: 0x000x01 Configure the mantissa of the Wake-Up Timer (WUT) value. 
	SI_GLOBAL_WUT_M								= (0x00 << 8) | 0x05,
	// Default: 0x60 Configure the exponent of the Wake-Up Timer (WUT) value.
	SI_GLOBAL_WUT_R								= (0x00 << 8) | 0x07,
	// Default: 0x00 Configures the period of time the chip remains active after automatic wake-up in LDC mode. 
	SI_GLOBAL_WUT_LDC							= (0x00 << 8) | 0x08,
	// Default: 0x00 Controls if calibration of the 32K R-C Oscillator will be performed on intervals of the WUT.
	SI_GLOBAL_WUT_CAL							= (0x00 << 8) | 0x09,
	// Default: 0x04 This property provides for global enabling of the three interrupt groups (Chip, Modem and Packet Handler) in order to generate HW interrupts at the NIRQ pin.
	SI_INT_CTL_ENABLE							= (0x01 << 8) | 0x00,
	// Default: 0x00 Enable individual interrupt sources within the Packet Handler Interrupt Group to generate a HW interrupt on the NIRQ output pin.
	SI_INT_CTL_PH_ENABLE						= (0x01 << 8) | 0x01,
	// Default: 0x00 Enable individual interrupt sources within the Modem Interrupt Group to generate a HW interrupt on the NIRQ output pin.
	SI_INT_CTL_MODEM_ENABLE						= (0x01 << 8) | 0x02,
	// Default: 0x04 Enable individual interrupt sources within the Chip Interrupt Group to generate a HW interrupt on the NIRQ output pin.
	SI_INT_CTL_CHIP_ENABLE						= (0x01 << 8) | 0x03,
	// Default: 0x01 Fast Response Register A Configuration.
	SI_FRR_CTL_A_MODE							= (0x02 << 8) | 0x00,
	// Default: 0x02 Fast Response Register B Configuration.
	SI_FRR_CTL_B_MODE							= (0x02 << 8) | 0x01,
	// Default: 0x09 Fast Response Register C Configuration.
	SI_FRR_CTL_C_MODE							= (0x02 << 8) | 0x02,
	// Default: 0x00 Fast Response Register D Configuration.
	SI_FRR_CTL_D_MODE							= (0x02 << 8) | 0x03,
	// Default: 0x08 Configure length of TX Preamble.
	SI_PREAMBLE_TX_LENGTH						= (0x10 << 8) | 0x00,
	// Default: 0x14 Configuration of reception of a packet with a Standard Preamble pattern.
	SI_PREAMBLE_CONFIG_STD_1					= (0x10 << 8) | 0x01,
	// Default: 0x00 Configuration of transmission/reception of a packet with a Non-Standard Preamble pattern.
	SI_PREAMBLE_CONFIG_NSTD						= (0x10 << 8) | 0x02,
	// Default: 0x0f Configuration of timeout periods during reception of a packet with Standard Preamble pattern.
	SI_PREAMBLE_CONFIG_STD_2					= (0x10 << 8) | 0x03,
	// Default: 0x21 General configuration bits for the Preamble field.
	SI_PREAMBLE_CONFIG							= (0x10 << 8) | 0x04,
	// Default: 0x000x000x000x00 Configuration of the bit values describing a Non-Standard Preamble pattern.
	SI_PREAMBLE_PATTERN							= (0x10 << 8) | 0x05,
	// Default: 0x00 Configuration of Postamble functionality and the Postamble pattern bits.
	SI_PREAMBLE_POSTAMBLE_CONFIG				= (0x10 << 8) | 0x09,
	// Default: 0x000x000x000x00 Defines the Postamble pattern.
	SI_PREAMBLE_POSTAMBLE_PATTERN				= (0x10 << 8) | 0x0a,
	// Default: 0x01 Sync Word configuration bits.
	SI_SYNC_CONFIG								= (0x11 << 8) | 0x00,
	// Default: 0x2d0xd40x2d0xd4 Sync word.
	SI_SYNC_BITS								= (0x11 << 8) | 0x01,
	// Default: 0x00 Select a CRC polynomial and seed.
	SI_PKT_CRC_CONFIG							= (0x12 << 8) | 0x00,
	// Default: 0x010x08 16-bit polynomial value for the PN Generator (e.g., for Data Whitening)
	SI_PKT_WHT_POLY								= (0x12 << 8) | 0x01,
	// Default: 0xff0xff 16-bit seed value for the PN Generator (e.g., for Data Whitening)
	SI_PKT_WHT_SEED								= (0x12 << 8) | 0x03,
	// Default: 0x00 Selects which bit of the LFSR (used to generate the PN / data whitening sequence) is used as the output bit for data scrambling.
	SI_PKT_WHT_BIT_NUM							= (0x12 << 8) | 0x05,
	// Default: 0x00 General configuration bits for transmission or reception of a packet.
	SI_PKT_CONFIG1								= (0x12 << 8) | 0x06,
	// Default: 0x00 Configuration bits for reception of a variable length packet.
	SI_PKT_LEN									= (0x12 << 8) | 0x08,
	// Default: 0x00 Field number containing the received packet length byte(s).
	SI_PKT_LEN_FIELD_SOURCE						= (0x12 << 8) | 0x09,
	// Default: 0x00 Provides for adjustment/offset of the received packet length value (in order to accommodate a variety of methods of defining total packet length).
	SI_PKT_LEN_ADJUST							= (0x12 << 8) | 0x0a,
	// Default: 0x30 TX FIFO almost empty threshold.
	SI_PKT_TX_THRESHOLD							= (0x12 << 8) | 0x0b,
	// Default: 0x30 RX FIFO Almost Full threshold.
	SI_PKT_RX_THRESHOLD							= (0x12 << 8) | 0x0c,
	// Default: 0x000x00 Unsigned 13-bit Field 1 length value.
	SI_PKT_FIELD_1_LENGTH						= (0x12 << 8) | 0x0d,
	// Default: 0x00 General data processing and packet configuration bits for Field 1.
	SI_PKT_FIELD_1_CONFIG						= (0x12 << 8) | 0x0f,
	// Default: 0x00 Configuration of CRC control bits across Field 1.
	SI_PKT_FIELD_1_CRC_CONFIG					= (0x12 << 8) | 0x10,
	// Default: 0x000x00 Unsigned 13-bit Field 2 length value.
	SI_PKT_FIELD_2_LENGTH						= (0x12 << 8) | 0x11,
	// Default: 0x00 General data processing and packet configuration bits for Field 2.
	SI_PKT_FIELD_2_CONFIG						= (0x12 << 8) | 0x13,
	// Default: 0x00 Configuration of CRC control bits across Field 2.
	SI_PKT_FIELD_2_CRC_CONFIG					= (0x12 << 8) | 0x14,
	// Default: 0x000x00 Unsigned 13-bit Field 3 length value.
	SI_PKT_FIELD_3_LENGTH						= (0x12 << 8) | 0x15,
	// Default: 0x00 General data processing and packet configuration bits for Field 3.
	SI_PKT_FIELD_3_CONFIG						= (0x12 << 8) | 0x17,
	// Default: 0x00 Configuration of CRC control bits across Field 3.
	SI_PKT_FIELD_3_CRC_CONFIG					= (0x12 << 8) | 0x18,
	// Default: 0x000x00 Unsigned 13-bit Field 4 length value.
	SI_PKT_FIELD_4_LENGTH						= (0x12 << 8) | 0x19,
	// Default: 0x00 General data processing and packet configuration bits for Field 4.
	SI_PKT_FIELD_4_CONFIG						= (0x12 << 8) | 0x1b,
	// Default: 0x00 Configuration of CRC control bits across Field 4.
	SI_PKT_FIELD_4_CRC_CONFIG					= (0x12 << 8) | 0x1c,
	// Default: 0x000x00 Unsigned 13-bit Field 5 length value.
	SI_PKT_FIELD_5_LENGTH						= (0x12 << 8) | 0x1d,
	// Default: 0x00 General data processing and packet configuration bits for Field 5.
	SI_PKT_FIELD_5_CONFIG						= (0x12 << 8) | 0x1f,
	// Default: 0x00 Configuration of CRC control bits across Field 5.
	SI_PKT_FIELD_5_CRC_CONFIG					= (0x12 << 8) | 0x20,
	// Default: 0x000x00 Unsigned 13-bit RX Field 1 length value.
	SI_PKT_RX_FIELD_1_LENGTH					= (0x12 << 8) | 0x21,
	// Default: 0x00 General data processing and packet configuration bits for RX Field 1.
	SI_PKT_RX_FIELD_1_CONFIG					= (0x12 << 8) | 0x23,
	// Default: 0x00 Configuration of CRC control bits across RX Field 1.
	SI_PKT_RX_FIELD_1_CRC_CONFIG				= (0x12 << 8) | 0x24,
	// Default: 0x000x00 Unsigned 13-bit RX Field 2 length value.
	SI_PKT_RX_FIELD_2_LENGTH					= (0x12 << 8) | 0x25,
	// Default: 0x00 General data processing and packet configuration bits for RX Field 2.
	SI_PKT_RX_FIELD_2_CONFIG					= (0x12 << 8) | 0x27,
	// Default: 0x00 Configuration of CRC control bits across RX Field 2.
	SI_PKT_RX_FIELD_2_CRC_CONFIG				= (0x12 << 8) | 0x28,
	// Default: 0x000x00 Unsigned 13-bit RX Field 3 length value.
	SI_PKT_RX_FIELD_3_LENGTH					= (0x12 << 8) | 0x29,
	// Default: 0x00 General data processing and packet configuration bits for RX Field 3.
	SI_PKT_RX_FIELD_3_CONFIG					= (0x12 << 8) | 0x2b,
	// Default: 0x00 Configuration of CRC control bits across RX Field 3.
	SI_PKT_RX_FIELD_3_CRC_CONFIG				= (0x12 << 8) | 0x2c,
	// Default: 0x000x00 Unsigned 13-bit RX Field 4 length value.
	SI_PKT_RX_FIELD_4_LENGTH					= (0x12 << 8) | 0x2d,
	// Default: 0x00 General data processing and packet configuration bits for RX Field 4.
	SI_PKT_RX_FIELD_4_CONFIG					= (0x12 << 8) | 0x2f,
	// Default: 0x00 Configuration of CRC control bits across RX Field 4.
	SI_PKT_RX_FIELD_4_CRC_CONFIG				= (0x12 << 8) | 0x30,
	// Default: 0x000x00 Unsigned 13-bit RX Field 5 length value.
	SI_PKT_RX_FIELD_5_LENGTH					= (0x12 << 8) | 0x31,
	// Default: 0x00 General data processing and packet configuration bits for RX Field 5.
	SI_PKT_RX_FIELD_5_CONFIG					= (0x12 << 8) | 0x33,
	// Default: 0x00 Configuration of CRC control bits across RX Field 5.
	SI_PKT_RX_FIELD_5_CRC_CONFIG				= (0x12 << 8) | 0x34,
	// Default: 0x02 Selects the type of modulation.  In TX mode, additionally selects the source of the modulation.
	SI_MODEM_MOD_TYPE							= (0x20 << 8) | 0x00,
	// Default: 0x80 Controls polarity and mapping of transmit and receive bits.
	SI_MODEM_MAP_CONTROL						= (0x20 << 8) | 0x01,
	// Default: 0x07 Miscellaneous control bits for the Delta-Sigma Modulator (DSM) in the PLL Synthesizer.
	SI_MODEM_DSM_CTRL							= (0x20 << 8) | 0x02,
	// Default: 0x0f0x420x40 Unsigned 24-bit value used to determine the TX data rate
	SI_MODEM_DATA_RATE							= (0x20 << 8) | 0x03,
	// Default: 0x010xc90xc30x80 TX Gaussian filter oversampling ratio and Byte 3 of unsigned 26-bit TX Numerically Controlled Oscillator (NCO) modulus.
	SI_MODEM_TX_NCO_MODE						= (0x20 << 8) | 0x06,
	// Default: 0x000x060xd3 17-bit unsigned TX frequency deviation word.
	SI_MODEM_FREQ_DEV							= (0x20 << 8) | 0x0a,
	// Default: 0x000x00 Frequency offset adjustment (a 16-bit signed number).
	SI_MODEM_FREQ_OFFSET						= (0x20 << 8) | 0x0d,
	// Default: 0x67 The 8th coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_8					= (0x20 << 8) | 0x0f,
	// Default: 0x60 The 7th coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_7					= (0x20 << 8) | 0x10,
	// Default: 0x4d The 6th coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_6					= (0x20 << 8) | 0x11,
	// Default: 0x36 The 5th coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_5					= (0x20 << 8) | 0x12,
	// Default: 0x21 The 4th coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_4					= (0x20 << 8) | 0x13,
	// Default: 0x11 The 3rd coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_3					= (0x20 << 8) | 0x14,
	// Default: 0x08 The 2nd coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_2					= (0x20 << 8) | 0x15,
	// Default: 0x03 The 1st coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_1					= (0x20 << 8) | 0x16,
	// Default: 0x01 The 0th coefficient of TX spectral shaping filter.
	SI_MODEM_TX_FILTER_COEFF_0					= (0x20 << 8) | 0x17,
	// Default: 0x01 TX ramp-down delay setting.
	SI_MODEM_TX_RAMP_DELAY						= (0x20 << 8) | 0x18,
	// Default: 0x00 MDM control.
	SI_MODEM_MDM_CTRL							= (0x20 << 8) | 0x19,
	// Default: 0x08 Selects Fixed-IF, Scaled-IF, or Zero-IF mode of RX Modem operation.
	SI_MODEM_IF_CONTROL							= (0x20 << 8) | 0x1a,
	// Default: 0x030xc00x00 the IF frequency setting (an 18-bit signed number).
	SI_MODEM_IF_FREQ							= (0x20 << 8) | 0x1b,
	// Default: 0x10 Specifies three decimator ratios for the Cascaded Integrator Comb (CIC) filter.
	SI_MODEM_DECIMATION_CFG1					= (0x20 << 8) | 0x1e,
	// Default: 0x20 Specifies miscellaneous parameters and decimator ratios for the Cascaded Integrator Comb (CIC) filter.
	SI_MODEM_DECIMATION_CFG0					= (0x20 << 8) | 0x1f,
	// Default: 0x000x4b RX BCR/Slicer oversampling rate (12-bit unsigned number).
	SI_MODEM_BCR_OSR							= (0x20 << 8) | 0x22,
	// Default: 0x060xd30xa0 RX BCR NCO offset value (an unsigned 22-bit number).
	SI_MODEM_BCR_NCO_OFFSET						= (0x20 << 8) | 0x24,
	// Default: 0x060xd3 The unsigned 11-bit RX BCR loop gain value.
	SI_MODEM_BCR_GAIN							= (0x20 << 8) | 0x27,
	// Default: 0x02 RX BCR loop gear control.
	SI_MODEM_BCR_GEAR							= (0x20 << 8) | 0x29,
	// Default: 0xc0 Miscellaneous control bits for the RX BCR loop.
	SI_MODEM_BCR_MISC1							= (0x20 << 8) | 0x2a,
	// Default: 0x00 Miscellaneous RX BCR loop controls.
	SI_MODEM_BCR_MISC0							= (0x20 << 8) | 0x2b,
	// Default: 0x00 RX AFC loop gear control.
	SI_MODEM_AFC_GEAR							= (0x20 << 8) | 0x2c,
	// Default: 0x23 RX AFC loop wait time control.
	SI_MODEM_AFC_WAIT							= (0x20 << 8) | 0x2d,
	// Default: 0x830x69 Sets the gain of the PLL-based AFC acquisition loop, and provides miscellaneous control bits for AFC functionality.
	SI_MODEM_AFC_GAIN							= (0x20 << 8) | 0x2e,
	// Default: 0x000x40 Set the AFC limiter value.
	SI_MODEM_AFC_LIMITER						= (0x20 << 8) | 0x30,
	// Default: 0xa0 Specifies miscellaneous AFC control bits.
	SI_MODEM_AFC_MISC							= (0x20 << 8) | 0x32,
	// Default: 0x00 AFC fixed frequency offset in zero IF mode.
	SI_MODEM_AFC_ZIFOFF							= (0x20 << 8) | 0x33,
	// Default: 0x00 Sigma Delta ADC controls.
	SI_MODEM_ADC_CTRL							= (0x20 << 8) | 0x34,
	// Default: 0xe0 Miscellaneous control bits for the Automatic Gain Control (AGC) function in the RX Chain.
	SI_MODEM_AGC_CONTROL						= (0x20 << 8) | 0x35,
	// Default: 0x11 Specifies the size of the measurement and settling windows for the AGC algorithm. 
	SI_MODEM_AGC_WINDOW_SIZE					= (0x20 << 8) | 0x38,
	// Default: 0x10 Sets the decay time of the RF peak detectors. 
	SI_MODEM_AGC_RFPD_DECAY						= (0x20 << 8) | 0x39,
	// Default: 0x10 Sets the decay time of the IF peak detectors.
	SI_MODEM_AGC_IFPD_DECAY						= (0x20 << 8) | 0x3a,
	// Default: 0x0b Specifies the gain factor of the secondary branch in 4(G)FSK ISI-suppression.
	SI_MODEM_FSK4_GAIN1							= (0x20 << 8) | 0x3b,
	// Default: 0x1c Specifies the gain factor of the primary branch in 4(G)FSK ISI-suppression.
	SI_MODEM_FSK4_GAIN0							= (0x20 << 8) | 0x3c,
	// Default: 0x400x00 16 bit 4(G)FSK slicer threshold.
	SI_MODEM_FSK4_TH							= (0x20 << 8) | 0x3d,
	// Default: 0x00 4(G)FSK symbol mapping code.
	SI_MODEM_FSK4_MAP							= (0x20 << 8) | 0x3f,
	// Default: 0x2b Configures the attack and decay times of the OOK Peak Detector.
	SI_MODEM_OOK_PDTC							= (0x20 << 8) | 0x40,
	// Default: 0x0c Configures the slicing reference level of the OOK Peak Detector.
	SI_MODEM_OOK_BLOPK							= (0x20 << 8) | 0x41,
	// Default: 0xa4 OOK control.
	SI_MODEM_OOK_CNT1							= (0x20 << 8) | 0x42,
	// Default: 0x03 Selects the detector(s) used for demodulation of an OOK signal, or for demodulation of a (G)FSK signal when using the asynchronous demodulator.
	SI_MODEM_OOK_MISC							= (0x20 << 8) | 0x43,
	// Default: 0x56 Defines and controls the search period length for the Moving Average and Min-Max detectors.
	SI_MODEM_RAW_SEARCH							= (0x20 << 8) | 0x44,
	// Default: 0x02 Defines gain and enable controls for raw / nonstandard mode.
	SI_MODEM_RAW_CONTROL						= (0x20 << 8) | 0x45,
	// Default: 0x000xa3 11 bit eye-open detector threshold.
	SI_MODEM_RAW_EYE							= (0x20 << 8) | 0x46,
	// Default: 0x02 Antenna diversity mode settings.
	SI_MODEM_ANT_DIV_MODE						= (0x20 << 8) | 0x48,
	// Default: 0x80 Specifies controls for the Antenna Diversity algorithm.
	SI_MODEM_ANT_DIV_CONTROL					= (0x20 << 8) | 0x49,
	// Default: 0xff Configures the RSSI threshold. 
	SI_MODEM_RSSI_THRESH						= (0x20 << 8) | 0x4a,
	// Default: 0x0c Configures the RSSI Jump Detection threshold.
	SI_MODEM_RSSI_JUMP_THRESH					= (0x20 << 8) | 0x4b,
	// Default: 0x01 Control of the averaging modes and latching time for reporting RSSI value(s).
	SI_MODEM_RSSI_CONTROL						= (0x20 << 8) | 0x4c,
	// Default: 0x00 RSSI Jump Detection control.
	SI_MODEM_RSSI_CONTROL2						= (0x20 << 8) | 0x4d,
	// Default: 0x32 RSSI compensation value.
	SI_MODEM_RSSI_COMP							= (0x20 << 8) | 0x4e,
	// Default: 0x08 Select PLL Synthesizer output divider ratio as a function of frequency band.
	SI_MODEM_CLKGEN_BAND						= (0x20 << 8) | 0x51,
	// Default: 0xff0xba0x0f0x510xcf0xa90xc90xfc0x1b0x1e0x0f0x010xfc0xfd0x150xff0x000x0f Filter coefficients for the first set of RX filter coefficients.
	SI_MODEM_CHFLT_RX1_CHFLT_COE				= (0x21 << 8) | 0x00,
	// Default: 0xff0xc40x300x7f0xf50xb50xb80xde0x050x170x160x0c0x030x000x150xff0x000x00 Filter coefficients for the second set of RX filter coefficients.
	SI_MODEM_CHFLT_RX2_CHFLT_COE				= (0x21 << 8) | 0x12,
	// Default: 0x08 Selects the PA operating mode, and selects resolution of PA power adjustment (i.e., step size).
	SI_PA_MODE									= (0x22 << 8) | 0x00,
	// Default: 0x7f Configuration of PA output power level.
	SI_PA_PWR_LVL								= (0x22 << 8) | 0x01,
	// Default: 0x00 Configuration of the PA Bias and duty cycle of the TX clock source.
	SI_PA_BIAS_CLKDUTY							= (0x22 << 8) | 0x02,
	// Default: 0x5d Configuration of PA ramping parameters.
	SI_PA_TC									= (0x22 << 8) | 0x03,
	// Default: 0x80 Select the time constant of the external PA ramp signal.
	SI_PA_RAMP_EX								= (0x22 << 8) | 0x04,
	// Default: 0x23 Delay from the start of the PA ramp down to disabling of the PA output. 
	SI_PA_RAMP_DOWN_DELAY						= (0x22 << 8) | 0x05,
	// Default: 0x2c Feed forward charge pump current selection.
	SI_SYNTH_PFDCP_CPFF							= (0x23 << 8) | 0x00,
	// Default: 0x0e Integration charge pump current selection.
	SI_SYNTH_PFDCP_CPINT						= (0x23 << 8) | 0x01,
	// Default: 0x0b Gain scaling factors (Kv) for the VCO tuning varactors on both the integrated-path and feed forward path.
	SI_SYNTH_VCO_KV								= (0x23 << 8) | 0x02,
	// Default: 0x04 Value of resistor R2 in feed-forward path of loop filter.
	SI_SYNTH_LPFILT3							= (0x23 << 8) | 0x03,
	// Default: 0x0c Value of capacitor C2 in feed-forward path of loop filter.
	SI_SYNTH_LPFILT2							= (0x23 << 8) | 0x04,
	// Default: 0x73 Value of capacitors C1 and C3 in feed-forward path of loop filter.
	SI_SYNTH_LPFILT1							= (0x23 << 8) | 0x05,
	// Default: 0x03 Bias current of the active amplifier in the feed-forward loop filter.
	SI_SYNTH_LPFILT0							= (0x23 << 8) | 0x06,
	// Default: 0x05 Scaling entire KV of VCO.
	SI_SYNTH_VCO_KVCAL							= (0x23 << 8) | 0x07,
	// Default: 0x00 Match value to be compared with the result of logically AND-ing (bit-wise) the Mask 1 value with the received Match 1 byte. 
	SI_MATCH_VALUE_1							= (0x30 << 8) | 0x00,
	// Default: 0x00 Mask value to be logically AND-ed (bit-wise) with the Match 1 byte.
	SI_MATCH_MASK_1								= (0x30 << 8) | 0x01,
	// Default: 0x00 Enable for Packet Match functionality, and configuration of Match Byte 1.
	SI_MATCH_CTRL_1								= (0x30 << 8) | 0x02,
	// Default: 0x00 Match value to be compared with the result of logically AND-ing (bit-wise) the Mask 2 value with the received Match 2 byte. 
	SI_MATCH_VALUE_2							= (0x30 << 8) | 0x03,
	// Default: 0x00 Mask value to be logically AND-ed (bit-wise) with the Match 2 byte.
	SI_MATCH_MASK_2								= (0x30 << 8) | 0x04,
	// Default: 0x00 Configuration of Match Byte 2.
	SI_MATCH_CTRL_2								= (0x30 << 8) | 0x05,
	// Default: 0x00 Match value to be compared with the result of logically AND-ing (bit-wise) the Mask 3 value with the received Match 3 byte. 
	SI_MATCH_VALUE_3							= (0x30 << 8) | 0x06,
	// Default: 0x00 Mask value to be logically AND-ed (bit-wise) with the Match 3 byte.
	SI_MATCH_MASK_3								= (0x30 << 8) | 0x07,
	// Default: 0x00 Configuration of Match Byte 3.
	SI_MATCH_CTRL_3								= (0x30 << 8) | 0x08,
	// Default: 0x00 Match value to be compared with the result of logically AND-ing (bit-wise) the Mask 4 value with the received Match 4 byte. 
	SI_MATCH_VALUE_4							= (0x30 << 8) | 0x09,
	// Default: 0x00 Mask value to be logically AND-ed (bit-wise) with the Match 4 byte.
	SI_MATCH_MASK_4								= (0x30 << 8) | 0x0a,
	// Default: 0x00 Configuration of Match Byte 4.
	SI_MATCH_CTRL_4								= (0x30 << 8) | 0x0b,
	// Default: 0x3c Frac-N PLL Synthesizer integer divide number.
	SI_FREQ_CONTROL_INTE						= (0x40 << 8) | 0x00,
	// Default: 0x080x000x00 Frac-N PLL fraction number.
	SI_FREQ_CONTROL_FRAC						= (0x40 << 8) | 0x01,
	// Default: 0x000x00 EZ Frequency Programming channel step size.
	SI_FREQ_CONTROL_CHANNEL_STEP_SIZE 			= (0x40 << 8) | 0x04,
	// Default: 0x20 Set window gating period (in number of crystal reference clock cycles) for counting VCO frequency during calibration.
	SI_SI_FREQ_CONTROL_W_SIZE					= (0x40 << 8) | 0x06,
	// Default: 0xff Adjust target count for VCO calibration in RX mode.
	SI_SI_FREQ_CONTROL_VCOCNT_RX_ADJ 			= (0x40 << 8) | 0x07,
	// Default: 0x04 Configuration options for the automatic RX Hop functionality.
	SI_SI_RX_HOP_CONTROL						= (0x50 << 8) | 0x00,
	// Default: 0x01 Specifies the number of entries (channels) in the RX Hop table.
	SI_RX_HOP_TABLE_SIZE						= (0x50 << 8) | 0x01,
	// Default: 0x00 Defines entries in the RX Ho=0 to 63)
	// Goes all the way from 0x02 to 0x3f
	SI_RX_HOP_TABLE_ENTRY						= (0x50 << 8) | 0x02,
} si_prop_t;
 
#endif /* __SI_PROP_H__ */
