/*
 * Real-time timer architecture for STM32F4XX
 *
 * Uses TIM2 (32-bit general purpose timer) for rtimer functionality.
 * TIM2 is independent of the SysTick clock used for the main Contiki-NG clock.
 */

#include "contiki.h"
#include "sys/rtimer.h"
#include "rtimer-arch.h"
#include "system_stm32f4xx.h"

#include <stdint.h>

/*---------------------------------------------------------------------------*/
/* rtimer prescaler configuration
 * TIM2 runs at APB1 clock (45 MHz on STM32F446RE)
 * We want rtimer_clock_t ticks to match RTIMER_ARCH_SECOND frequency
 * RTIMER_ARCH_SECOND = 32768 (Hz), from the header
 * 
 * Prescaler = (APB1_CLOCK / RTIMER_ARCH_SECOND) - 1
 * Prescaler = (45,000,000 / 32,768) - 1 ≈ 1372
 * 
 * This gives us one TIM2 tick per rtimer tick
 */
#define RTIMER_PRESCALER  1372

/*---------------------------------------------------------------------------*/
/* Next rtimer trigger time */
static volatile rtimer_clock_t next_trigger = 0;

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize the rtimer hardware (TIM2)
 *
 * Configures TIM2 as a free-running counter at RTIMER_ARCH_SECOND frequency.
 * The rtimer interrupt is only enabled when rtimer_arch_schedule() is called.
 */
void
rtimer_arch_init(void)
{
  /* Enable TIM2 clock via RCC APB1ENR */
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

  /* Disable timer during configuration */
  TIM2->CR1 = 0;

  /* Clear all pending interrupt flags */
  TIM2->SR = 0;

  /* Set prescaler for desired frequency
   * PSC = (peripheral_clock / desired_frequency) - 1
   * At 45 MHz APB1 and 32768 Hz desired: PSC = 1372
   */
  TIM2->PSC = RTIMER_PRESCALER;

  /* Set auto-reload register to maximum (free-running counter) */
  TIM2->ARR = 0xFFFFFFFFUL;

  /* Generate update event to load prescaler */
  TIM2->EGR |= (1U << 0);  /* UG bit */

  /* Configure for output compare on Channel 1 (CC1)
   * Mode: Output Compare (not PWM)
   * Direction: Down counter disabled (up counter)
   */
  TIM2->CCMR1 = 0;  /* Output compare mode */
  TIM2->CCER = 0;   /* No output on CC pins */

  /* Enable the counter */
  TIM2->CR1 |= TIM_CR1_CEN;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Schedule an rtimer task at absolute time t
 *
 * \param t The absolute time (in rtimer ticks) when the interrupt should fire
 *
 * This function sets up TIM2 Compare Register 1 (CCR1) to generate an
 * interrupt when the counter reaches the specified value.
 */
void
rtimer_arch_schedule(rtimer_clock_t t)
{
  rtimer_clock_t now;

  now = rtimer_arch_now();

  /* Guard time: minimum delay from now
   * Ensure the timer value is in the future
   * RTIMER_GUARD_TIME is typically a small value (a few ticks)
   */
  if(!RTIMER_CLOCK_LT(now, t - RTIMER_GUARD_TIME)) {
    t = now + RTIMER_GUARD_TIME;
  }

  /* Store the scheduled time for rtimer query */
  next_trigger = t;

  /* Set the Compare Match Register 1 with the target time */
  TIM2->CCR1 = t;

  /* Clear any pending CC1 interrupt flag */
  TIM2->SR &= ~TIM_SR_CC1IF;

  /* Enable Compare 1 interrupt */
  TIM2->DIER |= TIM_DIER_CC1IE;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Return the next scheduled rtimer trigger time
 *
 * \return The absolute time of the next scheduled event
 *
 * This is typically used by the power management system to determine
 * when the device should wake up.
 */
rtimer_clock_t
rtimer_arch_next_trigger()
{
  return next_trigger;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the current rtimer clock value
 *
 * \return The current counter value in rtimer ticks
 *
 * Reads the free-running TIM2 counter directly. This provides the
 * high-resolution time base for the rtimer subsystem.
 */
rtimer_clock_t
rtimer_arch_now()
{
  return TIM2->CNT;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief TIM2 interrupt handler
 *
 * Called when the Compare Match 1 interrupt fires. Executes the scheduled
 * rtimer task and disables further interrupts until the next task
 * is scheduled.
 */
void
TIM2_IRQHandler(void)
{
  /* Check if this was a Compare 1 interrupt */
  if(TIM2->SR & TIM_SR_CC1IF) {
    /* Clear the interrupt flag */
    TIM2->SR &= ~TIM_SR_CC1IF;

    /* Disable Compare 1 interrupt (will be re-enabled on next schedule) */
    TIM2->DIER &= ~TIM_DIER_CC1IE;

    /* Clear the next trigger time */
    next_trigger = 0;

    /* Execute the scheduled rtimer task */
    rtimer_run_next();
  }
}

/*---------------------------------------------------------------------------*/
