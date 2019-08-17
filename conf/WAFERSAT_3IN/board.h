/*
    ChibiOS - Copyright (C) 2006..2017 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for Wafersat  3in board.
 */

/*
 * Board identifier.
 */
#define BOARD_WAFERSAT_3IN
#define BOARD_NAME                  "Wafersat  3in"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F429xx

/*
 * IO pins assignments.
 */
#define GPIOA_UART4_TX              0U
#define GPIOA_UART4_RX              1U
#define GPIOA_UART2_GPS_TX          2U
#define GPIOA_UART2_GPS_RX          3U
#define GPIOA_DCMI_HSYNC            4U
#define GPIOA_SPI1_SCK              5U
#define GPIOA_DCMI_PXCLK            6U
#define GPIOA_SPI1_MOSI             7U
#define GPIOA_RCC_MCO_1             8U
#define GPIOA_UART1_TX              9U
#define GPIOA_UART1_RX              10U
#define GPIOA_UART1_CTS             11U
#define GPIOA_UART1_RTS             12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_SPI6_CS1              15U

#define GPIOB_CAM_RESET             0U
#define GPIOB_CAM_EN                1U
#define GPIOB_RADIO_IRQ             2U
#define GPIOB_SWO                   3U
#define GPIOB_SPI1_MISO             4U
#define GPIOB_FMC_SDCKE1            5U
#define GPIOB_FMC_SDNE1             6U
#define GPIOB_DCMI_VSYNC            7U
#define GPIOB_SD_D4                 8U
#define GPIOB_SD_D5                 9U
#define GPIOB_UART3_TX              10U
#define GPIOB_UART3_RX              11U
#define GPIOB_OTG_HS_ID             12U
#define GPIOB_OTG_HS_VBUS           13U
#define GPIOB_OTG_HS_DM             14U
#define GPIOB_OTG_HS_DP             15U

#define GPIOC_FMC_SDNWE             0U
#define GPIOC_HEADER_PINC1          1U
#define GPIOC_HEADER_PINC2          2U
#define GPIOC_HEADER_PINC3          3U
#define GPIOC_ADC_VIN               4U
#define GPIOC_HEADER_PINC5          5U
#define GPIOC_SD_D6                 6U
#define GPIOC_SD_D7                 7U
#define GPIOC_SD_D0                 8U
#define GPIOC_SD_D1                 9U
#define GPIOC_SD_D2                 10U
#define GPIOC_SD_D3                 11U
#define GPIOC_SD_CLK                12U
#define GPIOC_HEADER_PINC13         13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_FMC_D2                0U
#define GPIOD_FMC_D3                1U
#define GPIOD_SD_CMD                2U
#define GPIOD_DCMI_D5               3U
#define GPIOD_GPS_PPS               4U
#define GPIOD_LED_RED               5U
#define GPIOD_LED_GREEN             6U
#define GPIOD_LED_BLUE              7U
#define GPIOD_FMC_D13               8U
#define GPIOD_FMC_D14               9U
#define GPIOD_FMC_D15               10U
#define GPIOD_UART3_CTS             11U
#define GPIOD_UART3_RTS             12U
#define GPIOD_HEADER_PIND13         13U
#define GPIOD_FMC_D0                14U
#define GPIOD_FMC_D1                15U

#define GPIOE_FMC_NBL0              0U
#define GPIOE_FMC_NBL1              1U
#define GPIOE_HEADER_PINE2          2U
#define GPIOE_HEADER_PINE3          3U
#define GPIOE_DCMI_D4               4U
#define GPIOE_DCMI_D6               5U
#define GPIOE_DCMI_D7               6U
#define GPIOE_FMC_D4                7U
#define GPIOE_FMC_D5                8U
#define GPIOE_FMC_D6                9U
#define GPIOE_FMC_D7                10U
#define GPIOE_FMC_D8                11U
#define GPIOE_FMC_D9                12U
#define GPIOE_FMC_D10               13U
#define GPIOE_FMC_D11               14U
#define GPIOE_FMC_D12               15U

#define GPIOF_FMC_A0                0U
#define GPIOF_FMC_A1                1U
#define GPIOF_FMC_A2                2U
#define GPIOF_FMC_A3                3U
#define GPIOF_FMC_A4                4U
#define GPIOF_FMC_A5                5U
#define GPIOF_LASERCOM_TX           6U
#define GPIOF_LASERCOM_RX           7U
#define GPIOF_SPI5_MISO             8U
#define GPIOF_SPI5_MOSI             9U
#define GPIOF_SPI5_SC1              10U
#define GPIOF_FMC_SDNRAS            11U
#define GPIOF_FMC_A6                12U
#define GPIOF_FMC_A7                13U
#define GPIOF_FMC_A8                14U
#define GPIOF_FMC_A9                15U

