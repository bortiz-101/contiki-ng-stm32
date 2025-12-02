/**
  ******************************************************************************
  * @file    stm32f4xx_hal_conf.h
  * @brief   HAL configuration file for Contiki-NG STM32F4 port
  *
  * This file configures which HAL modules are enabled for the build.
  * Customize based on your platform's needs.
  ******************************************************************************
  */

#ifndef STM32F4XX_HAL_CONF_H
#define STM32F4XX_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* CMSIS includes - required by HAL */
#include "stm32f446xx.h"

/* ########################## Module Selection ############################## */
/**
 * @brief List of HAL modules to be used in this build
 * Uncomment the modules you need for your platform
 */
#define HAL_MODULE_ENABLED

/* Include HAL driver headers in correct order to resolve dependencies */
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_rcc_ex.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_pwr_ex.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_uart.h"

/* Core HAL modules */
#define HAL_CORTEX_MODULE_ENABLED    /* Cortex-M4 system tick, NVIC */
#define HAL_DMA_MODULE_ENABLED       /* Direct Memory Access */
#define HAL_FLASH_MODULE_ENABLED     /* Flash programming */
#define HAL_GPIO_MODULE_ENABLED      /* General Purpose I/O */
#define HAL_PWR_MODULE_ENABLED       /* Power management */
#define HAL_RCC_MODULE_ENABLED       /* Reset and Clock Control */

/* Communication modules - customize as needed */
#define HAL_UART_MODULE_ENABLED      /* UART for debug output */
/* #define HAL_USART_MODULE_ENABLED */
/* #define HAL_SPI_MODULE_ENABLED */
/* #define HAL_I2C_MODULE_ENABLED */
/* #define HAL_I2S_MODULE_ENABLED */

/* Timer/Counter modules */
/* #define HAL_TIM_MODULE_ENABLED */
/* #define HAL_RTC_MODULE_ENABLED */
/* #define HAL_IWDG_MODULE_ENABLED */
/* #define HAL_WWDG_MODULE_ENABLED */

/* Analog modules */
/* #define HAL_ADC_MODULE_ENABLED */
/* #define HAL_DAC_MODULE_ENABLED */

/* Other modules */
/* #define HAL_CAN_MODULE_ENABLED */
/* #define HAL_ETH_MODULE_ENABLED */
/* #define HAL_NAND_MODULE_ENABLED */
/* #define HAL_NOR_MODULE_ENABLED */
/* #define HAL_SRAM_MODULE_ENABLED */
/* #define HAL_DCMI_MODULE_ENABLED */
/* #define HAL_HASH_MODULE_ENABLED */
/* #define HAL_RNG_MODULE_ENABLED */
/* #define HAL_CRC_MODULE_ENABLED */

/* ########################## HSE/HSI Values definition ##################### */
/**
 * @brief Adjust the External High Speed oscillator (HSE) startup timeout value
 */
#if !defined(HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint32_t)100)   /* Time out for HSE start up, in ms */
#endif

/**
 * @brief Adjust the External Low Speed oscillator (LSE) startup timeout value
 */
#if !defined(LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((uint32_t)5000)  /* Time out for LSE start up, in ms */
#endif

/**
 * @brief External oscillator (HSE) value in Hz
 */
#if !defined(EXTERNAL_CLOCK_VALUE)
  #define EXTERNAL_CLOCK_VALUE    ((uint32_t)25000000)  /* Value of the external oscillator in Hz */
#endif /* HSE_STARTUP_TIMEOUT */

/**
 * @brief Internal High Speed oscillator (HSI) value.
 *   Is the nominal value without temperature nor voltage dependency. (±2%)
 */
#if !defined (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
 * @brief External High Speed oscillator (HSE) value.
 *   This is the nominal value. Adjust as needed for your board.
 */
#if !defined (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)25000000) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

/**
 * @brief External oscillator is assumed to be used if any of the following is true
 */
#if !defined (HSE_BY_DEFAULT)
  #define HSE_BY_DEFAULT       0
#endif /* HSE_BY_DEFAULT */

/* ########################### System Clock Frequency ######################## */
/**
 * @brief STM32F446RE system clock frequency
 */
#define SYSCLK_FREQ_180MHZ     180000000

/* ########################## Embedded Flash Memory ########################## */
/**
 * @brief Adjust the number of wait states for Flash access
 */
#if !defined(FLASH_LATENCY)
  #define FLASH_LATENCY  ((uint8_t)5)
#endif

/* ########################## Timeout Values ################################# */
/**
 * @brief Adjust timeout values for various operations
 */
#if !defined(USE_TIMEOUT)
  #define USE_TIMEOUT    0U
#endif

/* ########################## Tick Interrupt Priority ######################## */
/**
 * @brief SysTick interrupt priority - used by HAL_InitTick()
 * Priority levels: 0-15 (lower number = higher priority)
 * We use priority 15 (lowest) to not interfere with critical system operations
 */
#if !defined(TICK_INT_PRIORITY)
  #define TICK_INT_PRIORITY  ((uint32_t)15U)
#endif

/* ########################## Assert Selection ############################## */
/**
 * @brief Uncomment the line below to expanse the "assert_param" macro in the
 *        HAL drivers code
 */
#define USE_FULL_ASSERT    1U

#ifdef USE_FULL_ASSERT
/**
 * @brief assert_param macro is used for function parameter check.
 * It is defined in the stm32f4xx_hal_conf.h when USE_FULL_ASSERT is set.
 * @param expr: If expr is false, it calls assert_failed function
 *              which should implement an infinite loop.
 */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

/* ########################## DEBUG PIN Configuration ######################## */
/**
 * @brief Enable the DBGMCU debug pin remapping for debugging
 */
/* #define USE_DBGMCU */

#ifdef __cplusplus
}
#endif

#endif /* STM32F4XX_HAL_CONF_H */
