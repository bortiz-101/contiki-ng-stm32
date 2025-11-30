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
 * The DWT cycle counter increments once per CPU clock cycle and provides
 * nanosecond-level timing precision for benchmark and timing analysis.
 *
 * @{
 *
 * \file
 *        DWT cycle counter header for STM32F4
 */

#ifndef DWT_H_
#define DWT_H_

#include <stdint.h>

/*---------------------------------------------------------------------------*/

/**
 * \brief Initialize the DWT cycle counter.
 *
 * Enables the ARM CoreDebug trace enable and the DWT cycle counter.
 * Must be called once before using other DWT functions.
 *
 * \note Call this early in platform initialization, typically in
 *       platform_init_stage_one().
 */
void dwt_init(void);

/**
 * \brief Reset the DWT cycle counter to zero.
 *
 * Clears the cycle count register. Useful for measuring elapsed time
 * in code sections.
 */
void dwt_reset(void);

/**
 * \brief Read the current DWT cycle counter value.
 *
 * \return The number of CPU cycles since dwt_init() or dwt_reset().
 *
 * The counter is 32-bit and increments at the CPU clock frequency (180 MHz).
 * It will overflow after approximately 12 seconds.
 */
uint32_t dwt_get_cycles(void);

/**
 * \brief Convert DWT cycle count to microseconds.
 *
 * \param cycles The number of CPU cycles
 * \return Equivalent time in microseconds
 *
 * Assumes SystemCoreClock = 180 MHz. Precision: ±1 cycle ≈ ±5.6 ns.
 */
uint32_t dwt_cycles_to_us(uint32_t cycles);

/**
 * \brief Convert DWT cycle count to milliseconds.
 *
 * \param cycles The number of CPU cycles
 * \return Equivalent time in milliseconds
 *
 * Assumes SystemCoreClock = 180 MHz.
 */
uint32_t dwt_cycles_to_ms(uint32_t cycles);

/*---------------------------------------------------------------------------*/

/**
 * \name Timing Measurement Macro
 * @{
 */

/**
 * \brief Measure elapsed time in cycles between two dwt_get_cycles() calls.
 *
 * Example usage:
 * \code
 * uint32_t start_cycles = dwt_get_cycles();
 * // ... code to measure ...
 * uint32_t elapsed_cycles = dwt_get_cycles() - start_cycles;
 * uint32_t elapsed_us = dwt_cycles_to_us(elapsed_cycles);
 * printf("Elapsed time: %lu µs\n", elapsed_us);
 * \endcode
 */

/** @} */

#endif /* DWT_H_ */

/** @} */
/** @} */
