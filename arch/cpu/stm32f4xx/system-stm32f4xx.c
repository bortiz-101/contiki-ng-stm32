/**
 * @file system-stm32f4xx-stub.c
 * @brief System initialization stub for STM32F4
 *
 * Provides minimal SystemInit and SystemCoreClock for basic operation.
 * This can be replaced with a full HAL or custom implementation later.
 */

#include <stdint.h>

/* System core clock frequency - 180 MHz for STM32F446RE */
uint32_t SystemCoreClock = 180000000UL;

/**
 * @brief AHB prescaler values table for clock division
 * Used by HAL_RCC functions to convert prescaler enum to actual divisor values
 */
const uint8_t AHBPrescTable[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,  /* Division factors 1-8 (prescaler 0-7) */
  1, 2, 3, 4, 6, 7, 8, 9   /* Division factors 2-512 (prescaler 8-15) */
};

/**
 * @brief APB prescaler values table for clock division
 * Used by HAL_RCC functions to convert prescaler enum to actual divisor values
 */
const uint8_t APBPrescTable[8] = {
  0, 0, 0, 0,           /* Division factors 1-8 (prescaler 0-3) */
  1, 2, 3, 4            /* Division factors 2-16 (prescaler 4-7) */
};

/**
 * @brief System initialization function
 * 
 * Called from reset handler before main().
 * Minimal stub that just ensures SystemCoreClock is set.
 */
void
SystemInit(void)
{
  /* Stub: minimal initialization */
  /* In a full implementation, this would:
   * - Enable FPU if needed
   * - Configure cache/prefetch
   * - Set up clocks
   * - Configure flash wait states
   */
}

/**
 * @brief Update SystemCoreClock variable
 * 
 * Called after clock configuration changes to recalculate the
 * system core clock frequency.
 */
void
SystemCoreClockUpdate(void)
{
  /* Stub: assumes fixed 180 MHz */
  SystemCoreClock = 180000000UL;
}
