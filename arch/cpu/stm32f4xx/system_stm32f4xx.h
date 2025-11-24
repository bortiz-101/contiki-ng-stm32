#pragma once
#include <stdint.h>

/*---------------------------------------------------------------------------*/
/** \name RCC (Reset and Clock Control) Register Structure
 * @{
 */

/** \brief RCC register offsets and layout */
typedef struct {
  uint32_t CR;         /**< Control Register (offset 0x00) */
  uint32_t PLLCFGR;    /**< PLL Configuration Register (offset 0x04) */
  uint32_t CFGR;       /**< Configuration Register (offset 0x08) */
} rcc_registers_t;

/** \brief RCC peripheral pointer at fixed memory address */
#define RCC ((rcc_registers_t *)0x40023800UL)

/** @} */
/*---------------------------------------------------------------------------*/
/** \name RCC CR Register Bit Definitions
 * @{
 */

#define RCC_CR_HSEON    (1U << 16)   /**< HSE oscillator enable */
#define RCC_CR_HSERDY   (1U << 17)   /**< HSE oscillator ready flag */
#define RCC_CR_PLLON    (1U << 24)   /**< PLL enable */
#define RCC_CR_PLLRDY   (1U << 25)   /**< PLL ready flag */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name RCC PLLCFGR Register Bit Definitions
 * @{
 */

#define RCC_PLLCFGR_PLLM_MASK   0x3FU         /**< PLLM field mask (bits 5:0) */
#define RCC_PLLCFGR_PLLM(n)     ((n) & 0x3FU) /**< PLLM field value */

#define RCC_PLLCFGR_PLLN_MASK   (0x1FFU << 6)  /**< PLLN field mask (bits 14:6) */
#define RCC_PLLCFGR_PLLN(n)     (((n) & 0x1FFU) << 6) /**< PLLN field value */

#define RCC_PLLCFGR_PLLP_MASK   (0x3U << 16)   /**< PLLP field mask (bits 17:16) */
#define RCC_PLLCFGR_PLLP_2      (0x0U << 16)   /**< PLLP = 2 */
#define RCC_PLLCFGR_PLLP_4      (0x1U << 16)   /**< PLLP = 4 */
#define RCC_PLLCFGR_PLLP_6      (0x2U << 16)   /**< PLLP = 6 */
#define RCC_PLLCFGR_PLLP_8      (0x3U << 16)   /**< PLLP = 8 */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name RCC CFGR Register Bit Definitions
 * @{
 */

#define RCC_CFGR_SW_MASK        0x3U           /**< SW field mask (bits 1:0) */
#define RCC_CFGR_SW_HSI         0x0U           /**< HSI as system clock */
#define RCC_CFGR_SW_HSE         0x1U           /**< HSE as system clock */
#define RCC_CFGR_SW_PLL         0x2U           /**< PLL as system clock */
#define RCC_CFGR_SW_PLLR        0x3U           /**< PLL_R as system clock */

#define RCC_CFGR_SWS_MASK       (0x3U << 2)    /**< SWS field mask (bits 3:2) */
#define RCC_CFGR_SWS_HSI        (0x0U << 2)    /**< HSI used as system clock */
#define RCC_CFGR_SWS_HSE        (0x1U << 2)    /**< HSE used as system clock */
#define RCC_CFGR_SWS_PLL        (0x2U << 2)    /**< PLL used as system clock */
#define RCC_CFGR_SWS_PLLR       (0x3U << 2)    /**< PLL_R used as system clock */

#define RCC_CFGR_HPRE_MASK      (0xFU << 4)    /**< HPRE field mask (bits 7:4) */
#define RCC_CFGR_HPRE_DIV1      (0x0U << 4)    /**< AHB clock not divided */
#define RCC_CFGR_HPRE_DIV2      (0x8U << 4)    /**< AHB clock divided by 2 */
#define RCC_CFGR_HPRE_DIV4      (0x9U << 4)    /**< AHB clock divided by 4 */
#define RCC_CFGR_HPRE_DIV8      (0xAU << 4)    /**< AHB clock divided by 8 */
#define RCC_CFGR_HPRE_DIV16     (0xBU << 4)    /**< AHB clock divided by 16 */
#define RCC_CFGR_HPRE_DIV64     (0xCU << 4)    /**< AHB clock divided by 64 */
#define RCC_CFGR_HPRE_DIV128    (0xDU << 4)    /**< AHB clock divided by 128 */
#define RCC_CFGR_HPRE_DIV256    (0xEU << 4)    /**< AHB clock divided by 256 */
#define RCC_CFGR_HPRE_DIV512    (0xFU << 4)    /**< AHB clock divided by 512 */

#define RCC_CFGR_PPRE1_MASK     (0x7U << 10)   /**< PPRE1 field mask (bits 12:10) */
#define RCC_CFGR_PPRE1_DIV1     (0x0U << 10)   /**< APB1 clock not divided */
#define RCC_CFGR_PPRE1_DIV2     (0x4U << 10)   /**< APB1 clock divided by 2 */
#define RCC_CFGR_PPRE1_DIV4     (0x5U << 10)   /**< APB1 clock divided by 4 */
#define RCC_CFGR_PPRE1_DIV8     (0x6U << 10)   /**< APB1 clock divided by 8 */
#define RCC_CFGR_PPRE1_DIV16    (0x7U << 10)   /**< APB1 clock divided by 16 */

#define RCC_CFGR_PPRE2_MASK     (0x7U << 13)   /**< PPRE2 field mask (bits 15:13) */
#define RCC_CFGR_PPRE2_DIV1     (0x0U << 13)   /**< APB2 clock not divided */
#define RCC_CFGR_PPRE2_DIV2     (0x4U << 13)   /**< APB2 clock divided by 2 */
#define RCC_CFGR_PPRE2_DIV4     (0x5U << 13)   /**< APB2 clock divided by 4 */
#define RCC_CFGR_PPRE2_DIV8     (0x6U << 13)   /**< APB2 clock divided by 8 */
#define RCC_CFGR_PPRE2_DIV16    (0x7U << 13)   /**< APB2 clock divided by 16 */

/** @} */
/*---------------------------------------------------------------------------*/

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