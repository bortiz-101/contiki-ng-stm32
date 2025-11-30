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
 * \addtogroup isr-noise
 * @{
 *
 * \file
 *        ISR noise generator implementation for timing experiments
 */

#include "isr_noise.h"
#include "system_stm32f4xx.h"

/*---------------------------------------------------------------------------*/

/** Current loop iteration count for ISR work */
static volatile uint32_t isr_noise_loop_iterations = 0;

/** Whether ISR noise generator is running */
static volatile int isr_noise_running = 0;

/*---------------------------------------------------------------------------*/

/**
 * \brief TIM3 Update Interrupt Handler (1 kHz).
 *
 * Executes the noise loop for tunable duration, then clears interrupt flag.
 */
void
TIM3_IRQHandler(void)
{
  uint32_t i;

  /* Clear the Update Interrupt Flag */
  TIM3->SR &= ~TIM_SR_UIF;

  /* Execute noise loop for ISR load simulation */
  for (i = 0; i < isr_noise_loop_iterations; i++) {
    /* Empty loop: just burn cycles */
    __asm volatile("nop");
  }
}

/*---------------------------------------------------------------------------*/

void
isr_noise_init(void)
{
  /* Enable TIM3 clock (APB1) */
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

  /* Configure TIM3 for 1 kHz interrupt
   *
   * APB1 Clock: 45 MHz (from PLL, divided by 4)
   * Desired frequency: 1 kHz (1 ms period)
   * Formula: freq = APB1_CLOCK / ((PSC+1) * (ARR+1))
   *
   * Target: 1000 Hz = 45,000,000 / ((PSC+1) * (ARR+1))
   * Let PSC = 44 (45 MHz / 45 = 1 MHz)
   * Then: 1000 = 1,000,000 / (ARR+1)
   * So: ARR = 999 (generates 1 ms period)
   */

  /* Set prescaler: 44 (gives 1 MHz after division) */
  TIM3->PSC = 44;

  /* Set auto-reload: 999 (1 MHz / 1000 = 1 kHz) */
  TIM3->ARR = 999;

  /* Update registers with new values */
  TIM3->EGR |= (1U << 0);  /* Generate update event to reload PSC/ARR */

  /* Clear counter */
  TIM3->CNT = 0;

  /* Enable Update Interrupt (UIE) */
  TIM3->DIER |= TIM_DIER_UIE;

  /* Enable TIM3 interrupt in NVIC (IRQ 29) */
  __asm volatile("cpsid i");  /* Disable all interrupts temporarily */

  /* Set TIM3_IRQn priority and enable */
  *(uint32_t *)(0xE000E400 + 4 * 29 / 4) = 0;  /* NVIC_IPR7, TIM3 priority */
  *(uint32_t *)(0xE000E100 + 4 * (29 / 32)) |= (1U << (29 % 32));  /* NVIC_ISER0 */

  __asm volatile("cpsie i");  /* Re-enable interrupts */

  isr_noise_loop_iterations = 0;
  isr_noise_running = 0;
}

/*---------------------------------------------------------------------------*/

void
isr_noise_set_iterations(uint32_t iterations)
{
  isr_noise_loop_iterations = iterations;
}

/*---------------------------------------------------------------------------*/

uint32_t
isr_noise_get_iterations(void)
{
  return isr_noise_loop_iterations;
}

/*---------------------------------------------------------------------------*/

void
isr_noise_start(void)
{
  /* Enable TIM3 counter */
  TIM3->CR1 |= TIM_CR1_CEN;
  isr_noise_running = 1;
}

/*---------------------------------------------------------------------------*/

void
isr_noise_stop(void)
{
  /* Disable TIM3 counter */
  TIM3->CR1 &= ~TIM_CR1_CEN;
  isr_noise_running = 0;
}

/*---------------------------------------------------------------------------*/

int
isr_noise_is_running(void)
{
  return isr_noise_running;
}

/*---------------------------------------------------------------------------*/

/**
 * \brief Measure a single ISR loop execution time.
 *
 * Runs the ISR loop once and measures cycle count via DWT.
 * This is a helper for the public isr_noise_measure_loop_time().
 */
static uint32_t
isr_noise_measure_loop_cycles(uint32_t iterations)
{
  extern uint32_t dwt_get_cycles(void);
  uint32_t cycles_start, cycles_end, cycles_elapsed;
  uint32_t i;

  /* Record cycle count before loop */
  cycles_start = dwt_get_cycles();

  /* Execute the noise loop */
  for (i = 0; i < iterations; i++) {
    __asm volatile("nop");
  }

  /* Record cycle count after loop */
  cycles_end = dwt_get_cycles();

  /* Calculate elapsed cycles (handle wraparound) */
  if (cycles_end >= cycles_start) {
    cycles_elapsed = cycles_end - cycles_start;
  } else {
    /* 32-bit counter wrapped around */
    cycles_elapsed = (0xFFFFFFFFU - cycles_start) + cycles_end;
  }

  return cycles_elapsed;
}

/*---------------------------------------------------------------------------*/

uint32_t
isr_noise_measure_loop_time(uint32_t iterations)
{
  extern uint32_t dwt_cycles_to_us(uint32_t cycles);
  uint32_t cycles;

  /* Measure the loop */
  cycles = isr_noise_measure_loop_cycles(iterations);

  /* Convert cycles to microseconds */
  return dwt_cycles_to_us(cycles);
}

/*---------------------------------------------------------------------------*/

uint32_t
isr_noise_calibrate_for_load(float target_isr_percent)
{
  uint32_t low = 0;
  uint32_t high = 1000000;  /* Upper bound: ~5.5 ms loop */
  uint32_t mid;
  uint32_t loop_time_us;
  float measured_isr_percent;
  float error;
  float best_error = 100.0f;
  uint32_t best_iterations = 0;
  int iterations = 0;

  /* Binary search for iteration count that matches target ISR% */
  while (low <= high && iterations < 30) {
    mid = (low + high) / 2;

    /* Measure loop time for this iteration count */
    loop_time_us = isr_noise_measure_loop_time(mid);

    /* Calculate ISR% from measured time */
    /* ISR% = (loop_time_µs / 1000 µs) * 100 */
    measured_isr_percent = (loop_time_us / 1000.0f) * 100.0f;

    /* Calculate error from target */
    error = measured_isr_percent - target_isr_percent;
    if (error < 0) error = -error;  /* Absolute value */

    /* Track best match */
    if (error < best_error) {
      best_error = error;
      best_iterations = mid;
    }

    /* Adjust search bounds */
    if (measured_isr_percent < target_isr_percent) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }

    iterations++;
  }

  return best_iterations;
}

/*---------------------------------------------------------------------------*/

/** @} */
