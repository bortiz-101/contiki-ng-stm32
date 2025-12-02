/**
 * @file hal-msp.c
 * @brief HAL Microcontroller Support Package (MSP) initialization
 *
 * This file provides MSP initialization callbacks required by the STM32 HAL.
 * It configures GPIO, clocks, and other peripherals when HAL functions are called.
 *
 * This is called automatically by HAL_Init() and peripheral initialization functions.
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"
#include <stdint.h>

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "HAL-MSP"
#define LOG_LEVEL LOG_LEVEL_NONE

/*---------------------------------------------------------------------------*/
/**
 * \brief HAL MSP Initialization
 * 
 * Called once at HAL initialization to set up global MSP settings.
 * Configures SYSCFG, PWR, and NVIC priority grouping.
 */
void
HAL_MspInit(void)
{
  /* Enable syscfg and power clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* Set NVIC priority grouping (already done in soc.c, but HAL may call this) */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  LOG_DBG("HAL_MspInit() completed\n");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief HAL UART MSP Initialization
 *
 * Called by HAL_UART_Init() to initialize GPIO and clocks for UART peripherals.
 * This handles all UART instances (USART1, USART2, USART3, UART4, UART5).
 *
 * @param huart UART handle being initialized
 */
void
HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  if (huart->Instance == USART2) {
    /* USART2 on PA2 (TX), PA3 (RX) - Debug console */
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LOG_DBG("USART2 MSP initialized (PA2/PA3)\n");
  }
  else if (huart->Instance == USART1) {
    /* USART1 on PA9 (TX), PA10 (RX) */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LOG_DBG("USART1 MSP initialized (PA9/PA10)\n");
  }
  else if (huart->Instance == USART3) {
    /* USART3 on PB10 (TX), PC5 (RX) */
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    LOG_DBG("USART3 MSP initialized (PB10/PC5)\n");
  }
  else if (huart->Instance == UART4) {
    /* UART4 on PA0 (TX), PA1 (RX) */
    __HAL_RCC_UART4_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LOG_DBG("UART4 MSP initialized (PA0/PA1)\n");
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief HAL UART MSP De-Initialization
 *
 * Called by HAL_UART_DeInit() to disable UART peripherals.
 * This is typically not needed for embedded systems that don't dynamically
 * enable/disable UART, but is required for API completeness.
 *
 * @param huart UART handle being de-initialized
 */
void
HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2) {
    __HAL_RCC_USART2_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
  }
  else if (huart->Instance == USART1) {
    __HAL_RCC_USART1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
  }
  else if (huart->Instance == USART3) {
    __HAL_RCC_USART3_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_5);
  }
  else if (huart->Instance == UART4) {
    __HAL_RCC_UART4_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);
  }
}

/*---------------------------------------------------------------------------*/
/** @} */
