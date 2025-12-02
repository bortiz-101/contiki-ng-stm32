/**
 * \defgroup rtimer_arch STM32F4 Real-time Timer Architecture
 * @{
 */

/**
 * \file
 * STM32F4 real-time timer architecture definitions
 *
 * The STM32F446RE has multiple timers. The rtimer-arch implementation
 * should use a dedicated hardware timer (not SysTick, which is used for
 * the main Contiki-NG clock). Typical choices:
 * - TIM2 (32-bit, general purpose)
 * - TIM5 (32-bit, general purpose)
 *
 * This file provides architecture-specific definitions for the rtimer
 * subsystem. The actual implementation (rtimer-arch.c) should provide:
 * - rtimer_arch_init(): Initialize the hardware timer
 * - rtimer_arch_schedule(): Schedule a callback at a future time
 */

#ifndef RTIMER_ARCH_H_
#define RTIMER_ARCH_H_

#include "contiki.h"
#include "sys/rtimer.h"
#include <stdint.h>

/**
 * \brief Real-time timer clock size (in bytes)
 * 
 * STM32F4 TIM2 is a 32-bit counter, so we use 32-bit rtimer ticks
 */
#define RTIMER_CONF_CLOCK_SIZE 4

/**
 * \brief Get the current rtimer clock value
 * 
 * Defined in rtimer-arch.c - reads the free-running TIM2 counter
 * RTIMER_ARCH_SECOND is defined in stm32f4xx-def.h (1000000 Hz for microsecond resolution)
 */
rtimer_clock_t rtimer_arch_now(void);

/**
 * \brief Return the next scheduled rtimer trigger time
 * 
 * Used by power management to determine wake-up time
 */
rtimer_clock_t rtimer_arch_next_trigger(void);

#endif /* RTIMER_ARCH_H_ */

/** @} */
