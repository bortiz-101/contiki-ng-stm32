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
 * \addtogroup stm32f4xx-cpu
 * @{
 *
 * \defgroup stm32f4xx-dwt DWT (Data Watchpoint and Trace) Cycle Counter
 *
 * Provides precise timing via the ARM Cortex-M4 Data Watchpoint and Trace (DWT)
 * cycle counter for high-resolution performance measurements.
 *
 * @{
 *
 * \file
 *        DWT cycle counter driver for STM32F4
 */

#include "system_stm32f4xx.h"
#include "stm32f446xx.h"

#include <stdint.h>

/*---------------------------------------------------------------------------*/

/**
 * \brief Initialize the DWT cycle counter.
 *
 * Enables trace and the DWT cycle counter. The counter increments once per
 * CPU clock cycle and can be read via dwt_get_cycles().
 *
 * \note This must be called before using dwt_get_cycles().
 */
void
dwt_init(void)
{
  /* Enable debug features via CoreDebug (required for DWT access) */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  /* Reset the cycle counter to 0 */
  DWT->CYCCNT = 0;

  /* Enable the cycle counter */
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/*---------------------------------------------------------------------------*/

/**
 * \brief Reset the DWT cycle counter to zero.
 *
 * Clears the cycle count register. Useful for measuring time intervals.
 */
void
dwt_reset(void)
{
  DWT->CYCCNT = 0;
}

/*---------------------------------------------------------------------------*/

/**
 * \brief Read the current DWT cycle counter value.
 *
 * \return The number of CPU cycles elapsed since dwt_init() or dwt_reset().
 *
 * \note The counter is 32-bit, so it will overflow after ~12 seconds at 180 MHz.
 *       Use the return value directly or handle overflow in calling code.
 */
uint32_t
dwt_get_cycles(void)
{
  return DWT->CYCCNT;
}

/*---------------------------------------------------------------------------*/

/**
 * \brief Convert DWT cycle count to microseconds.
 *
 * \param cycles The number of CPU cycles
 * \return Equivalent time in microseconds
 *
 * \note Assumes SystemCoreClock is 180 MHz. If the clock frequency changes,
 *       update this calculation accordingly.
 */
uint32_t
dwt_cycles_to_us(uint32_t cycles)
{
  /* SystemCoreClock is in Hz, so cycles / (SystemCoreClock / 1,000,000) */
  /* = cycles * 1,000,000 / SystemCoreClock */
  return (cycles * 1000000U) / SystemCoreClock;
}

/*---------------------------------------------------------------------------*/

/**
 * \brief Convert DWT cycle count to milliseconds.
 *
 * \param cycles The number of CPU cycles
 * \return Equivalent time in milliseconds
 *
 * \note Assumes SystemCoreClock is 180 MHz.
 */
uint32_t
dwt_cycles_to_ms(uint32_t cycles)
{
  /* cycles * 1000 / (SystemCoreClock / 1,000,000) */
  /* = cycles * 1000 * 1,000,000 / SystemCoreClock */
  /* = cycles * 1,000,000,000 / SystemCoreClock */
  return (cycles * 1000U) / (SystemCoreClock / 1000U);
}

/*---------------------------------------------------------------------------*/

/**
 * \brief Measure the duration of a code block using DWT.
 *
 * Example usage:
 * \code
 * uint32_t start = dwt_get_cycles();
 * // ... code to measure ...
 * uint32_t elapsed = dwt_get_cycles() - start;
 * uint32_t elapsed_us = dwt_cycles_to_us(elapsed);
 * \endcode
 */

/** @} */
/** @} */
