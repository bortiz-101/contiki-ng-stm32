/*
 * Clock driver for STM32F4XX using SysTick
 * 
 * Based on cc2538 implementation but adapted for STM32F4XX
 * Uses ARM SysTick for clock ticks at CLOCK_CONF_SECOND rate
 */

#include "contiki.h"
#include "sys/clock.h"
#include "sys/etimer.h"
#include "system_stm32f4xx.h"

#include <stdint.h>

/* Clock ticks counter */
static volatile clock_time_t tick_count = 0;
static volatile unsigned long second_count = 0;

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize the clock subsystem
 * 
 * Configures SysTick to generate interrupts at CLOCK_CONF_SECOND rate
 * Assumes system clock (CPU) is running at a known frequency
 */
void
clock_init(void)
{
  /* Disable SysTick first */
  SYSTICK->CTRL = 0;
  
  /* 
   * Calculate reload value for desired tick rate
   * For STM32F4XX at 168 MHz system clock and CLOCK_CONF_SECOND = 128:
   * Reload = (168,000,000 Hz / 128) - 1 = 1,312,500 - 1
   * 
   * Generic formula: reload = (SYS_CLK_HZ / CLOCK_SECOND) - 1
   * For now, use a conservative estimate assuming ~168MHz
   */
  
  /* Set reload value (24-bit) */
  /* Assuming 168 MHz clock, for 128 Hz: 168000000 / 128 = 1312500 */
  SYSTICK->LOAD = (168000000 / CLOCK_SECOND) - 1;
  
  /* Clear current value */
  SYSTICK->VAL = 0;
  
  /* 
   * Configure SysTick:
   * - Use processor clock (CLKSOURCE = 1)
   * - Enable interrupt on tick (TICKINT = 1)
   * - Enable counter (ENABLE = 1)
   */
  SYSTICK->CTRL = SYSTICK_CTRL_INIT_VALUE;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the current clock time in ticks
 * 
 * Returns the number of clock ticks since clock_init() was called
 */
clock_time_t
clock_time(void)
{
  return tick_count;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the number of seconds elapsed since reset
 * 
 * Returns the number of seconds since clock_init() was called
 */
unsigned long
clock_seconds(void)
{
  return second_count;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief SysTick interrupt handler
 * 
 * Called by the interrupt dispatcher when SysTick timer expires
 * Updates clock ticks and handles per-second callbacks
 */
void
SysTick_Handler(void)
{
  tick_count++;
  
  /* Check if we've completed a full second */
  if(tick_count % CLOCK_SECOND == 0) {
    second_count++;
  }
  
  /* Notify the system that a clock tick occurred */
  if(etimer_pending()) {
    etimer_request_poll();
  }
}

/*---------------------------------------------------------------------------*/
