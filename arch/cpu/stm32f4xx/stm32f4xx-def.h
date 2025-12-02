/**
 * \defgroup stm32f4xx STM32F4 MCU Definitions
 * @{
 */

/**
 * \file
 * STM32F4 series MCU definitions for Contiki-NG using STM32 HAL
 *
 * This file provides MCU-specific definitions that users should NOT modify.
 * It includes system clock configuration, memory constraints, and hardware
 * characteristics.
 *
 * This file is included early in the configuration chain (from contiki-conf.h)
 * and provides non-configurable MCU definitions.
 */

#ifndef STM32F4XX_DEF_H_
#define STM32F4XX_DEF_H_

#include <stdint.h>
#include "stm32f4xx.h"

/* ==================== System Clock Definitions ==================== */

/**
 * @brief Contiki-NG software clock tick frequency
 * Number of software ticks per second
 */
#define CLOCK_CONF_SECOND 128

/**
 * @brief Contiki-NG software clock tick size
 * Size of the tick variable (4 bytes = 32-bit)
 */
#define CLOCK_CONF_SIZE 4

/**
 * @brief CPU frequency for STM32F446RE at maximum performance
 * Nucleo-F446RE operates at 180 MHz via PLL
 */
#define CPU_FREQ 180000000UL

/**
 * @brief APB1 peripheral bus clock
 * STM32F446: CPU_FREQ / 4 = 45 MHz
 * Used for UART, SPI, I2C, timers on APB1
 */
#define APB1_FREQ 45000000UL

/**
 * @brief APB2 peripheral bus clock
 * STM32F446: CPU_FREQ / 2 = 90 MHz
 * Used for UART, SPI, I2C, timers on APB2
 */
#define APB2_FREQ 90000000UL

/* ==================== Real-Time Timer ==================== */

/**
 * @brief Real-time interval timer frequency
 * STM32F4 rtimer uses microsecond resolution
 */
#define RTIMER_ARCH_SECOND 1000000UL

/* ==================== Memory Constraints ==================== */

/**
 * @brief STM32F446RE Flash memory size: 512 KB
 */
#define FLASH_SIZE (512 * 1024)

/**
 * @brief STM32F446RE SRAM size: 128 KB
 */
#define SRAM_SIZE (128 * 1024)

/* ==================== UART Configuration ==================== */

/**
 * @brief Default UART baud rate for debug output (USART2)
 */
#define DBG_UART_BAUDRATE 115200

/**
 * @brief UART instance used for debug output on Nucleo-F446RE
 * USART2 is connected to ST-LINK virtual COM port via PA2 (TX) / PA3 (RX)
 */
#define DBG_UART_INSTANCE USART2

/* ==================== ARM Cortex-M4 Features ==================== */

/**
 * @brief ARM Cortex-M4 with FPU support
 */
#define CPU_SUPPORTS_ARM_THUMB 1
#define CPU_SUPPORTS_FPU 1

/**
 * @brief CPU supports native ARM Cortex mutex operations via LDREX/STREX
 */
#define CPU_SUPPORTS_MUTEX 1

#endif /* STM32F4XX_DEF_H_ */

/** @} */