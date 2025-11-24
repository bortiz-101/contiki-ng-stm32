/**
 * \file
 * Minimal STM32F4xx device header for barebones port
 * 
 * This file provides basic register definitions and memory addresses
 * without pulling in the full STM32 HAL library. This allows Contiki-NG
 * to be ported to STM32F4 with minimal dependencies.
 *
 * For a production system, you would typically include the official
 * STM32F4xx_StdPeriph_Driver headers or the newer STM32CubeF4 HAL.
 *
 * Register definitions are in the following files:
 * - system_stm32f4xx.h: System/clock control registers
 * - f446-def.h: Device-specific constants
 */

#ifndef STM32F4XX_H_
#define STM32F4XX_H_

#include <stdint.h>

/* Memory addresses for STM32F446RE */
#define FLASH_BASE        0x08000000UL
#define SRAM_BASE         0x20000000UL
#define PERIPH_BASE       0x40000000UL

/* Peripheral block addresses */
#define AHB1PERIPH_BASE   (PERIPH_BASE + 0x00000000UL)
#define AHB2PERIPH_BASE   (PERIPH_BASE + 0x10000000UL)
#define APB1PERIPH_BASE   (PERIPH_BASE + 0x00000000UL)
#define APB2PERIPH_BASE   (PERIPH_BASE + 0x00010000UL)

/* RCC is in AHB1 at offset 0x3800 */
#define RCC_BASE          (AHB1PERIPH_BASE + 0x3800UL)

/* GPIO ports in AHB1 */
#define GPIOA_BASE        (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE        (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE        (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE        (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE        (AHB1PERIPH_BASE + 0x1000UL)

/* USART ports in APB1 and APB2 */
#define USART1_BASE       (APB2PERIPH_BASE + 0x1000UL)
#define USART2_BASE       (APB1PERIPH_BASE + 0x4400UL)
#define USART3_BASE       (APB1PERIPH_BASE + 0x4800UL)
#define USART4_BASE       (APB1PERIPH_BASE + 0x4C00UL)
#define USART5_BASE       (APB1PERIPH_BASE + 0x5000UL)
#define USART6_BASE       (APB2PERIPH_BASE + 0x1400UL)

/* Timers in APB1 and APB2 */
#define TIM2_BASE         (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE         (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE         (APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE         (APB1PERIPH_BASE + 0x0C00UL)

/* SysTick is part of the Cortex-M4 core */
#define SYSTICK_BASE      0xE000E010UL

#endif /* STM32F4XX_H_ */
