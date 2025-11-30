/*
 * Copyright (c) 2025, Contiki-NG STM32F4 Timing Experiments
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
 * \defgroup isr-noise 1 kHz ISR noise generator
 *
 * Programmable interrupt source for timing experiments. Generates
 * a 1 kHz timer interrupt with tunable loop duration to emulate
 * ISR load (0% to 5% and beyond).
 *
 * Uses TIM3 (not TIM2, which is reserved for rtimer).
 * Interrupt: TIM3_IRQn
 *
 * @{
 *
 * \file
 *        ISR noise generator header for timing experiments
 */

#ifndef ISR_NOISE_H_
#define ISR_NOISE_H_

#include <stdint.h>

/*---------------------------------------------------------------------------*/

/**
 * \brief Initialize 1 kHz timer interrupt on TIM3.
 *
 * Configures TIM3 to generate an interrupt every 1.000 ms.
 * Loop iterations set to 0 (empty ISR, minimal overhead).
 *
 * Requires system clock and TIM3 clock to be running.
 *
 * \note Enables global interrupts via __enable_irq() after setup.
 */
void isr_noise_init(void);

/**
 * \brief Set the loop iteration count for ISR work simulation.
 *
 * \param iterations Number of loop iterations per ISR.
 *                   0 = minimal work (~10 cycles)
 *                   180 = ~1 µs of work (at 180 MHz)
 *                   9000 = ~50 µs of work (at 180 MHz)
 *                   18000 = ~100 µs of work (at 180 MHz)
 *
 * Call this after isr_noise_init() to tune ISR load.
 *
 * \note Can be called at runtime to change load dynamically.
 */
void isr_noise_set_iterations(uint32_t iterations);

/**
 * \brief Get the current loop iteration count.
 *
 * \return Current iterations setting.
 */
uint32_t isr_noise_get_iterations(void);

/**
 * \brief Start the 1 kHz interrupt.
 *
 * Enables TIM3 counter. Interrupt fires every 1 ms.
 *
 * \note isr_noise_init() must be called first.
 */
void isr_noise_start(void);

/**
 * \brief Stop the 1 kHz interrupt.
 *
 * Disables TIM3 counter. No more interrupts.
 */
void isr_noise_stop(void);

/**
 * \brief Check if ISR noise generator is running.
 *
 * \return 1 if running, 0 if stopped.
 */
int isr_noise_is_running(void);

/*---------------------------------------------------------------------------*/

/** \brief Configuration: TIM3 frequency (1 kHz) */
#define ISR_NOISE_FREQ_HZ 1000

/** @} */

#endif /* ISR_NOISE_H_ */
