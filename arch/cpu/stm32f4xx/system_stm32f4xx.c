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
 * \file
 * STM32F4xx System Initialization
 *
 * ARM CMSIS SystemInit implementation for STM32F4xx family.
 * Configures the system clock tree (HSE → PLL → SYSCLK) and bus prescalers.
 *
 * Called early from startup assembly (startup_stm32f446xx.s) before main().
 * Peripheral-specific clocks are enabled by individual drivers.
 */
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include <stdint.h>

/* System core clock variable required by ARM CMSIS */
uint32_t SystemCoreClock = HSE_VALUE;

/* AHB prescaler lookup table (output of 2^n for each entry) */
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/* APB prescaler lookup table (output of 2^n for each entry) */
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize the system clock to 180 MHz via PLL
 *
 * Configures:
 * - HSE (8 MHz external oscillator on STM32 Nucleo board)
 * - PLL parameters: PLLM=2, PLLN=180, PLLP=2 → 180 MHz
 * - Bus prescalers: AHB=1, APB1=4, APB2=2 → 180/45/90 MHz
 * - Updates SystemCoreClock variable
 *
 * This is called from startup assembly before any C runtime initialization.
 * Peripheral clocks (GPIO, UART, timers) are enabled by individual drivers via soc_init().
 */
void
SystemInit(void)
{
  /* TODO: Implement clock tree configuration
   * 
   * Step 1: Enable HSE oscillator
   *   - Set RCC->CR |= RCC_CR_HSEON
   *   - Wait for RCC->CR & RCC_CR_HSERDY
   * 
   * Step 2: Configure PLL
   *   - Set RCC->PLLCFGR with PLLM, PLLN, PLLP values
   *   - Enable PLL: RCC->CR |= RCC_CR_PLLON
   *   - Wait for RCC->CR & RCC_CR_PLLRDY
   * 
   * Step 3: Set system clock source to PLL
   *   - RCC->CFGR |= RCC_CFGR_SW_PLL
   *   - Wait for (RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL
   * 
   * Step 4: Configure bus prescalers
   *   - RCC->CFGR |= (AHB_PRESCALER | APB1_PRESCALER | APB2_PRESCALER)
   * 
   * Step 5: Update SystemCoreClock variable
   *   - SystemCoreClock = 180000000UL;
   */

  /* Placeholder: system clock remains at HSE for now */
  SystemCoreClock = HSE_VALUE;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Update SystemCoreClock variable after clock source or prescaler change
 *
 * Called by application if dynamic clock reconfiguration occurs.
 * Reads current clock configuration from RCC registers and updates SystemCoreClock.
 */
void
SystemCoreClockUpdate(void)
{
  /* TODO: Implement dynamic clock update
   * Read RCC->CFGR to determine current clock source and prescalers,
   * then recalculate SystemCoreClock accordingly.
   */
  SystemCoreClock = HSE_VALUE;
}
