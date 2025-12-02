/**
 * @file stm32f4xx_it.c
 * @brief STM32F4xx Cortex-M4 Interrupt Service Routines
 *
 * This file provides the interrupt handlers for the STM32F446RE.
 * Most handlers are common exceptions; peripheral-specific handlers
 * are added as needed when drivers are implemented.
 */

#include "stm32f4xx_hal.h"

/*---------------------------------------------------------------------------*/
/* Cortex-M4 Processor Exceptions */
/*---------------------------------------------------------------------------*/

/**
 * \brief Non-maskable interrupt handler
 * 
 * NMI can be triggered by clock security system or other critical events.
 * Should never return to normal program execution.
 */
void
NMI_Handler(void)
{
  /* Infinite loop - NMI is fatal */
  while (1) {
    ;
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Hard fault exception handler
 * 
 * Called when CPU encounters an unrecoverable error (invalid instruction,
 * memory access violation, etc.). Often indicates a programming error.
 */
void
HardFault_Handler(void)
{
  /* Infinite loop - hard fault is typically fatal */
  while (1) {
    ;
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Memory management fault handler
 * 
 * Called when MPU detects a memory access violation.
 * Only relevant if MPU is enabled.
 */
void
MemManage_Handler(void)
{
  while (1) {
    ;
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Bus fault handler
 * 
 * Called on prefetch abort, memory access fault, precise or imprecise.
 * May indicate I-cache, D-cache, or memory system issues.
 */
void
BusFault_Handler(void)
{
  while (1) {
    ;
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Usage fault handler
 * 
 * Called on undefined instruction, invalid state transition,
 * or error on exception return.
 */
void
UsageFault_Handler(void)
{
  while (1) {
    ;
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief System service call (SVC) handler
 * 
 * Called when SVC instruction is executed.
 * Used by OS for system calls and context switching.
 */
void
SVC_Handler(void)
{
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Debug monitor handler
 * 
 * Called in debug mode for debugging events.
 */
void
DebugMon_Handler(void)
{
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Pending SV exception handler
 * 
 * Called by OS for context switching and other critical OS operations.
 * Should NOT be user-modified; OS controls this.
 */
void
PendSV_Handler(void)
{
}

/*---------------------------------------------------------------------------*/
/**
 * \brief SysTick exception handler
 * 
 * SysTick_Handler is implemented in clock.c for Contiki-NG clock management.
 * It is NOT defined here to avoid multiple definitions.
 */

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* STM32F446RE Specific Interrupts */
/*---------------------------------------------------------------------------*/

/**
 * \brief UART/USART interrupt handlers (to be added as needed)
 * 
 * These are stubs that can be filled in when UART drivers are added:
 *   void USART1_IRQHandler(void) { HAL_UART_IRQHandler(&huart1); }
 *   void USART2_IRQHandler(void) { HAL_UART_IRQHandler(&huart2); }
 *   etc.
 */

/**
 * \brief Timer interrupt handlers (to be added as needed)
 * 
 * Stubs for timer interrupts when timer drivers are added:
 *   void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(&htim2); }
 *   etc.
 */

/*---------------------------------------------------------------------------*/

/**
 * \brief Assert parameter failed handler
 * 
 * Called by assert_param macro in hal_conf.h when a HAL function
 * receives invalid parameters.
 */
void
assert_failed(uint8_t* file, uint32_t line)
{
  /* Infinite loop - parameter validation failed */
  (void)file;
  (void)line;
  while (1) {
    ;
  }
}
