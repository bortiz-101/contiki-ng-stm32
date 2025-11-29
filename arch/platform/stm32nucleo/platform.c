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
 * \addtogroup stm32nucleo
 * @{
 *
 * \file
 * STM32 Nucleo-F446RE platform initialization
 */
#include "contiki.h"
#include "soc.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "STM32 Nucleo Platform"
#define LOG_LEVEL LOG_LEVEL_NONE

/*---------------------------------------------------------------------------*/
/**
 * \brief Early platform initialization (stage one)
 *
 * Called by main() before Contiki-NG OS initialization.
 * Performs critical SoC setup:
 * - Clock tree configuration
 * - NVIC interrupt controller setup
 * - Basic peripheral clocks (GPIO, UART, timers)
 *
 * After this completes, the board should be ready for OS scheduling.
 */
void
platform_init_stage_one(void)
{
  /* Initialize SoC: clock tree, interrupts, basic peripherals */
  soc_init();

  /* Initialize debug output */
  dbg_init();

  /* TODO: Platform-specific LED initialization will go here */
  /* leds_init(); */

  LOG_DBG("STM32 Nucleo platform initialized\n");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Deferred platform initialization (stage two)
 *
 * Called by main() after Contiki-NG OS is running.
 * Performs non-critical setup:
 * - Radio/network stack initialization
 * - Sensor drivers
 * - Other application-specific peripherals
 */
void
platform_init_stage_two(void)
{
  /* TODO: Deferred initialization such as:
   * - netstack_init()
   * - radio initialization
   * - sensor drivers
   */
}

/*---------------------------------------------------------------------------*/
/**
 * \brief CPU idle function
 *
 * Called by the scheduler when there is no active work.
 * Puts the CPU into a low-power sleep state until the next interrupt.
 */
void
platform_idle(void)
{
  /* Wait for interrupt (WFI instruction) */
  __asm volatile("wfi");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Final platform initialization (stage three)
 *
 * Called by main() after network stack initialization.
 * Performs application-specific setup:
 * - Sensor calibration
 * - Application-specific timers
 * - Other deferred setup
 */
void
platform_init_stage_three(void)
{
  /* TODO: Application-specific deferred initialization */
}

/*---------------------------------------------------------------------------*/
/** @} */
