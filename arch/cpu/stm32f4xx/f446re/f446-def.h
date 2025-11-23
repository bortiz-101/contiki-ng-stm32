/*
 * Copyright (c) 2024, Contiki-NG Contributors
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Contiki-NG project nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*---------------------------------------------------------------------------*/
/**
 * \addtogroup stm32f4xx
 * @{
 *
 * \defgroup stm32f446re STM32F446RE MCU
 *
 * @{
 *
 * \file
 *  STM32F446RE MCU-specific definitions, constants, and macros.
 *  These are immutable values determined by the hardware and should not be
 *  modified by the user.
 * 
 * Registry Map can be found in RM0390 Reference Manual:
 * STM32F446xx advanced ARM®-based 32-bit MCUs
 * https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
 */
/*---------------------------------------------------------------------------*/
#ifndef F446_DEF_H_
#define F446_DEF_H_
/*---------------------------------------------------------------------------*/
#include <stdint.h>
/*---------------------------------------------------------------------------*/
/**
 * \name STM32F446RE Device Specifications
 * @{
 */

/* STM32F446RE core and memory specifications */
#define MCU_FAMILY              "STM32F4xx"
#define MCU_MODEL               "STM32F446RE"

/* Core specifications */
#define MCU_CORE                "ARM Cortex-M4"
#define MCU_CORE_CLOCK          180000000UL  /* 180 MHz maximum */
#define MCU_FLASH_SIZE          0x80000      /* 512 KB */
#define MCU_SRAM_SIZE           0x20000      /* 128 KB */

/* Clock configuration */
#define HSE_VALUE               8000000UL    /* 8 MHz external oscillator on Nucleo */
#define HSI_VALUE               16000000UL   /* 16 MHz internal oscillator */
#define LSE_VALUE               32768UL      /* 32.768 kHz external oscillator */

