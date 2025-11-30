/*
 * Copyright (c) 2025, Contiki-NG STM32F4 Timing Experiments
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
 * \addtogroup timing-log
 * @{
 *
 * \file
 *        Task timing log implementation for timing experiments
 */

#include "timing_log.h"
#include "dwt.h"
#include "dbg.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/

/** Ring buffer for timing events */
static timing_log_entry_t timing_log_buffer[TIMING_LOG_BUFFER_SIZE];

/** Current write index in ring buffer */
static uint16_t timing_log_write_index = 0;

/** Total number of events logged (for overflow detection) */
static uint16_t timing_log_total_count = 0;

/*---------------------------------------------------------------------------*/

void
timing_log_init(void)
{
  /* Clear the buffer */
  memset(timing_log_buffer, 0, sizeof(timing_log_buffer));
  timing_log_write_index = 0;
  timing_log_total_count = 0;
}

/*---------------------------------------------------------------------------*/

void
timing_log_timestamp(timing_log_event_t event_type, uint16_t task_id)
{
  uint32_t cycles;
  uint32_t timestamp_us;

  /* Get current DWT cycle count */
  cycles = dwt_get_cycles();

  /* Convert cycles to microseconds (180 MHz clock) */
  timestamp_us = dwt_cycles_to_us(cycles);

  /* Write entry to ring buffer */
  timing_log_buffer[timing_log_write_index].timestamp_us = timestamp_us;
  timing_log_buffer[timing_log_write_index].task_id = task_id;
  timing_log_buffer[timing_log_write_index].event_type = (uint8_t)event_type;
  timing_log_buffer[timing_log_write_index]._padding = 0;

  /* Advance write pointer (wrap around if needed) */
  timing_log_write_index = (timing_log_write_index + 1) % TIMING_LOG_BUFFER_SIZE;
  timing_log_total_count++;
}

/*---------------------------------------------------------------------------*/

uint16_t
timing_log_get_count(void)
{
  /* Return actual count, capped at buffer size */
  if (timing_log_total_count > TIMING_LOG_BUFFER_SIZE) {
    return TIMING_LOG_BUFFER_SIZE;  /* Buffer is full */
  }
  return timing_log_total_count;
}

/*---------------------------------------------------------------------------*/

int
timing_log_get_entry(uint16_t index, timing_log_entry_t *entry)
{
  uint16_t actual_count;
  uint16_t read_index;

  if (entry == NULL) {
    return -1;
  }

  actual_count = timing_log_get_count();

  if (index >= actual_count) {
    return -1;  /* Index out of bounds */
  }

  /* Calculate read index (accounts for ring buffer wrap) */
  if (timing_log_total_count <= TIMING_LOG_BUFFER_SIZE) {
    /* Buffer not full yet, read sequentially from start */
    read_index = index;
  } else {
    /* Buffer full; oldest entry is at timing_log_write_index */
    read_index = (timing_log_write_index + index) % TIMING_LOG_BUFFER_SIZE;
  }

  *entry = timing_log_buffer[read_index];
  return 0;
}

/*---------------------------------------------------------------------------*/

void
timing_log_csv_dump(void)
{
  uint16_t count;
  uint16_t i;
  timing_log_entry_t entry;
  char csv_line[64];
  int len;

  count = timing_log_get_count();

  /* Print CSV header */
  dbg_send_bytes((const unsigned char *)"task_id,event_type,timestamp_us\n", 33);

  /* Print each entry */
  for (i = 0; i < count; i++) {
    if (timing_log_get_entry(i, &entry) == 0) {
      /* Format: task_id,event_type,timestamp_us\n */
      len = snprintf(csv_line, sizeof(csv_line), "%u,%u,%lu\n",
                     entry.task_id, entry.event_type, entry.timestamp_us);

      if (len > 0 && len < (int)sizeof(csv_line)) {
        dbg_send_bytes((const unsigned char *)csv_line, len);
      }
    }
  }
}

/*---------------------------------------------------------------------------*/

void
timing_log_reset(void)
{
  memset(timing_log_buffer, 0, sizeof(timing_log_buffer));
  timing_log_write_index = 0;
  timing_log_total_count = 0;
}

/*---------------------------------------------------------------------------*/

/** @} */
