/*
 * Copyright (c) 2024, Contiki-NG STM32F4 Port Contributors
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
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \addtogroup stm32f4xx-soc
 * @{
 *
 * \file
 * Implementation of STM32F4xx SoC initialization using STM32 HAL
 *
 * This file handles:
 * - MCU reset and system clock initialization
 * - NVIC configuration for interrupt handling
 * - Basic peripheral clock setup
 * - Power management configuration
 */

#include "contiki.h"
#include "soc.h"

#include <inttypes.h>
#include <stdint.h>

/* STM32 HAL includes */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_rcc_ex.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_pwr_ex.h"
#include "stm32f4xx_hal_flash.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "STM32F4 SoC"
#define LOG_LEVEL LOG_LEVEL_NONE

/*---------------------------------------------------------------------------*/
/**
 * \brief System clock configuration for STM32F446RE
 *
 * Configures the system to run at 180 MHz using the PLL with HSE (25 MHz).
 * - HSE input: 25 MHz (Nucleo-F446RE onboard oscillator)
 * - PLL multiplier: M=25, N=360, P=2 → 180 MHz
 * - APB1 divisor: 4 (45 MHz) - timers, UART
 * - APB2 divisor: 2 (90 MHz) - timers, SPI
 * - AHB divisor: 1 (180 MHz) - CPU, DMA
 *
 * Uses STM32 HAL for clock configuration to ensure correctness
 * and compatibility with vendor updates.
 */
static void
stm32f4_clock_init(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Configure the main internal regulator output voltage to scale 3 */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitStruct structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    /* Clock configuration error - halt */
    LOG_ERR("HSE/PLL configuration failed\n");
    while (1) {
      ;
    }
  }

  /** Activate the Over-Drive mode */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    LOG_ERR("Over-Drive enable failed\n");
    while (1) {
      ;
    }
  }

  /** Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    LOG_ERR("Clock configuration failed\n");
    while (1) {
      ;
    }
  }

  LOG_DBG("System clock: 180 MHz, APB1: 45 MHz, APB2: 90 MHz\n");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize the System-on-Chip (SoC)
 *
 * Called from platform_init_stage_one() to set up:
 * 1. HAL system initialization (HAL_Init)
 * 2. System clock configuration via PLL
 * 3. NVIC interrupt controller setup
 * 4. Basic peripheral clocks
 *
 * This uses the STM32 HAL extensively for portability and correctness.
 * Must be called before any other HAL functions are used.
 */
void
soc_init(void)
{
  /* ========== STEP 1: HAL System Initialization ==========
   * HAL_Init() resets all peripherals, initializes the Flash interface,
   * and configures the SysTick timer at 1 ms interval.
   * This MUST be called before any HAL functions.
   */
  if (HAL_Init() != HAL_OK) {
    LOG_ERR("HAL_Init() failed!\n");
    while (1) {
      ;
    }
  }

  /* ========== STEP 2: System Clock Configuration ==========
   * Configure clocks for 180 MHz operation via PLL.
   * This function is critical for all timing and peripheral clocks.
   */
  stm32f4_clock_init();

  /* ========== STEP 3: NVIC Priority Grouping ==========
   * Configure NVIC to use priority group 0 (8 preemption levels, 0 sublevels).
   * This is typically set once at startup and shouldn't be changed later.
   */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* ========== STEP 4: Peripheral Clock Enable ==========
   * Enable clock for GPIO (needed for any pin access).
   * Additional peripheral clocks are enabled by individual drivers
   * (UART driver enables UART clocks, etc.)
   */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  LOG_DBG("SoC initialized: SystemCoreClock = %" PRIu32 " Hz\n",
          SystemCoreClock);
}

/*---------------------------------------------------------------------------*/
/** @} */

