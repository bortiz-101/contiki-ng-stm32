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
 * \defgroup timing-log Task timing data collection
 *
 * High-precision timestamp recording for task timing measurements.
 * Records task events (release, start, end) using DWT cycle counter.
 * Separate from Contiki-NG's general logging system (sys/log.h).
 *
 * @{
 *
 * \file
 *        Task timing log header for timing experiments
 */

#ifndef TIMING_LOG_H_
#define TIMING_LOG_H_

#include <stdint.h>

/*---------------------------------------------------------------------------*/

/** \brief Event type enumeration for timing_log_timestamp() */
typedef enum {
  TIMING_LOG_EVENT_RELEASE = 0,  /**< Task released/scheduled */
  TIMING_LOG_EVENT_START = 1,    /**< Task started execution */
  TIMING_LOG_EVENT_END = 2       /**< Task completed execution */
} timing_log_event_t;

/** \brief Timing log entry: event timestamp with task ID */
typedef struct {
  uint32_t timestamp_us;  /**< Timestamp in microseconds (from DWT) */
  uint16_t task_id;       /**< Task identifier */
  uint8_t event_type;     /**< Event type (timing_log_event_t) */
  uint8_t _padding;       /**< Padding for alignment (unused) */
} timing_log_entry_t;

/*---------------------------------------------------------------------------*/

/**
 * \brief Initialize the timing log system.
 *
 * Must be called once at startup before using timing_log_timestamp().
 * Requires DWT to be initialized (dwt_init()).
 */
void timing_log_init(void);

/**
 * \brief Record a timestamp for a task event.
 *
 * \param event_type The event type (release, start, or end)
 * \param task_id The task identifier (0-65535)
 *
 * Captures the current DWT cycle counter and converts to microseconds,
 * storing the event in a ring buffer for later retrieval.
 *
 * \note This function is fast (~5-10 cycles) and can be called from ISR.
 * \note Ring buffer wraps around; oldest entries are overwritten if full.
 */
void timing_log_timestamp(timing_log_event_t event_type, uint16_t task_id);

/**
 * \brief Get the number of logged events.
 *
 * \return The count of events in the ring buffer (0 to TIMING_LOG_BUFFER_SIZE).
 */
uint16_t timing_log_get_count(void);

/**
 * \brief Retrieve a logged event by index.
 *
 * \param index The event index (0 to timing_log_get_count()-1)
 * \param entry Pointer to store the retrieved log entry
 *
 * \return 0 on success, -1 if index is out of bounds.
 */
int timing_log_get_entry(uint16_t index, timing_log_entry_t *entry);

/**
 * \brief Dump all logged events as CSV to serial output.
 *
 * Outputs each event in CSV format:
 *   task_id,event_type,timestamp_us
 *
 * Uses dbg_send_bytes() for serial transmission (115200 baud).
 *
 * \note Blocking operation; takes ~50-100 ms depending on event count.
 */
void timing_log_csv_dump(void);

/**
 * \brief Reset the timing log buffer (clear all entries).
 */
void timing_log_reset(void);

/*---------------------------------------------------------------------------*/

/** \brief Configuration: maximum events in ring buffer */
#define TIMING_LOG_BUFFER_SIZE 1024

/** @} */

#endif /* TIMING_LOG_H_ */
