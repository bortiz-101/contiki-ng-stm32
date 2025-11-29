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
  uint32_t CIR;        /**< Clock Interrupt Register (offset 0x0C) */
  uint32_t AHB1RSTR;   /**< AHB1 Peripheral Reset Register (offset 0x10) */
  uint32_t AHB2RSTR;   /**< AHB2 Peripheral Reset Register (offset 0x14) */
  uint32_t AHB3RSTR;   /**< AHB3 Peripheral Reset Register (offset 0x18) */
  uint32_t RESERVED0;  /**< Reserved (offset 0x1C) */
  uint32_t APB1RSTR;   /**< APB1 Peripheral Reset Register (offset 0x20) */
  uint32_t APB2RSTR;   /**< APB2 Peripheral Reset Register (offset 0x24) */
  uint32_t RESERVED1[2]; /**< Reserved (offset 0x28-0x2C) */
  uint32_t AHB1ENR;    /**< AHB1 Peripheral Clock Enable Register (offset 0x30) */
  uint32_t AHB2ENR;    /**< AHB2 Peripheral Clock Enable Register (offset 0x34) */
  uint32_t AHB3ENR;    /**< AHB3 Peripheral Clock Enable Register (offset 0x38) */
  uint32_t RESERVED2;  /**< Reserved (offset 0x3C) */
  uint32_t APB1ENR;    /**< APB1 Peripheral Clock Enable Register (offset 0x40) */
  uint32_t APB2ENR;    /**< APB2 Peripheral Clock Enable Register (offset 0x44) */
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
/** \name SysTick (System Tick Timer) Register Structure
 * @{
 */

/** \brief SysTick register layout (ARM Cortex-M4) */
typedef struct {
  uint32_t CTRL;       /**< Control and Status Register (offset 0x00) */
  uint32_t LOAD;       /**< Reload Value Register (offset 0x04) */
  uint32_t VAL;        /**< Current Value Register (offset 0x08) */
  uint32_t CALIB;      /**< Calibration Value Register (offset 0x0C) */
} systick_registers_t;

/** \brief SysTick peripheral pointer at fixed memory address */
#define SYSTICK ((systick_registers_t *)0xE000E010UL)

/** @} */
/*---------------------------------------------------------------------------*/
/** \name SysTick CTRL (Control and Status) Register Bit Definitions
 * @{
 */

#define SYSTICK_CTRL_ENABLE     (1U << 0)   /**< Counter enable (ENABLE) */
#define SYSTICK_CTRL_TICKINT    (1U << 1)   /**< SysTick exception request enable (TICKINT) */
#define SYSTICK_CTRL_CLKSOURCE  (1U << 2)   /**< Clock source selection (CLKSOURCE) */
#define SYSTICK_CTRL_COUNTFLAG  (1U << 16)  /**< Count flag (COUNTFLAG, read-only) */

/** Convenience macro: SysTick configuration for 128 Hz with interrupts */
#define SYSTICK_CTRL_INIT_VALUE (SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT | SYSTICK_CTRL_CLKSOURCE)

/** @} */
/*---------------------------------------------------------------------------*/
/** \name GPIO (General Purpose I/O) Register Structure
 * @{
 */

/** \brief GPIO register layout */
typedef struct {
  uint32_t MODER;      /**< GPIO port mode register (offset 0x00) */
  uint32_t OTYPER;     /**< GPIO port output type register (offset 0x04) */
  uint32_t OSPEEDR;    /**< GPIO port output speed register (offset 0x08) */
  uint32_t PUPDR;      /**< GPIO port pull-up/pull-down register (offset 0x0C) */
  uint32_t IDR;        /**< GPIO port input data register (offset 0x10) */
  uint32_t ODR;        /**< GPIO port output data register (offset 0x14) */
  uint32_t BSRR;       /**< GPIO port bit set/reset register (offset 0x18) */
  uint32_t LCKR;       /**< GPIO port configuration lock register (offset 0x1C) */
  uint32_t AFRL;       /**< GPIO alternate function low register (offset 0x20) */
  uint32_t AFRH;       /**< GPIO alternate function high register (offset 0x24) */
} gpio_registers_t;

