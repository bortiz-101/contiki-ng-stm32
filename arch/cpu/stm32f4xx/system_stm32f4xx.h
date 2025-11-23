#pragma once
#include <stdint.h>

// Sets up the FPU, vector relocation, and other system functions
void SystemInit(void);
// Re-reads RCC and updates SystemCoreClock variable
void SystemCoreClockUpdate(void);
// Global variable holding the current HCLK frequency (in Hz)
extern uint32_t SystemCoreClock;

// Define the HSE and HSI values

#ifndef HSE_VALUE
#define HSE_VALUE    ((uint32_t)8000000U) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#ifndef HSI_VALUE
#define HSI_VALUE    ((uint32_t)16000000U) /*!< Value of the Internal oscillator in Hz */
#endif /* HSI_VALUE */ 