/**
 * @file stm32nucleo-f446re-conf.h
 * @brief STM32 Nucleo-F446RE board configuration for Contiki-NG
 *
 * This file contains board-specific configuration that users CAN modify.
 * Board features, optional drivers, and board-specific settings go here.
 */

#ifndef STMUCLEO_F446RE_CONF_H_
#define STMUCLEO_F446RE_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== Board Identification ==================== */

/**
 * @brief Board name for identification
 */
#define BOARD_NAME "STM32 Nucleo-F446RE"

/* ==================== LED Support ==================== */

/**
 * @brief Enable LED driver for user LED (LD2 on PA5)
 * Set to 1 to enable leds module support
 */
#define LEDS_CONF_ALL 1

/**
 * @brief LED color definitions
 * Only LD2 (green) is available on Nucleo-F446RE
 */
#define LEDS_CONF_GREEN 1
#define LEDS_CONF_RED 0
#define LEDS_CONF_BLUE 0

/* ==================== Button Support ==================== */

/**
 * @brief Enable button driver for user button (PC13)
 * Set to 1 to enable button-hal support
 */
#define BUTTON_CONF_USER 1

/* ==================== UART Configuration ==================== */

/**
 * @brief Enable debug UART (USART2)
 */
#define UART_CONF_ENABLED 1

/**
 * @brief Debug output UART instance
 */
#define DEBUG_UART USART2

/**
 * @brief Debug UART baud rate
 * Standard IoT debugging rate: 115200 baud
 */
#define DEBUG_UART_BAUDRATE 115200

/* ==================== SPI Configuration ==================== */

/**
 * @brief Enable SPI support if needed
 * Uncomment to add SPI driver for external devices
 */
/* #define SPI_CONF_ENABLED 1 */

/* ==================== I2C Configuration ==================== */

/**
 * @brief Enable I2C support if needed
 * Uncomment to add I2C driver for external devices
 */
/* #define I2C_CONF_ENABLED 1 */

/* ==================== Network Configuration ==================== */

/**
 * @brief External radio device support
 * If using an external IEEE 802.15.4 radio module, configure here
 * Uncomment and configure for your radio (CC2520, RFM69, etc.)
 */
/* #define RADIO_CONF_EXT 1 */

/* ==================== Power Management ==================== */

/**
 * @brief Enable low-power idle mode
 * Set to 1 to enable platform_idle() sleep when system is idle
 * 0 = run continuously (useful for debugging)
 * 1 = sleep when idle (reduces power consumption)
 */
#define PLATFORM_CONF_LOW_POWER 0

/**
 * @brief Sleep mode configuration
 * 0 = run continuously (default)
 * 1 = enable sleep when idle
 */
#define SLEEP_CONF_MODE 0

#ifdef __cplusplus
}
#endif

#endif /* STMUCLEO_F446RE_CONF_H_ */