/* System clock tree defaults */
#define SYSTEM_CLOCK            180000000UL  /* Target system clock */
#define AHB_CLOCK               180000000UL  /* AHB clock */
#define APB1_CLOCK              45000000UL   /* APB1 clock (max 45 MHz) */
#define APB2_CLOCK              90000000UL   /* APB2 clock (max 90 MHz) */

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Peripheral Base Addresses
 * @{
 */

/* UART peripheral base addresses */
#define USART1_BASE             0x40011000UL
#define USART2_BASE             0x40004400UL
#define USART3_BASE             0x40004800UL
#define UART4_BASE              0x40004C00UL
#define UART5_BASE              0x40005000UL
#define USART6_BASE             0x40011400UL

/* SPI peripheral base addresses */
#define SPI1_BASE               0x40013000UL
#define SPI2_BASE               0x40003800UL
#define SPI3_BASE               0x40003C00UL
#define SPI4_BASE               0x40013400UL

/* I2C peripheral base addresses */
#define I2C1_BASE               0x40005400UL
#define I2C2_BASE               0x40005800UL
#define I2C3_BASE               0x40005C00UL

/* Timer peripheral base addresses */
#define TIM1_BASE               0x40010000UL
#define TIM2_BASE               0x40000000UL
#define TIM3_BASE               0x40000400UL
#define TIM4_BASE               0x40000800UL
#define TIM5_BASE               0x40000C00UL
#define TIM6_BASE               0x40001000UL
#define TIM7_BASE               0x40001400UL
#define TIM8_BASE               0x40010400UL
#define TIM9_BASE               0x40014000UL
#define TIM10_BASE              0x40014400UL
#define TIM11_BASE              0x40014800UL
#define TIM12_BASE              0x40001800UL
#define TIM13_BASE              0x40001C00UL
#define TIM14_BASE              0x40002000UL

/* RTC peripheral base address */
#define RTC_BASE                0x40002800UL

/* GPIO peripheral base addresses */
#define GPIOA_BASE              0x40020000UL
#define GPIOB_BASE              0x40020400UL
#define GPIOC_BASE              0x40020800UL
#define GPIOD_BASE              0x40020C00UL
#define GPIOE_BASE              0x40021000UL
#define GPIOF_BASE              0x40021400UL
#define GPIOG_BASE              0x40021800UL
#define GPIOH_BASE              0x40021C00UL

/* ADC peripheral base addresses */
#define ADC1_BASE               0x40012000UL
#define ADC2_BASE               0x40012100UL
#define ADC3_BASE               0x40012200UL

/* DAC peripheral base address */
#define DAC_BASE                0x40007400UL

/* CAN peripheral base addresses */
#define CAN1_BASE               0x40006400UL
#define CAN2_BASE               0x40006800UL

/* WWDG and IWDG base addresses */
#define WWDG_BASE               0x40002C00UL
#define IWDG_BASE               0x40003000UL

/* System control block */
#define SCB_BASE                0xE000ED00UL
#define SYSTICK_BASE            0xE000E010UL
#define NVIC_BASE               0xE000E100UL

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Contiki-NG Configuration
 * @{
 */

/* Clock configuration for Contiki-NG */
#define CLOCK_CONF_SIZE         4                /* 32-bit clock counter */
#define CLOCK_CONF_SECOND       128              /* 128 ticks per second */

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name UART Configuration
 * @{
 */

/* Default UART for debugging/console output */
#define UART_DEBUG_UNIT         1                /* USART1 */
#define UART_DEBUG_BAUDRATE     115200
#define UART_DEBUG_TX_PORT      'A'              /* PA9 */
#define UART_DEBUG_TX_PIN       9
#define UART_DEBUG_RX_PORT      'A'              /* PA10 */
#define UART_DEBUG_RX_PIN       10

/* Alternative UART ports on STM32F446RE */
#define UART1_TX_PORT           'A'
#define UART1_TX_PIN            9
#define UART1_RX_PORT           'A'
#define UART1_RX_PIN            10

/* UART2: PD5 (TX), PD6 (RX) - Alternative: PA2 (TX), PA3 (RX) */
#define UART2_TX_PORT           'A'
#define UART2_TX_PIN            2
#define UART2_RX_PORT           'A'
#define UART2_RX_PIN            3

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Timer Configuration
 * @{
 */

/* Timer used for Contiki-NG system clock (via SysTick) */
#define SYSTICK_TIMER_BASE      SYSTICK_BASE
#define SYSTICK_CLOCK           AHB_CLOCK      /* SysTick uses AHB clock */

/* Timer used for real-time interrupts (MAC/radio timing) */
#define RTIMER_TIMER            TIM2           /* Use Timer 2 for rtimer */
#define RTIMER_TIMER_BASE       TIM2_BASE
#define RTIMER_TIMER_IRQ        TIM2_IRQn

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Interrupt Configuration
 * @{
 */

/* Number of interrupt handlers supported by NVIC */
#define NVIC_INTERRUPT_COUNT    84

/* SysTick interrupt priority (0 = highest, 255 = lowest) */
#define SYSTICK_INT_PRIORITY    0xFF           /* Lowest priority */

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name GPIO Configuration
 * @{
 */

/* LED GPIO configuration for STM32 Nucleo-F446RE board */
#define LED_GREEN_PORT          'A'
#define LED_GREEN_PIN           5              /* User LED LD2 on Nucleo */

/* Button GPIO configuration for STM32 Nucleo-F446RE board */
#define BUTTON_PORT             'C'
#define BUTTON_PIN              13             /* User Button (RESET if not available) */

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Memory Layout
 * @{
 */

/* Stack configuration (linker script defines stack end) */
#define STACK_ORIGIN            0x20000000 + MCU_SRAM_SIZE  /* Top of SRAM */

/* Heap configuration */
#define HEAP_SIZE               0x2000         /* 8 KB heap */

/** @} */
/*---------------------------------------------------------------------------*/
#endif /* F446_DEF_H_ */
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
