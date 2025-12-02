/*
 * Copyright (c) 2024, Contiki-NG STM32F4 Port Contributors
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \addtogroup stm32f4xx-dbg
 * @{
 *
 * \file
 * Debug output driver for STM32F4xx using USART2 with STM32 HAL
 *
 * Uses USART2 on PA2 (TX) / PA3 (RX) connected to ST-LINK virtual COM port.
 * HAL is used for all peripheral initialization and character transmission.
 *
 * Features:
 * - USART2 at 115200 baud
 * - Configured for typical IoT debugging
 * - Uses HAL_UART for compatibility and maintainability
 */

#include "contiki.h"
#include "dbg.h"

#include <stdint.h>

/* HAL GPIO and UART support */
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_rcc.h"

/* ========== Global UART Handle ========== */
static UART_HandleTypeDef huart2;

/*---------------------------------------------------------------------------*/
/**
 * \brief Configure GPIO pins for USART2 (PA2, PA3)
 *
 * Sets PA2 and PA3 as USART2 TX and RX respectively.
 */
static void
dbg_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Configure PA2 (USART2 TX) and PA3 (USART2 RX) as AF7 */
  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           /* Alternate function, push-pull */
  GPIO_InitStruct.Pull = GPIO_NOPULL;               /* No pull resistors (STM32 has internal) */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; /* High speed for 115200 baud */
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;      /* USART2 on AF7 */

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize USART2 for debug output using HAL
 *
 * Configures USART2 at 115200 baud, 8N1 (8 data, no parity, 1 stop).
 * PA2 = TX, PA3 = RX (connected to ST-LINK on Nucleo-F446RE).
 *
 * HAL_UART_Init handles all register configuration via the HAL.
 * This is preferred over raw register access for:
 * - Vendor support and updates
 * - Easier debugging
 * - Compatibility with other HAL functions
 */
void
dbg_init(void)
{
  /* Configure GPIO pins for UART */
  dbg_gpio_init();

  /* Enable USART2 clock */
  __HAL_RCC_USART2_CLK_ENABLE();

  /* Configure USART2 handle */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

  /* Initialize USART2 with HAL */
  if (HAL_UART_Init(&huart2) != HAL_OK) {
    /* Initialization failed - halt here */
    while (1) {
      ;
    }
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Send a single character via USART2
 *
 * Uses HAL_UART_Transmit to send one byte.
 * Blocks until transmission is complete (with 100ms timeout).
 *
 * @param c Character to send
 */
void
dbg_putchar(unsigned char c)
{
  /* HAL_UART_Transmit blocks until transmission is done */
  HAL_UART_Transmit(&huart2, (uint8_t *)&c, 1, 100);
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Send multiple bytes via USART2
 *
 * Uses HAL_UART_Transmit for efficiency (single transmission vs. per-byte).
 *
 * @param buf Buffer containing bytes to send
 * @param len Number of bytes to send
 */
void
dbg_send_bytes(const unsigned char *buf, unsigned int len)
{
  /* Transmit entire buffer at once for efficiency */
  if (len > 0) {
    HAL_UART_Transmit(&huart2, (uint8_t *)buf, len, 1000);
  }
}

/*---------------------------------------------------------------------------*/
/** @} */