#define GPIOG_FMC_A10               0U
#define GPIOG_FMC_A11               1U
#define GPIOG_FMC_A12               2U
#define GPIOG_SPI1_CS1              3U
#define GPIOG_FMC_BA0               4U
#define GPIOG_FMC_BA1               5U
#define GPIOG_RADIO_GPIO1           6U
#define GPIOG_RADIO_GPIO0           7U
#define GPIOG_FMC_SDCLK             8U
#define GPIOG_PIN9                  9U
#define GPIOG_DCMI_D2               10U
#define GPIOG_DCMI_D3               11U
#define GPIOG_SPI6_MISO             12U
#define GPIOG_SPI6_SCK              13U
#define GPIOG_SPI6_MOSI             14U
#define GPIOG_FMC_SDNCAS            15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_I2C2_SCL              4U
#define GPIOH_I2C2_SDA              5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_DCMI_D0               9U
#define GPIOH_DCMI_D1               10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_UART4_TX               PAL_LINE(GPIOA, 0U)
#define LINE_UART4_RX               PAL_LINE(GPIOA, 1U)
#define LINE_UART2_GPS_TX           PAL_LINE(GPIOA, 2U)
#define LINE_UART2_GPS_RX           PAL_LINE(GPIOA, 3U)
#define LINE_DCMI_HSYNC             PAL_LINE(GPIOA, 4U)
#define LINE_SPI1_SCK               PAL_LINE(GPIOA, 5U)
#define LINE_DCMI_PXCLK             PAL_LINE(GPIOA, 6U)
#define LINE_SPI1_MOSI              PAL_LINE(GPIOA, 7U)
#define LINE_RCC_MCO_1              PAL_LINE(GPIOA, 8U)
#define LINE_UART1_TX               PAL_LINE(GPIOA, 9U)
#define LINE_UART1_RX               PAL_LINE(GPIOA, 10U)
#define LINE_UART1_CTS              PAL_LINE(GPIOA, 11U)
#define LINE_UART1_RTS              PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_SPI6_CS1               PAL_LINE(GPIOA, 15U)
#define LINE_CAM_RESET              PAL_LINE(GPIOB, 0U)
#define LINE_CAM_EN                 PAL_LINE(GPIOB, 1U)
#define LINE_RADIO_IRQ              PAL_LINE(GPIOB, 2U)
#define LINE_SWO                    PAL_LINE(GPIOB, 3U)
#define LINE_SPI1_MISO              PAL_LINE(GPIOB, 4U)
#define LINE_FMC_SDCKE1             PAL_LINE(GPIOB, 5U)
#define LINE_FMC_SDNE1              PAL_LINE(GPIOB, 6U)
#define LINE_DCMI_VSYNC             PAL_LINE(GPIOB, 7U)
#define LINE_SD_D4                  PAL_LINE(GPIOB, 8U)
#define LINE_SD_D5                  PAL_LINE(GPIOB, 9U)
#define LINE_UART3_TX               PAL_LINE(GPIOB, 10U)
#define LINE_UART3_RX               PAL_LINE(GPIOB, 11U)
#define LINE_OTG_HS_ID              PAL_LINE(GPIOB, 12U)
#define LINE_OTG_HS_VBUS            PAL_LINE(GPIOB, 13U)
#define LINE_OTG_HS_DM              PAL_LINE(GPIOB, 14U)
#define LINE_OTG_HS_DP              PAL_LINE(GPIOB, 15U)
#define LINE_FMC_SDNWE              PAL_LINE(GPIOC, 0U)
#define LINE_HEADER_PINC1           PAL_LINE(GPIOC, 1U)
#define LINE_HEADER_PINC2           PAL_LINE(GPIOC, 2U)
#define LINE_HEADER_PINC3           PAL_LINE(GPIOC, 3U)
#define LINE_ADC_VIN                PAL_LINE(GPIOC, 4U)
#define LINE_HEADER_PINC5           PAL_LINE(GPIOC, 5U)
#define LINE_SD_D6                  PAL_LINE(GPIOC, 6U)
#define LINE_SD_D7                  PAL_LINE(GPIOC, 7U)
#define LINE_SD_D0                  PAL_LINE(GPIOC, 8U)
#define LINE_SD_D1                  PAL_LINE(GPIOC, 9U)
#define LINE_SD_D2                  PAL_LINE(GPIOC, 10U)
#define LINE_SD_D3                  PAL_LINE(GPIOC, 11U)
#define LINE_SD_CLK                 PAL_LINE(GPIOC, 12U)
#define LINE_HEADER_PINC13          PAL_LINE(GPIOC, 13U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_OSC32_OUT              PAL_LINE(GPIOC, 15U)
#define LINE_FMC_D2                 PAL_LINE(GPIOD, 0U)
#define LINE_FMC_D3                 PAL_LINE(GPIOD, 1U)
#define LINE_SD_CMD                 PAL_LINE(GPIOD, 2U)
#define LINE_DCMI_D5                PAL_LINE(GPIOD, 3U)
#define LINE_GPS_PPS                PAL_LINE(GPIOD, 4U)
#define LINE_LED_RED                PAL_LINE(GPIOD, 5U)
#define LINE_LED_GREEN              PAL_LINE(GPIOD, 6U)
#define LINE_LED_BLUE               PAL_LINE(GPIOD, 7U)
#define LINE_FMC_D13                PAL_LINE(GPIOD, 8U)
#define LINE_FMC_D14                PAL_LINE(GPIOD, 9U)
#define LINE_FMC_D15                PAL_LINE(GPIOD, 10U)
#define LINE_UART3_CTS              PAL_LINE(GPIOD, 11U)
#define LINE_UART3_RTS              PAL_LINE(GPIOD, 12U)
#define LINE_HEADER_PIND13          PAL_LINE(GPIOD, 13U)
#define LINE_FMC_D0                 PAL_LINE(GPIOD, 14U)
#define LINE_FMC_D1                 PAL_LINE(GPIOD, 15U)
#define LINE_FMC_NBL0               PAL_LINE(GPIOE, 0U)
#define LINE_FMC_NBL1               PAL_LINE(GPIOE, 1U)
#define LINE_HEADER_PINE2           PAL_LINE(GPIOE, 2U)
#define LINE_HEADER_PINE3           PAL_LINE(GPIOE, 3U)
#define LINE_DCMI_D4                PAL_LINE(GPIOE, 4U)
#define LINE_DCMI_D6                PAL_LINE(GPIOE, 5U)
#define LINE_DCMI_D7                PAL_LINE(GPIOE, 6U)
#define LINE_FMC_D4                 PAL_LINE(GPIOE, 7U)
#define LINE_FMC_D5                 PAL_LINE(GPIOE, 8U)
#define LINE_FMC_D6                 PAL_LINE(GPIOE, 9U)
#define LINE_FMC_D7                 PAL_LINE(GPIOE, 10U)
#define LINE_FMC_D8                 PAL_LINE(GPIOE, 11U)
#define LINE_FMC_D9                 PAL_LINE(GPIOE, 12U)
#define LINE_FMC_D10                PAL_LINE(GPIOE, 13U)
#define LINE_FMC_D11                PAL_LINE(GPIOE, 14U)
#define LINE_FMC_D12                PAL_LINE(GPIOE, 15U)
#define LINE_FMC_A0                 PAL_LINE(GPIOF, 0U)
#define LINE_FMC_A1                 PAL_LINE(GPIOF, 1U)
#define LINE_FMC_A2                 PAL_LINE(GPIOF, 2U)
#define LINE_FMC_A3                 PAL_LINE(GPIOF, 3U)
#define LINE_FMC_A4                 PAL_LINE(GPIOF, 4U)
#define LINE_FMC_A5                 PAL_LINE(GPIOF, 5U)
#define LINE_LASERCOM_TX            PAL_LINE(GPIOF, 6U)
#define LINE_LASERCOM_RX            PAL_LINE(GPIOF, 7U)
#define LINE_SPI5_MISO              PAL_LINE(GPIOF, 8U)
#define LINE_SPI5_MOSI              PAL_LINE(GPIOF, 9U)
#define LINE_SPI5_SC1               PAL_LINE(GPIOF, 10U)
#define LINE_FMC_SDNRAS             PAL_LINE(GPIOF, 11U)
#define LINE_FMC_A6                 PAL_LINE(GPIOF, 12U)
#define LINE_FMC_A7                 PAL_LINE(GPIOF, 13U)
#define LINE_FMC_A8                 PAL_LINE(GPIOF, 14U)
#define LINE_FMC_A9                 PAL_LINE(GPIOF, 15U)
#define LINE_FMC_A10                PAL_LINE(GPIOG, 0U)
#define LINE_FMC_A11                PAL_LINE(GPIOG, 1U)
#define LINE_FMC_A12                PAL_LINE(GPIOG, 2U)
#define LINE_SPI1_CS1               PAL_LINE(GPIOG, 3U)
#define LINE_FMC_BA0                PAL_LINE(GPIOG, 4U)
#define LINE_FMC_BA1                PAL_LINE(GPIOG, 5U)
#define LINE_RADIO_GPIO1            PAL_LINE(GPIOG, 6U)
#define LINE_RADIO_GPIO0            PAL_LINE(GPIOG, 7U)
#define LINE_FMC_SDCLK              PAL_LINE(GPIOG, 8U)
#define LINE_DCMI_D2                PAL_LINE(GPIOG, 10U)
#define LINE_DCMI_D3                PAL_LINE(GPIOG, 11U)
#define LINE_SPI6_MISO              PAL_LINE(GPIOG, 12U)
#define LINE_SPI6_SCK               PAL_LINE(GPIOG, 13U)
#define LINE_SPI6_MOSI              PAL_LINE(GPIOG, 14U)
#define LINE_FMC_SDNCAS             PAL_LINE(GPIOG, 15U)
#define LINE_OSC_IN                 PAL_LINE(GPIOH, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOH, 1U)
#define LINE_I2C2_SCL               PAL_LINE(GPIOH, 4U)
#define LINE_I2C2_SDA               PAL_LINE(GPIOH, 5U)
#define LINE_DCMI_D0                PAL_LINE(GPIOH, 9U)
#define LINE_DCMI_D1                PAL_LINE(GPIOH, 10U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - UART4_TX                  (alternate 8).
 * PA1  - UART4_RX                  (alternate 8).
 * PA2  - UART2_GPS_TX              (alternate 7).
 * PA3  - UART2_GPS_RX              (alternate 7).
 * PA4  - DCMI_HSYNC                (alternate 13).
 * PA5  - SPI1_SCK                  (input floating).
 * PA6  - DCMI_PXCLK                (alternate 13).
 * PA7  - SPI1_MOSI                 (input floating).
 * PA8  - RCC_MCO_1                 (alternate 0).
 * PA9  - UART1_TX                  (alternate 7).
 * PA10 - UART1_RX                  (alternate 7).
 * PA11 - UART1_CTS                 (alternate 7).
 * PA12 - UART1_RTS                 (alternate 7).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - SPI6_CS1                  (input floating).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(GPIOA_UART4_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_UART4_RX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_UART2_GPS_TX) |\
                                     PIN_MODE_ALTERNATE(GPIOA_UART2_GPS_RX) |\
                                     PIN_MODE_ALTERNATE(GPIOA_DCMI_HSYNC) | \
                                     PIN_MODE_INPUT(GPIOA_SPI1_SCK) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_DCMI_PXCLK) | \
                                     PIN_MODE_INPUT(GPIOA_SPI1_MOSI) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_RCC_MCO_1) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_RX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_CTS) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_RTS) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_SPI6_CS1))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_UART4_TX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART4_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART2_GPS_TX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART2_GPS_RX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_DCMI_HSYNC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_DCMI_PXCLK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RCC_MCO_1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_TX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_CTS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_RTS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI6_CS1))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOA_UART4_TX) |   \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART4_RX) |   \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART2_GPS_TX) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_UART2_GPS_RX) |\
                                     PIN_OSPEED_HIGH(GPIOA_DCMI_HSYNC) |    \
                                     PIN_OSPEED_VERYLOW(GPIOA_SPI1_SCK) |   \
                                     PIN_OSPEED_HIGH(GPIOA_DCMI_PXCLK) |    \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MOSI) |     \
                                     PIN_OSPEED_HIGH(GPIOA_RCC_MCO_1) |     \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART1_TX) |   \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART1_RX) |   \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART1_CTS) |  \
                                     PIN_OSPEED_VERYLOW(GPIOA_UART1_RTS) |  \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SPI6_CS1))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_UART4_TX) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_UART4_RX) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_UART2_GPS_TX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_UART2_GPS_RX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_DCMI_HSYNC) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_SCK) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_DCMI_PXCLK) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MOSI) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_RCC_MCO_1) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_TX) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_RX) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_CTS) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_RTS) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI6_CS1))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_UART4_TX) |         \
                                     PIN_ODR_HIGH(GPIOA_UART4_RX) |         \
                                     PIN_ODR_HIGH(GPIOA_UART2_GPS_TX) |     \
                                     PIN_ODR_HIGH(GPIOA_UART2_GPS_RX) |     \
                                     PIN_ODR_HIGH(GPIOA_DCMI_HSYNC) |       \
                                     PIN_ODR_HIGH(GPIOA_SPI1_SCK) |         \
                                     PIN_ODR_HIGH(GPIOA_DCMI_PXCLK) |       \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOA_RCC_MCO_1) |        \
                                     PIN_ODR_HIGH(GPIOA_UART1_TX) |         \
                                     PIN_ODR_HIGH(GPIOA_UART1_RX) |         \
                                     PIN_ODR_HIGH(GPIOA_UART1_CTS) |        \
                                     PIN_ODR_HIGH(GPIOA_UART1_RTS) |        \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_SPI6_CS1))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_UART4_TX, 8U) |      \
                                     PIN_AFIO_AF(GPIOA_UART4_RX, 8U) |      \
                                     PIN_AFIO_AF(GPIOA_UART2_GPS_TX, 7U) |  \
                                     PIN_AFIO_AF(GPIOA_UART2_GPS_RX, 7U) |  \
                                     PIN_AFIO_AF(GPIOA_DCMI_HSYNC, 13U) |   \
                                     PIN_AFIO_AF(GPIOA_SPI1_SCK, 0U) |      \
                                     PIN_AFIO_AF(GPIOA_DCMI_PXCLK, 13U) |   \
                                     PIN_AFIO_AF(GPIOA_SPI1_MOSI, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_RCC_MCO_1, 0U) |     \
                                     PIN_AFIO_AF(GPIOA_UART1_TX, 7U) |      \
                                     PIN_AFIO_AF(GPIOA_UART1_RX, 7U) |      \
                                     PIN_AFIO_AF(GPIOA_UART1_CTS, 7U) |     \
                                     PIN_AFIO_AF(GPIOA_UART1_RTS, 7U) |     \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SPI6_CS1, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - CAM_RESET                 (output pushpull minimum).
 * PB1  - CAM_EN                    (output pushpull minimum).
 * PB2  - RADIO_IRQ                 (input pullup).
 * PB3  - SWO                       (alternate 0).
 * PB4  - SPI1_MISO                 (input floating).
 * PB5  - FMC_SDCKE1                (alternate 12).
 * PB6  - FMC_SDNE1                 (alternate 12).
 * PB7  - DCMI_VSYNC                (alternate 13).
 * PB8  - SD_D4                     (alternate 12).
 * PB9  - SD_D5                     (alternate 12).
 * PB10 - UART3_TX                  (alternate 7).
 * PB11 - UART3_RX                  (alternate 7).
 * PB12 - OTG_HS_ID                 (alternate 12).
 * PB13 - OTG_HS_VBUS               (input pulldown).
 * PB14 - OTG_HS_DM                 (alternate 12).
 * PB15 - OTG_HS_DP                 (alternate 12).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_CAM_RESET) |     \
                                     PIN_MODE_OUTPUT(GPIOB_CAM_EN) |        \
                                     PIN_MODE_INPUT(GPIOB_RADIO_IRQ) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_INPUT(GPIOB_SPI1_MISO) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_FMC_SDCKE1) | \
                                     PIN_MODE_ALTERNATE(GPIOB_FMC_SDNE1) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_DCMI_VSYNC) | \
                                     PIN_MODE_ALTERNATE(GPIOB_SD_D4) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_SD_D5) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_UART3_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_UART3_RX) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_ID) |  \
                                     PIN_MODE_INPUT(GPIOB_OTG_HS_VBUS) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_CAM_RESET) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAM_EN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RADIO_IRQ) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SPI1_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_FMC_SDCKE1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_FMC_SDNE1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_DCMI_VSYNC) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SD_D4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SD_D5) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_UART3_TX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_UART3_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_ID) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_VBUS) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOB_CAM_RESET) |  \
                                     PIN_OSPEED_VERYLOW(GPIOB_CAM_EN) |     \
                                     PIN_OSPEED_VERYLOW(GPIOB_RADIO_IRQ) |  \
                                     PIN_OSPEED_HIGH(GPIOB_SWO) |           \
                                     PIN_OSPEED_VERYLOW(GPIOB_SPI1_MISO) |  \
                                     PIN_OSPEED_HIGH(GPIOB_FMC_SDCKE1) |    \
                                     PIN_OSPEED_HIGH(GPIOB_FMC_SDNE1) |     \
                                     PIN_OSPEED_HIGH(GPIOB_DCMI_VSYNC) |    \
                                     PIN_OSPEED_HIGH(GPIOB_SD_D4) |         \
                                     PIN_OSPEED_HIGH(GPIOB_SD_D5) |         \
                                     PIN_OSPEED_VERYLOW(GPIOB_UART3_TX) |   \
                                     PIN_OSPEED_VERYLOW(GPIOB_UART3_RX) |   \
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_ID) |     \
                                     PIN_OSPEED_VERYLOW(GPIOB_OTG_HS_VBUS) |\
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_DM) |     \
                                     PIN_OSPEED_HIGH(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_CAM_RESET) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_CAM_EN) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_RADIO_IRQ) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_SPI1_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_FMC_SDCKE1) | \
                                     PIN_PUPDR_FLOATING(GPIOB_FMC_SDNE1) |  \
                                     PIN_PUPDR_PULLUP(GPIOB_DCMI_VSYNC) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_SD_D4) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_SD_D5) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_UART3_TX) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_UART3_RX) |     \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_ID) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOB_OTG_HS_VBUS) |\
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_CAM_RESET) |        \
                                     PIN_ODR_HIGH(GPIOB_CAM_EN) |           \
                                     PIN_ODR_HIGH(GPIOB_RADIO_IRQ) |        \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_SPI1_MISO) |        \
                                     PIN_ODR_HIGH(GPIOB_FMC_SDCKE1) |       \
                                     PIN_ODR_HIGH(GPIOB_FMC_SDNE1) |        \
                                     PIN_ODR_HIGH(GPIOB_DCMI_VSYNC) |       \
                                     PIN_ODR_HIGH(GPIOB_SD_D4) |            \
                                     PIN_ODR_HIGH(GPIOB_SD_D5) |            \
                                     PIN_ODR_HIGH(GPIOB_UART3_TX) |         \
                                     PIN_ODR_HIGH(GPIOB_UART3_RX) |         \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_ID) |        \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_VBUS) |      \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_DM) |        \
                                     PIN_ODR_HIGH(GPIOB_OTG_HS_DP))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_CAM_RESET, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_CAM_EN, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_RADIO_IRQ, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_SPI1_MISO, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_FMC_SDCKE1, 12U) |   \
                                     PIN_AFIO_AF(GPIOB_FMC_SDNE1, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_DCMI_VSYNC, 13U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_SD_D4, 12U) |        \
                                     PIN_AFIO_AF(GPIOB_SD_D5, 12U) |        \
                                     PIN_AFIO_AF(GPIOB_UART3_TX, 7U) |      \
                                     PIN_AFIO_AF(GPIOB_UART3_RX, 7U) |      \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_ID, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_VBUS, 0U) |   \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_DM, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_OTG_HS_DP, 12U))

