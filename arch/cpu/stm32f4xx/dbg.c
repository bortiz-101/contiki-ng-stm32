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
 * Debug output driver for STM32F4XX using USART2
 * USART2 on PA2 (TX), PA3 (RX) - connected to ST-LINK virtual COM port
 * Baud rate: 115200 @ 45 MHz APB1 clock
 */

#include "contiki.h"
#include "system_stm32f4xx.h"

#include <stdint.h>

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize USART2 for debug output
 *
 * Configures USART2 with:
 * - Baud rate: 115200
 * - Data bits: 8
 * - Stop bits: 1
 * - No parity
 * - TX pin: PA2 (AF7)
 * - RX pin: PA3 (AF7)
 * - APB1 clock: 45 MHz
 */
void
dbg_init(void)
{
  uint32_t baud_div;

  /* Enable GPIOA clock */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  /* Configure PA2 (USART2 TX) as alternate function 7 */
  GPIOA->MODER &= ~GPIO_MODER_MASK(2);
  GPIOA->MODER |= GPIO_MODER_SET(2, GPIO_MODER_ALT_FUNC);
  GPIOA->AFRL &= ~GPIO_AFR_MASK(2);
  GPIOA->AFRL |= GPIO_AFR_SET(2, GPIO_AF7_USART2);

  /* Configure PA3 (USART2 RX) as alternate function 7 */
  GPIOA->MODER &= ~GPIO_MODER_MASK(3);
  GPIOA->MODER |= GPIO_MODER_SET(3, GPIO_MODER_ALT_FUNC);
  GPIOA->AFRL &= ~GPIO_AFR_MASK(3);
  GPIOA->AFRL |= GPIO_AFR_SET(3, GPIO_AF7_USART2);

  /* Enable USART2 clock on APB1 */
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  /* Set baud rate divisor: APB1 45MHz / (16 * 115200) ≈ 24 */
  baud_div = 24;
  USART2->BRR = baud_div;

  /* Configure USART2:
   * - 8 data bits (default, M=0)
   * - 1 stop bit (default)
   * - No parity (default)
   * - Enable transmitter and receiver
   */
  USART2->CR1 = USART_CR1_TE | USART_CR1_RE;

  /* Enable USART2 */
  USART2->CR1 |= USART_CR1_UE;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Send a single character via USART2
 *
 * Blocks until the transmit buffer is ready.
 */
void
dbg_putchar(unsigned char c)
{
  /* Wait for transmit data register to be empty */
  while(!(USART2->SR & USART_SR_TXE)) {
    ;
  }

  /* Send the character */
  USART2->DR = c;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Send multiple bytes via USART2
 *
 * Sends a buffer of bytes one by one.
 */
void
dbg_send_bytes(const unsigned char *buf, unsigned int len)
{
  unsigned int i;

  for(i = 0; i < len; i++) {
    dbg_putchar(buf[i]);
  }
}

/*---------------------------------------------------------------------------*/
/** @} */