/** \brief GPIO peripheral pointers at fixed memory addresses */
#define GPIOA ((gpio_registers_t *)0x40020000UL)
#define GPIOB ((gpio_registers_t *)0x40020400UL)
#define GPIOC ((gpio_registers_t *)0x40020800UL)
#define GPIOD ((gpio_registers_t *)0x40020C00UL)
#define GPIOE ((gpio_registers_t *)0x40021000UL)
#define GPIOF ((gpio_registers_t *)0x40021400UL)
#define GPIOG ((gpio_registers_t *)0x40021800UL)
#define GPIOH ((gpio_registers_t *)0x40021C00UL)

/** @} */
/*---------------------------------------------------------------------------*/
/** \name USART (Universal Synchronous/Asynchronous Receiver-Transmitter) Register Structure
 * @{
 */

/** \brief USART register layout */
typedef struct {
  uint32_t SR;         /**< Status register (offset 0x00) */
  uint32_t DR;         /**< Data register (offset 0x04) */
  uint32_t BRR;        /**< Baud rate register (offset 0x08) */
  uint32_t CR1;        /**< Control register 1 (offset 0x0C) */
  uint32_t CR2;        /**< Control register 2 (offset 0x10) */
  uint32_t CR3;        /**< Control register 3 (offset 0x14) */
  uint32_t GTPR;       /**< Guard time and prescaler register (offset 0x18) */
} usart_registers_t;

/** \brief USART peripheral pointers at fixed memory addresses */
#define USART1 ((usart_registers_t *)0x40011000UL)
#define USART2 ((usart_registers_t *)0x40004400UL)
#define USART3 ((usart_registers_t *)0x40004800UL)
#define UART4  ((usart_registers_t *)0x40004C00UL)
#define UART5  ((usart_registers_t *)0x40005000UL)
#define USART6 ((usart_registers_t *)0x40011400UL)

/** @} */
/*---------------------------------------------------------------------------*/
/** \name USART SR (Status Register) Bit Definitions
 * @{
 */

