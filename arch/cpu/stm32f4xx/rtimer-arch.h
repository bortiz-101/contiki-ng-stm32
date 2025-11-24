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

#include <stdint.h>

/**
 * \brief Real-time timer tick frequency
 * 
 * This should match the actual hardware timer frequency used for rtimer.
 * Currently set to 1000 Hz (1ms resolution) as a placeholder.
 * This will be updated when rtimer-arch.c is implemented.
 */
#define RTIMER_ARCH_SECOND 1000

/* Architecture-specific rtimer type - can be overridden for custom implementations */
#ifndef RTIMER_ARCH_SECOND
#define RTIMER_ARCH_SECOND 1000
#endif

#endif /* RTIMER_ARCH_H_ */

/** @} */