/*
 * GPIOC setup:
 *
 * PC0  - FMC_SDNWE                 (alternate 12).
 * PC1  - HEADER_PINC1              (input pullup).
 * PC2  - HEADER_PINC2              (input pullup).
 * PC3  - HEADER_PINC3              (input pullup).
 * PC4  - ADC_VIN                   (analog).
 * PC5  - HEADER_PINC5              (input pullup).
 * PC6  - SD_D6                     (alternate 12).
 * PC7  - SD_D7                     (alternate 12).
 * PC8  - SD_D0                     (alternate 12).
 * PC9  - SD_D1                     (alternate 12).
 * PC10 - SD_D2                     (alternate 12).
 * PC11 - SD_D3                     (alternate 12).
 * PC12 - SD_CLK                    (alternate 12).
 * PC13 - HEADER_PINC13             (input pullup).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_FMC_SDNWE) |  \
                                     PIN_MODE_INPUT(GPIOC_HEADER_PINC1) |   \
                                     PIN_MODE_INPUT(GPIOC_HEADER_PINC2) |   \
                                     PIN_MODE_INPUT(GPIOC_HEADER_PINC3) |   \
                                     PIN_MODE_ANALOG(GPIOC_ADC_VIN) |       \
                                     PIN_MODE_INPUT(GPIOC_HEADER_PINC5) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D6) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D7) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D0) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D1) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D2) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_D3) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SD_CLK) |     \
                                     PIN_MODE_INPUT(GPIOC_HEADER_PINC13) |  \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_FMC_SDNWE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HEADER_PINC1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_HEADER_PINC2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_HEADER_PINC3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC_VIN) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HEADER_PINC5) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D6) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D7) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D0) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_D3) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD_CLK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HEADER_PINC13) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_FMC_SDNWE) |     \
                                     PIN_OSPEED_VERYLOW(GPIOC_HEADER_PINC1) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_HEADER_PINC2) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_HEADER_PINC3) |\
                                     PIN_OSPEED_VERYLOW(GPIOC_ADC_VIN) |    \
                                     PIN_OSPEED_VERYLOW(GPIOC_HEADER_PINC5) |\
                                     PIN_OSPEED_HIGH(GPIOC_SD_D6) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D7) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D0) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D1) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D2) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SD_D3) |         \
                                     PIN_OSPEED_HIGH(GPIOC_SD_CLK) |        \
                                     PIN_OSPEED_VERYLOW(GPIOC_HEADER_PINC13) |\
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_FMC_SDNWE) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_HEADER_PINC1) | \
                                     PIN_PUPDR_PULLUP(GPIOC_HEADER_PINC2) | \
                                     PIN_PUPDR_PULLUP(GPIOC_HEADER_PINC3) | \
                                     PIN_PUPDR_FLOATING(GPIOC_ADC_VIN) |    \
                                     PIN_PUPDR_PULLUP(GPIOC_HEADER_PINC5) | \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D6) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D7) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D0) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D1) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D2) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_D3) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_SD_CLK) |     \
                                     PIN_PUPDR_PULLUP(GPIOC_HEADER_PINC13) |\
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_FMC_SDNWE) |        \
                                     PIN_ODR_HIGH(GPIOC_HEADER_PINC1) |     \
                                     PIN_ODR_HIGH(GPIOC_HEADER_PINC2) |     \
                                     PIN_ODR_HIGH(GPIOC_HEADER_PINC3) |     \
                                     PIN_ODR_HIGH(GPIOC_ADC_VIN) |          \
                                     PIN_ODR_HIGH(GPIOC_HEADER_PINC5) |     \
                                     PIN_ODR_HIGH(GPIOC_SD_D6) |            \
                                     PIN_ODR_HIGH(GPIOC_SD_D7) |            \
                                     PIN_ODR_HIGH(GPIOC_SD_D0) |            \
                                     PIN_ODR_HIGH(GPIOC_SD_D1) |            \
                                     PIN_ODR_HIGH(GPIOC_SD_D2) |            \
                                     PIN_ODR_HIGH(GPIOC_SD_D3) |            \
                                     PIN_ODR_HIGH(GPIOC_SD_CLK) |           \
                                     PIN_ODR_HIGH(GPIOC_HEADER_PINC13) |    \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_FMC_SDNWE, 12U) |    \
                                     PIN_AFIO_AF(GPIOC_HEADER_PINC1, 0U) |  \
                                     PIN_AFIO_AF(GPIOC_HEADER_PINC2, 0U) |  \
                                     PIN_AFIO_AF(GPIOC_HEADER_PINC3, 0U) |  \
                                     PIN_AFIO_AF(GPIOC_ADC_VIN, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_HEADER_PINC5, 0U) |  \
                                     PIN_AFIO_AF(GPIOC_SD_D6, 12U) |        \
                                     PIN_AFIO_AF(GPIOC_SD_D7, 12U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SD_D0, 12U) |        \
                                     PIN_AFIO_AF(GPIOC_SD_D1, 12U) |        \
                                     PIN_AFIO_AF(GPIOC_SD_D2, 12U) |        \
                                     PIN_AFIO_AF(GPIOC_SD_D3, 12U) |        \
                                     PIN_AFIO_AF(GPIOC_SD_CLK, 12U) |       \
                                     PIN_AFIO_AF(GPIOC_HEADER_PINC13, 0U) | \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - FMC_D2                    (alternate 12).
 * PD1  - FMC_D3                    (alternate 12).
 * PD2  - SD_CMD                    (alternate 12).
 * PD3  - DCMI_D5                   (alternate 13).
 * PD4  - GPS_PPS                   (input pulldown).
 * PD5  - LED_RED                   (output pushpull minimum).
 * PD6  - LED_GREEN                 (output pushpull minimum).
 * PD7  - LED_BLUE                  (output pushpull minimum).
 * PD8  - FMC_D13                   (alternate 12).
 * PD9  - FMC_D14                   (alternate 12).
 * PD10 - FMC_D15                   (alternate 12).
 * PD11 - UART3_CTS                 (alternate 7).
 * PD12 - UART3_RTS                 (alternate 7).
 * PD13 - HEADER_PIND13             (input pullup).
 * PD14 - FMC_D0                    (alternate 12).
 * PD15 - FMC_D1                    (alternate 12).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_FMC_D2) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D3) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_SD_CMD) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_DCMI_D5) |    \
                                     PIN_MODE_INPUT(GPIOD_GPS_PPS) |        \
                                     PIN_MODE_OUTPUT(GPIOD_LED_RED) |       \
                                     PIN_MODE_OUTPUT(GPIOD_LED_GREEN) |     \
                                     PIN_MODE_OUTPUT(GPIOD_LED_BLUE) |      \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D13) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D14) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D15) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_UART3_CTS) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_UART3_RTS) |  \
                                     PIN_MODE_INPUT(GPIOD_HEADER_PIND13) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D0) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D1))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FMC_D2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SD_CMD) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_DCMI_D5) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_GPS_PPS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED_RED) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED_GREEN) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED_BLUE) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D14) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D15) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_UART3_CTS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_UART3_RTS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_HEADER_PIND13) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D1))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FMC_D2) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D3) |        \
                                     PIN_OSPEED_HIGH(GPIOD_SD_CMD) |        \
                                     PIN_OSPEED_HIGH(GPIOD_DCMI_D5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_GPS_PPS) |    \
                                     PIN_OSPEED_VERYLOW(GPIOD_LED_RED) |    \
                                     PIN_OSPEED_VERYLOW(GPIOD_LED_GREEN) |  \
                                     PIN_OSPEED_VERYLOW(GPIOD_LED_BLUE) |   \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D13) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D14) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D15) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_UART3_CTS) |  \
                                     PIN_OSPEED_VERYLOW(GPIOD_UART3_RTS) |  \
                                     PIN_OSPEED_VERYLOW(GPIOD_HEADER_PIND13) |\
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D0) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_SD_CMD) |     \
                                     PIN_PUPDR_PULLUP(GPIOD_DCMI_D5) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOD_GPS_PPS) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_LED_RED) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_LED_GREEN) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_LED_BLUE) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D13) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D14) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D15) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_UART3_CTS) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_UART3_RTS) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_HEADER_PIND13) |\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D0) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D1))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_FMC_D2) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D3) |           \
                                     PIN_ODR_HIGH(GPIOD_SD_CMD) |           \
                                     PIN_ODR_HIGH(GPIOD_DCMI_D5) |          \
                                     PIN_ODR_HIGH(GPIOD_GPS_PPS) |          \
                                     PIN_ODR_LOW(GPIOD_LED_RED) |           \
                                     PIN_ODR_LOW(GPIOD_LED_GREEN) |         \
                                     PIN_ODR_LOW(GPIOD_LED_BLUE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D13) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D14) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D15) |          \
                                     PIN_ODR_HIGH(GPIOD_UART3_CTS) |        \
                                     PIN_ODR_HIGH(GPIOD_UART3_RTS) |        \
                                     PIN_ODR_HIGH(GPIOD_HEADER_PIND13) |    \
                                     PIN_ODR_HIGH(GPIOD_FMC_D0) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FMC_D2, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D3, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_SD_CMD, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_DCMI_D5, 13U) |      \
                                     PIN_AFIO_AF(GPIOD_GPS_PPS, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_LED_RED, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_LED_GREEN, 0U) |     \
                                     PIN_AFIO_AF(GPIOD_LED_BLUE, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_FMC_D13, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D14, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D15, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_UART3_CTS, 7U) |     \
                                     PIN_AFIO_AF(GPIOD_UART3_RTS, 7U) |     \
                                     PIN_AFIO_AF(GPIOD_HEADER_PIND13, 0U) | \
                                     PIN_AFIO_AF(GPIOD_FMC_D0, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D1, 12U))

/*
 * GPIOE setup:
 *
 * PE0  - FMC_NBL0                  (alternate 12).
 * PE1  - FMC_NBL1                  (alternate 12).
 * PE2  - HEADER_PINE2              (input pullup).
 * PE3  - HEADER_PINE3              (input pullup).
 * PE4  - DCMI_D4                   (alternate 13).
 * PE5  - DCMI_D6                   (alternate 13).
 * PE6  - DCMI_D7                   (alternate 13).
 * PE7  - FMC_D4                    (alternate 12).
 * PE8  - FMC_D5                    (alternate 12).
 * PE9  - FMC_D6                    (alternate 12).
 * PE10 - FMC_D7                    (alternate 12).
 * PE11 - FMC_D8                    (alternate 12).
 * PE12 - FMC_D9                    (alternate 12).
 * PE13 - FMC_D10                   (alternate 12).
 * PE14 - FMC_D11                   (alternate 12).
 * PE15 - FMC_D12                   (alternate 12).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_FMC_NBL0) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_NBL1) |   \
                                     PIN_MODE_INPUT(GPIOE_HEADER_PINE2) |   \
                                     PIN_MODE_INPUT(GPIOE_HEADER_PINE3) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_DCMI_D4) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_DCMI_D6) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_DCMI_D7) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D4) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D5) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D6) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D7) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D8) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D9) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D10) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D11) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D12))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_HEADER_PINE2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_HEADER_PINE3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_DCMI_D4) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_DCMI_D6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_DCMI_D7) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D9) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D12))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_FMC_NBL0) |      \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_NBL1) |      \
                                     PIN_OSPEED_VERYLOW(GPIOE_HEADER_PINE2) |\
                                     PIN_OSPEED_VERYLOW(GPIOE_HEADER_PINE3) |\
                                     PIN_OSPEED_VERYLOW(GPIOE_DCMI_D4) |    \
                                     PIN_OSPEED_HIGH(GPIOE_DCMI_D6) |       \
                                     PIN_OSPEED_HIGH(GPIOE_DCMI_D7) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D4) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D5) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D6) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D7) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D8) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D9) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D10) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D11) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1) |   \
                                     PIN_PUPDR_PULLUP(GPIOE_HEADER_PINE2) | \
                                     PIN_PUPDR_PULLUP(GPIOE_HEADER_PINE3) | \
                                     PIN_PUPDR_PULLUP(GPIOE_DCMI_D4) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_DCMI_D6) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_DCMI_D7) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D4) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D5) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D6) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D7) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D8) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D9) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D10) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D11) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D12))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_FMC_NBL0) |         \
                                     PIN_ODR_HIGH(GPIOE_FMC_NBL1) |         \
                                     PIN_ODR_HIGH(GPIOE_HEADER_PINE2) |     \
                                     PIN_ODR_HIGH(GPIOE_HEADER_PINE3) |     \
                                     PIN_ODR_HIGH(GPIOE_DCMI_D4) |          \
                                     PIN_ODR_HIGH(GPIOE_DCMI_D6) |          \
                                     PIN_ODR_HIGH(GPIOE_DCMI_D7) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D4) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D5) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D6) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D7) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D8) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D9) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D10) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D11) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_FMC_NBL0, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_FMC_NBL1, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_HEADER_PINE2, 0U) |  \
                                     PIN_AFIO_AF(GPIOE_HEADER_PINE3, 0U) |  \
                                     PIN_AFIO_AF(GPIOE_DCMI_D4, 13U) |      \
                                     PIN_AFIO_AF(GPIOE_DCMI_D6, 13U) |      \
                                     PIN_AFIO_AF(GPIOE_DCMI_D7, 13U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D4, 12U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_FMC_D5, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D6, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D7, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D8, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D9, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D10, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D11, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D12, 12U))

/*
 * GPIOF setup:
 *
 * PF0  - FMC_A0                    (alternate 12).
 * PF1  - FMC_A1                    (alternate 12).
 * PF2  - FMC_A2                    (alternate 12).
 * PF3  - FMC_A3                    (alternate 12).
 * PF4  - FMC_A4                    (alternate 12).
 * PF5  - FMC_A5                    (alternate 12).
 * PF6  - LASERCOM_TX               (input pulldown).
 * PF7  - LASERCOM_RX               (input pulldown).
 * PF8  - SPI5_MISO                 (alternate 5).
 * PF9  - SPI5_MOSI                 (alternate 5).
 * PF10 - SPI5_SC1                  (output pushpull maximum).
 * PF11 - FMC_SDNRAS                (alternate 12).
 * PF12 - FMC_A6                    (alternate 12).
 * PF13 - FMC_A7                    (alternate 12).
 * PF14 - FMC_A8                    (alternate 12).
 * PF15 - FMC_A9                    (alternate 12).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ALTERNATE(GPIOF_FMC_A0) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A1) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A2) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A3) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A4) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A5) |     \
                                     PIN_MODE_INPUT(GPIOF_LASERCOM_TX) |    \
                                     PIN_MODE_INPUT(GPIOF_LASERCOM_RX) |    \
                                     PIN_MODE_ALTERNATE(GPIOF_SPI5_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOF_SPI5_MOSI) |  \
                                     PIN_MODE_OUTPUT(GPIOF_SPI5_SC1) |      \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_SDNRAS) | \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A6) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A7) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A8) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A9))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_FMC_A0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_LASERCOM_TX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_LASERCOM_RX) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SPI5_SC1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_SDNRAS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A9))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_FMC_A0) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A1) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A2) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A3) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A4) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A5) |        \
                                     PIN_OSPEED_VERYLOW(GPIOF_LASERCOM_TX) |\
                                     PIN_OSPEED_VERYLOW(GPIOF_LASERCOM_RX) |\
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_MOSI) |     \
                                     PIN_OSPEED_HIGH(GPIOF_SPI5_SC1) |      \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_SDNRAS) |    \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A6) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A7) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A8) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_FMC_A0) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A1) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A2) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A3) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A4) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A5) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOF_LASERCOM_TX) |\
                                     PIN_PUPDR_PULLDOWN(GPIOF_LASERCOM_RX) |\
                                     PIN_PUPDR_FLOATING(GPIOF_SPI5_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_SPI5_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_SPI5_SC1) |   \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_SDNRAS) | \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A6) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A7) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A8) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A9))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_FMC_A0) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A1) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A2) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A3) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A4) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A5) |           \
                                     PIN_ODR_HIGH(GPIOF_LASERCOM_TX) |      \
                                     PIN_ODR_LOW(GPIOF_LASERCOM_RX) |       \
                                     PIN_ODR_HIGH(GPIOF_SPI5_MISO) |        \
                                     PIN_ODR_HIGH(GPIOF_SPI5_MOSI) |        \
                                     PIN_ODR_LOW(GPIOF_SPI5_SC1) |          \
                                     PIN_ODR_HIGH(GPIOF_FMC_SDNRAS) |       \
                                     PIN_ODR_HIGH(GPIOF_FMC_A6) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A7) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A8) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_FMC_A0, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A1, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A2, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A3, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A4, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A5, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_LASERCOM_TX, 0U) |   \
                                     PIN_AFIO_AF(GPIOF_LASERCOM_RX, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_SPI5_MISO, 5U) |     \
                                     PIN_AFIO_AF(GPIOF_SPI5_MOSI, 5U) |     \
                                     PIN_AFIO_AF(GPIOF_SPI5_SC1, 0U) |      \
                                     PIN_AFIO_AF(GPIOF_FMC_SDNRAS, 12U) |   \
                                     PIN_AFIO_AF(GPIOF_FMC_A6, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A7, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A8, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A9, 12U))

/*
 * GPIOG setup:
 *
 * PG0  - FMC_A10                   (alternate 12).
 * PG1  - FMC_A11                   (alternate 12).
 * PG2  - FMC_A12                   (alternate 12).
 * PG3  - SPI1_CS1                  (output pushpull maximum).
 * PG4  - FMC_BA0                   (alternate 12).
 * PG5  - FMC_BA1                   (alternate 12).
 * PG6  - RADIO_GPIO1               (input pullup).
 * PG7  - RADIO_GPIO0               (input pullup).
 * PG8  - FMC_SDCLK                 (alternate 12).
 * PG9  - PIN9                      (input pullup).
 * PG10 - DCMI_D2                   (alternate 13).
 * PG11 - DCMI_D3                   (alternate 13).
 * PG12 - SPI6_MISO                 (alternate 5).
 * PG13 - SPI6_SCK                  (alternate 5).
 * PG14 - SPI6_MOSI                 (alternate 5).
 * PG15 - FMC_SDNCAS                (alternate 12).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ALTERNATE(GPIOG_FMC_A10) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A11) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A12) |    \
                                     PIN_MODE_OUTPUT(GPIOG_SPI1_CS1) |      \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_BA0) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_BA1) |    \
                                     PIN_MODE_INPUT(GPIOG_RADIO_GPIO1) |    \
                                     PIN_MODE_INPUT(GPIOG_RADIO_GPIO0) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDCLK) |  \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_ALTERNATE(GPIOG_DCMI_D2) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_DCMI_D3) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_SPI6_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_SPI6_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOG_SPI6_MOSI) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_FMC_A10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A12) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_SPI1_CS1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_BA0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_BA1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_RADIO_GPIO1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_RADIO_GPIO0) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDCLK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_DCMI_D2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_DCMI_D3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_SPI6_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_SPI6_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOG_SPI6_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_FMC_A10) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A11) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A12) |       \
                                     PIN_OSPEED_HIGH(GPIOG_SPI1_CS1) |      \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_BA0) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_BA1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_RADIO_GPIO1) |\
                                     PIN_OSPEED_VERYLOW(GPIOG_RADIO_GPIO0) |\
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDCLK) |     \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_DCMI_D2) |       \
                                     PIN_OSPEED_HIGH(GPIOG_DCMI_D3) |       \
                                     PIN_OSPEED_HIGH(GPIOG_SPI6_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOG_SPI6_SCK) |      \
                                     PIN_OSPEED_HIGH(GPIOG_SPI6_MOSI) |     \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_SPI1_CS1) |   \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA0) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_BA1) |    \
                                     PIN_PUPDR_PULLUP(GPIOG_RADIO_GPIO1) |  \
                                     PIN_PUPDR_PULLUP(GPIOG_RADIO_GPIO0) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDCLK) |  \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_DCMI_D2) |      \
                                     PIN_PUPDR_PULLUP(GPIOG_DCMI_D3) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_SPI6_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_SPI6_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOG_SPI6_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_FMC_A10) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A11) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A12) |          \
                                     PIN_ODR_LOW(GPIOG_SPI1_CS1) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_BA0) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_BA1) |          \
                                     PIN_ODR_HIGH(GPIOG_RADIO_GPIO1) |      \
                                     PIN_ODR_HIGH(GPIOG_RADIO_GPIO0) |      \
                                     PIN_ODR_HIGH(GPIOG_FMC_SDCLK) |        \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_DCMI_D2) |          \
                                     PIN_ODR_HIGH(GPIOG_DCMI_D3) |          \
                                     PIN_ODR_HIGH(GPIOG_SPI6_MISO) |        \
                                     PIN_ODR_HIGH(GPIOG_SPI6_SCK) |         \
                                     PIN_ODR_HIGH(GPIOG_SPI6_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOG_FMC_SDNCAS))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_FMC_A10, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A11, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A12, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_SPI1_CS1, 0U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_BA0, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_BA1, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_RADIO_GPIO1, 0U) |   \
                                     PIN_AFIO_AF(GPIOG_RADIO_GPIO0, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_FMC_SDCLK, 12U) |    \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_DCMI_D2, 13U) |      \
                                     PIN_AFIO_AF(GPIOG_DCMI_D3, 13U) |      \
                                     PIN_AFIO_AF(GPIOG_SPI6_MISO, 5U) |     \
                                     PIN_AFIO_AF(GPIOG_SPI6_SCK, 5U) |      \
                                     PIN_AFIO_AF(GPIOG_SPI6_MOSI, 5U) |     \
                                     PIN_AFIO_AF(GPIOG_FMC_SDNCAS, 12U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - I2C2_SCL                  (alternate 4).
 * PH5  - I2C2_SDA                  (alternate 4).
 * PH6  - PIN6                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - DCMI_D0                   (alternate 13).
 * PH10 - DCMI_D1                   (alternate 1).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_ALTERNATE(GPIOH_I2C2_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOH_I2C2_SDA) |   \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_ALTERNATE(GPIOH_DCMI_D0) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_DCMI_D1) |    \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOH_I2C2_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOH_I2C2_SDA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_DCMI_D0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_DCMI_D1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN3) |       \
                                     PIN_OSPEED_HIGH(GPIOH_I2C2_SCL) |      \
                                     PIN_OSPEED_HIGH(GPIOH_I2C2_SDA) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) |       \
                                     PIN_OSPEED_HIGH(GPIOH_DCMI_D0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_DCMI_D1) |    \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOH_I2C2_SCL) |   \
                                     PIN_PUPDR_PULLUP(GPIOH_I2C2_SDA) |     \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_DCMI_D0) |      \
                                     PIN_PUPDR_PULLUP(GPIOH_DCMI_D1) |      \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_I2C2_SCL) |         \
                                     PIN_ODR_HIGH(GPIOH_I2C2_SDA) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_DCMI_D0) |          \
                                     PIN_ODR_HIGH(GPIOH_DCMI_D1) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_I2C2_SCL, 4U) |      \
                                     PIN_AFIO_AF(GPIOH_I2C2_SDA, 4U) |      \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_DCMI_D0, 13U) |      \
                                     PIN_AFIO_AF(GPIOH_DCMI_D1, 1U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOI_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