#define USART_SR_PE      (1U << 0)   /**< Parity error */
#define USART_SR_FE      (1U << 1)   /**< Framing error */
#define USART_SR_NE      (1U << 2)   /**< Noise error */
#define USART_SR_ORE     (1U << 3)   /**< Overrun error */
#define USART_SR_IDLE    (1U << 4)   /**< IDLE line detected */
#define USART_SR_RXNE    (1U << 5)   /**< Read data register not empty */
#define USART_SR_TC      (1U << 6)   /**< Transmission complete */
#define USART_SR_TXE     (1U << 7)   /**< Transmit data register empty */
#define USART_SR_LBD     (1U << 8)   /**< LIN break detection flag */
#define USART_SR_CTS     (1U << 9)   /**< CTS flag */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name USART CR1 (Control Register 1) Bit Definitions
 * @{
 */

#define USART_CR1_SBK    (1U << 0)   /**< Send break */
#define USART_CR1_RWU    (1U << 1)   /**< Receiver wakeup */
#define USART_CR1_RE     (1U << 2)   /**< Receiver enable */
#define USART_CR1_TE     (1U << 3)   /**< Transmitter enable */
#define USART_CR1_IDLEIE (1U << 4)   /**< IDLE interrupt enable */
#define USART_CR1_RXNEIE (1U << 5)   /**< RXNE interrupt enable */
#define USART_CR1_TCIE   (1U << 6)   /**< Transmission complete interrupt enable */
#define USART_CR1_TXEIE  (1U << 7)   /**< TXE interrupt enable */
#define USART_CR1_PEIE   (1U << 8)   /**< Parity error interrupt enable */
#define USART_CR1_PS     (1U << 9)   /**< Parity selection */
#define USART_CR1_PCE    (1U << 10)  /**< Parity control enable */
#define USART_CR1_WAKE   (1U << 11)  /**< Wakeup method */
#define USART_CR1_M      (1U << 12)  /**< Word length */
#define USART_CR1_UE     (1U << 13)  /**< USART enable */
#define USART_CR1_OVER8  (1U << 15)  /**< Oversampling mode */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name RCC Clock Enable Bits
 * @{
 */

/** \brief RCC_AHB1ENR - AHB1 Peripheral Clock Enable Register Bits */
#define RCC_AHB1ENR_GPIOAEN  (1U << 0)   /**< GPIOA clock enable */
#define RCC_AHB1ENR_GPIOBEN  (1U << 1)   /**< GPIOB clock enable */
#define RCC_AHB1ENR_GPIOCEN  (1U << 2)   /**< GPIOC clock enable */
#define RCC_AHB1ENR_GPIODEN  (1U << 3)   /**< GPIOD clock enable */
#define RCC_AHB1ENR_GPIOEEN  (1U << 4)   /**< GPIOE clock enable */
#define RCC_AHB1ENR_GPIOFEN  (1U << 5)   /**< GPIOF clock enable */
#define RCC_AHB1ENR_GPIOGEN  (1U << 6)   /**< GPIOG clock enable */
#define RCC_AHB1ENR_GPIOHEN  (1U << 7)   /**< GPIOH clock enable */

/** \brief RCC_APB2ENR - APB2 Peripheral Clock Enable Register Bits */
#define RCC_APB2ENR_USART1EN (1U << 4)   /**< USART1 clock enable */
#define RCC_APB2ENR_USART6EN (1U << 5)   /**< USART6 clock enable */

/** \brief RCC_APB1ENR - APB1 Peripheral Clock Enable Register Bits */
#define RCC_APB1ENR_USART2EN (1U << 17)  /**< USART2 clock enable */
#define RCC_APB1ENR_USART3EN (1U << 18)  /**< USART3 clock enable */
#define RCC_APB1ENR_UART4EN  (1U << 19)  /**< UART4 clock enable */
#define RCC_APB1ENR_UART5EN  (1U << 20)  /**< UART5 clock enable */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name GPIO Mode Register (MODER) Bit Definitions
 * @{
 */

#define GPIO_MODER_INPUT     0U   /**< Input mode */
#define GPIO_MODER_OUTPUT    1U   /**< Output mode */
#define GPIO_MODER_ALT_FUNC  2U   /**< Alternate function mode */
#define GPIO_MODER_ANALOG    3U   /**< Analog mode */

/** Macro to set GPIO mode for a specific pin (2 bits per pin) */
#define GPIO_MODER_SET(pin, mode) ((mode) << ((pin) * 2))
#define GPIO_MODER_MASK(pin)      (0x3U << ((pin) * 2))

/** @} */
/*---------------------------------------------------------------------------*/
/** \name GPIO Alternate Function Register (AFRL/AFRH) Bit Definitions
 * @{
 */

/** Macro to set GPIO alternate function for a specific pin (4 bits per pin) */
#define GPIO_AFR_SET(pin, func)  ((func) << (((pin) % 8) * 4))
#define GPIO_AFR_MASK(pin)       (0xFU << (((pin) % 8) * 4))

/** Alternate function values for common peripherals */
#define GPIO_AF7_USART1  7U   /**< Alternate function 7 for USART1 on STM32F4XX */
#define GPIO_AF7_USART2  7U   /**< Alternate function 7 for USART2 on STM32F4XX */
#define GPIO_AF7_USART3  7U   /**< Alternate function 7 for USART3 on STM32F4XX */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name General Purpose Timer (TIM2-TIM5) Register Structure
 * @{
 */

/** \brief General Purpose Timer register layout */
typedef struct {
  volatile uint32_t CR1;      /**< Control register 1 (offset 0x00) */
  volatile uint32_t CR2;      /**< Control register 2 (offset 0x04) */
  volatile uint32_t SMCR;     /**< Slave mode control register (offset 0x08) */
  volatile uint32_t DIER;     /**< DMA/interrupt enable register (offset 0x0C) */
  volatile uint32_t SR;       /**< Status register (offset 0x10) */
  volatile uint32_t EGR;      /**< Event generation register (offset 0x14) */
  volatile uint32_t CCMR1;    /**< Capture/compare mode register 1 (offset 0x18) */
  volatile uint32_t CCMR2;    /**< Capture/compare mode register 2 (offset 0x1C) */
  volatile uint32_t CCER;     /**< Capture/compare enable register (offset 0x20) */
  volatile uint32_t CNT;      /**< Counter register (offset 0x24) */
  volatile uint32_t PSC;      /**< Prescaler register (offset 0x28) */
  volatile uint32_t ARR;      /**< Auto-reload register (offset 0x2C) */
  volatile uint32_t _reserved1;
  volatile uint32_t CCR1;     /**< Capture/compare register 1 (offset 0x34) */
  volatile uint32_t CCR2;     /**< Capture/compare register 2 (offset 0x38) */
  volatile uint32_t CCR3;     /**< Capture/compare register 3 (offset 0x3C) */
  volatile uint32_t CCR4;     /**< Capture/compare register 4 (offset 0x40) */
} tim_registers_t;

/** \brief General Purpose Timer peripheral pointers at fixed memory addresses */
#define TIM2  ((tim_registers_t *)0x40000000UL)
#define TIM3  ((tim_registers_t *)0x40000400UL)
#define TIM4  ((tim_registers_t *)0x40000800UL)
#define TIM5  ((tim_registers_t *)0x40000C00UL)

/** \brief Advanced Control Timer peripheral pointers */
#define TIM1  ((tim_registers_t *)0x40010000UL)
#define TIM8  ((tim_registers_t *)0x40010400UL)

/** @} */
/*---------------------------------------------------------------------------*/
/** \name General Purpose Timer (TIM) CR1 (Control Register 1) Bit Definitions
 * @{
 */

#define TIM_CR1_CEN     (1U << 0)   /**< Counter enable */
#define TIM_CR1_UDIS    (1U << 1)   /**< Update disable */
#define TIM_CR1_URS     (1U << 2)   /**< Update request source */
#define TIM_CR1_OPM     (1U << 3)   /**< One pulse mode */
#define TIM_CR1_DIR     (1U << 4)   /**< Direction */
#define TIM_CR1_CMS     (3U << 5)   /**< Center-aligned mode selection */
#define TIM_CR1_ARPE    (1U << 7)   /**< Auto-reload preload enable */
#define TIM_CR1_CKD     (3U << 8)   /**< Clock division */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name General Purpose Timer (TIM) DIER (DMA/Interrupt Enable) Bit Definitions
 * @{
 */

#define TIM_DIER_UIE    (1U << 0)   /**< Update interrupt enable */
#define TIM_DIER_CC1IE  (1U << 1)   /**< Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE  (1U << 2)   /**< Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE  (1U << 3)   /**< Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE  (1U << 4)   /**< Capture/Compare 4 interrupt enable */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name General Purpose Timer (TIM) SR (Status Register) Bit Definitions
 * @{
 */

#define TIM_SR_UIF      (1U << 0)   /**< Update interrupt flag */
#define TIM_SR_CC1IF    (1U << 1)   /**< Capture/Compare 1 interrupt flag */
#define TIM_SR_CC2IF    (1U << 2)   /**< Capture/Compare 2 interrupt flag */
#define TIM_SR_CC3IF    (1U << 3)   /**< Capture/Compare 3 interrupt flag */
#define TIM_SR_CC4IF    (1U << 4)   /**< Capture/Compare 4 interrupt flag */

/** @} */
/*---------------------------------------------------------------------------*/
/** \name RCC Clock Enable Bits (continued)
 * @{
 */

/** \brief RCC_APB1ENR - APB1 Peripheral Clock Enable Register Bits (Timer section) */
#define RCC_APB1ENR_TIM2EN  (1U << 0)   /**< TIM2 clock enable */
#define RCC_APB1ENR_TIM3EN  (1U << 1)   /**< TIM3 clock enable */
#define RCC_APB1ENR_TIM4EN  (1U << 2)   /**< TIM4 clock enable */
#define RCC_APB1ENR_TIM5EN  (1U << 3)   /**< TIM5 clock enable */

/** \brief RCC_APB2ENR - APB2 Peripheral Clock Enable Register Bits (Timer section) */
#define RCC_APB2ENR_TIM1EN  (1U << 0)   /**< TIM1 clock enable */
#define RCC_APB2ENR_TIM8EN  (1U << 1)   /**< TIM8 clock enable */
#define RCC_APB2ENR_TIM9EN  (1U << 16)  /**< TIM9 clock enable */
#define RCC_APB2ENR_TIM10EN (1U << 17)  /**< TIM10 clock enable */
#define RCC_APB2ENR_TIM11EN (1U << 18)  /**< TIM11 clock enable */

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