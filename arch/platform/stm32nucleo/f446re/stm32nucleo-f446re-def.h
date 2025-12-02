/**
 * @file stm32nucleo-f446re-def.h
 * @brief STM32 Nucleo-F446RE board definitions for Contiki-NG
 *
 * This file contains board-specific definitions that users should NOT modify.
 * It includes LED/button pin mappings, on-board peripheral definitions,
 * and other hardware constants specific to the Nucleo-F446RE board.
 */

#ifndef STMUCLEO_F446RE_DEF_H_
#define STMUCLEO_F446RE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== LED Definitions ==================== */

/**
 * @brief User LED on Nucleo-F446RE (LD2)
 * Green LED connected to PA5
 */
#define LED_GREEN_PORT   GPIOA
#define LED_GREEN_PIN    GPIO_PIN_5
#define LED_GREEN_ACTIVE_HIGH 1

/* ==================== Button Definitions ==================== */

/**
 * @brief User Button on Nucleo-F446RE
 * Blue button connected to PC13
 * Active LOW (button press pulls pin to ground)
 */
#define BUTTON_USER_PORT   GPIOC
#define BUTTON_USER_PIN    GPIO_PIN_13
#define BUTTON_USER_ACTIVE_LOW 1

/* ==================== UART Definitions ==================== */

/**
 * @brief Debug UART on Nucleo-F446RE
 * USART2: Connected to ST-LINK virtual COM port
 * - TX: PA2 (AF7)
 * - RX: PA3 (AF7)
 * - Baud rate: 115200
 * - This is the primary debug console
 */
#define DBG_UART_INSTANCE USART2
#define DBG_UART_BAUDRATE 115200
#define DBG_UART_TXPIN GPIO_PIN_2
#define DBG_UART_RXPIN GPIO_PIN_3
#define DBG_UART_PORT GPIOA

/**
 * @brief Alternative UART instances available on Nucleo-F446RE
 * Can be used for additional serial communication or sensor interfacing
 *
 * UART1: PB6 (TX) / PB7 (RX) - 45 MHz (APB1)
 * UART3: PB10 (TX) / PB11 (RX) - 45 MHz (APB1)
 * UART4: PA0 (TX) / PA1 (RX) - 45 MHz (APB1)
 * UART5: PC12 (TX) / PD2 (RX) - 45 MHz (APB1)
 */

/* ==================== SPI Definitions ==================== */

/**
 * @brief SPI1 pins on Nucleo-F446RE
 * PA5 (SCK), PA6 (MISO), PA7 (MOSI)
 * WARNING: PA5 is also used for LED_GREEN
 * Ensure only one is used at a time
 */

/* ==================== I2C Definitions ==================== */

/**
 * @brief I2C1 pins on Nucleo-F446RE
 * PB8 (SCL), PB9 (SDA)
 * Can be used for connecting I2C sensors
 */

/* ==================== Clock Configuration ==================== */

/**
 * @brief External oscillator frequency (HSE)
 * Nucleo boards use 25 MHz oscillator
 * This value is used by HAL for clock calculations
 */
#define HSE_VALUE       ((uint32_t)25000000)

/**
 * @brief System clock frequency after PLL
 * Nucleo-F446RE can run at maximum 180 MHz
 * Set via PLL configuration in soc.c
 */
#define SYSCLK_FREQ     ((uint32_t)180000000)

/* ==================== On-Board Features ==================== */

/**
 * @brief ST-LINK debugger presence
 * Nucleo boards have on-board ST-LINK for SWD debugging
 */
#define ONBOARD_STLINK 1

/**
 * @brief USB device connector
 * Nucleo-F446RE has a USB Type-A connector (mini-USB)
 * Connected to USB_OTG_FS (FS = full-speed, not HS)
 * Available pins: PA11 (DM), PA12 (DP)
 */
#define USB_OTG_FS_ENABLED 0  /* Disabled by default, enable if needed */

#ifdef __cplusplus
}
#endif

#endif /* STMUCLEO_F446RE_DEF_H_ */
