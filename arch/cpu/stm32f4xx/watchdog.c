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
 * \addtogroup stm32f4xx-watchdog
 * @{
 *
 * \file
 * Watchdog driver for STM32F4XX using IWDG (Independent Watchdog)
 */

#include "contiki.h"
#include "system_stm32f4xx.h"

#include <stdint.h>

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "WATCHDOG"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Watchdog state */
static volatile uint8_t watchdog_enabled = 0;

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize the watchdog
 *
 * Configures IWDG with:
 * - Prescaler: 256 (gives 40kHz/256 = 156.25 Hz counter clock)
 * - Reload value: 156 (gives ~1 second timeout at 156.25 Hz)
 * - This allows watchdog_periodic() to kick watchdog every ~250ms safely
 */
void
watchdog_init(void)
{
  /* Enable access to PR and RLR registers */
  IWDG->KR = IWDG_KR_KEY_ENABLE;

  /* Wait for prescaler update to complete */
  while(IWDG->SR & IWDG_SR_PVU) {
    ;
  }

  /* Set prescaler to 256
   * IWDG clock = LSI (40 kHz typical)
   * Counter clock = 40kHz / 256 = 156.25 Hz
   */
  IWDG->PR = IWDG_PR_DIV256;

  /* Wait for prescaler update to complete */
  while(IWDG->SR & IWDG_SR_PVU) {
    ;
  }

  /* Set reload value (timeout period)
   * Timeout = (RLR + 1) / (counter_clock)
   * 156 counter ticks = 1 second at 156.25 Hz
   */
  IWDG->RLR = 156;

  /* Wait for reload value update to complete */
  while(IWDG->SR & IWDG_SR_RVU) {
    ;
  }

  LOG_DBG("Watchdog initialized (1 second timeout)\n");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Start the watchdog
 *
 * Enables the watchdog counter. Must call watchdog_periodic() regularly
 * to prevent a reset.
 */
void
watchdog_start(void)
{
  /* Start the watchdog */
  IWDG->KR = IWDG_KR_KEY_START;
  watchdog_enabled = 1;
  LOG_DBG("Watchdog started\n");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Kick the watchdog (reload counter)
 *
 * Resets the watchdog counter. Must be called periodically (at least
 * once per second with current configuration).
 */
void
watchdog_periodic(void)
{
  if(watchdog_enabled) {
    /* Reload the counter */
    IWDG->KR = IWDG_KR_KEY_RELOAD;
  }
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Stop the watchdog
 *
 * Note: On STM32F4, the IWDG cannot be disabled once started.
 * This function does nothing but is provided for API compatibility.
 */
void
watchdog_stop(void)
{
  /* Note: IWDG cannot be stopped once started on STM32F4 */
  LOG_WARN("Watchdog cannot be stopped on STM32F4\n");
}

/*---------------------------------------------------------------------------*/
/**
 * \brief Force a watchdog-triggered reset
 *
 * Stops feeding the watchdog, allowing it to timeout and trigger a reset.
 */
void
watchdog_reboot(void)
{
  /* Disable watchdog feeding - let it timeout */
  watchdog_enabled = 0;
  
  /* Loop until watchdog resets the system */
  while(1) {
    ;
  }
}

/*---------------------------------------------------------------------------*/
/** @} */
