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
 * \file
 *         WL1 Periodic Workload Scaling Experiment
 *         Tests Contiki-NG scheduling with N periodic tasks (N = 10..50)
 *
 *         SUN-7: Workload scaling experiment
 *         - Dynamic task activation based on test parameter N
 *         - 30 seconds per N value
 *         - Records timing events via timing_log
 *         - Generates ISR load via isr_noise
 *
 * \author Contiki-NG STM32F4 Port Team
 */

#include "contiki.h"
#include "timing_log.h"
#include "isr_noise.h"
#include "dbg.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/
/** \name Configuration Constants
 * @{
 */

/** Maximum number of concurrent periodic tasks */
#define WL1_MAX_TASKS 50

/** Test array of N values - tests from 10 to 50 tasks */
static const uint16_t wl1_test_n_values[] = {10, 20, 30, 40, 50};
static const uint16_t wl1_num_test_values = 5;

/** Task periods (milliseconds) - repeating pattern: 10ms, 20ms, 50ms */
static const uint16_t wl1_task_period_pattern[3] = {10, 20, 50};

/** Busy loop iteration count for work simulation (~1% CPU per task) */
#define WL1_WORK_LOOP_ITERATIONS 18000

/** Experiment duration per N value (in seconds) */
#define WL1_DURATION_PER_TEST_SECONDS 30

/** @} */

/*---------------------------------------------------------------------------*/
/** \name Global State
 * @{
 */

/** Currently active number of tasks (dynamically set by orchestrator) */
static volatile uint16_t wl1_active_tasks = 0;

/** Event timers for each task */
static struct etimer wl1_task_timer[WL1_MAX_TASKS];

/** Task activation counter (for statistics) */
static volatile uint32_t wl1_task_activation_count[WL1_MAX_TASKS];

/** @} */

/*---------------------------------------------------------------------------*/
/** \name Utility Functions
 * @{
 */

/**
 * \brief Execute busy work to simulate task processing.
 *
 * Consumes CPU cycles via iteration loop.
 * Used to generate load for timing measurements.
 */
static void
wl1_do_work(uint32_t iterations)
{
  uint32_t i;
  volatile uint32_t dummy = 0;

  for (i = 0; i < iterations; i++) {
    dummy += i;  /* Prevent compiler optimization */
  }
}

/** @} */

/*---------------------------------------------------------------------------*/
/** \name Task Process
 * @{
 */

/**
 * \brief Single generic WL1 task process.
 *
 * Demonstrates task behavior:
 * - Waits for period timer
 * - Logs timing events
 * - Performs work
 * - Reschedules
 */
PROCESS(wl1_task_process, "WL1 Task");

PROCESS_THREAD(wl1_task_process, ev, data)
{
  static uint16_t task_id = 0;
  static uint16_t period_ms;

  PROCESS_BEGIN();

  while (1) {
    /* Check if this task should be active */
    if (task_id < wl1_active_tasks) {
      period_ms = wl1_task_period_pattern[task_id % 3];

      /* Wait for next period */
      etimer_set(&wl1_task_timer[task_id], (period_ms * CLOCK_SECOND) / 1000);
      PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&wl1_task_timer[task_id]));

      /* Log timing events */
      timing_log_timestamp(TIMING_LOG_EVENT_RELEASE, task_id);
      timing_log_timestamp(TIMING_LOG_EVENT_START, task_id);

      /* Simulate work */
      wl1_do_work(WL1_WORK_LOOP_ITERATIONS);

      /* Log completion */
      timing_log_timestamp(TIMING_LOG_EVENT_END, task_id);

      /* Update activation counter */
      wl1_task_activation_count[task_id]++;
    } else {
      /* Wait for activation */
      PROCESS_WAIT_EVENT();
    }
  }

  PROCESS_END();
}

/** @} */

/*---------------------------------------------------------------------------*/
/** \name Orchestrator Process
 * @{
 */

/**
 * \brief WL1 Orchestrator - runs multiple experiments with varying N.
 *
 * For each N in wl1_test_n_values:
 * 1. Initializes timing log
 * 2. Activates N tasks (sets wl1_active_tasks = N)
 * 3. Runs for WL1_DURATION_PER_TEST_SECONDS
 * 4. Records statistics
 * 5. Repeats for next N
 *
 * After all tests complete, dumps CSV log to serial.
 */
PROCESS(wl1_orchestrator_process, "WL1 Orchestrator");

AUTOSTART_PROCESSES(&wl1_orchestrator_process);

PROCESS_THREAD(wl1_orchestrator_process, ev, data)
{
  static struct etimer test_timer;
  static int i, j;
  static uint16_t current_n;
  static char msg[256];

  PROCESS_BEGIN();

  dbg_send_bytes((const unsigned char *)"\n\n=== WL1 Periodic Workload Scaling Experiment ===\n", 51);
  dbg_send_bytes((const unsigned char *)"Testing N values: 10, 20, 30, 40, 50 tasks\n", 44);
  dbg_send_bytes((const unsigned char *)"Duration per test: 30 seconds\n", 30);
  dbg_send_bytes((const unsigned char *)"\n", 1);

  /* Initialize ISR noise (0% load for baseline) */
  isr_noise_init();
  isr_noise_set_iterations(0);
  isr_noise_start();
  dbg_send_bytes((const unsigned char *)"[INIT] ISR noise started (0% load)\n", 35);

  /* Start the periodic task process */
  process_start(&wl1_task_process, NULL);
  dbg_send_bytes((const unsigned char *)"[INIT] Task process started\n", 28);

  /* Initialize timing log before first test */
  timing_log_init();
  dbg_send_bytes((const unsigned char *)"[INIT] Timing log initialized\n\n", 31);

  /* Loop through each N value */
  for (j = 0; j < wl1_num_test_values; j++) {
    current_n = wl1_test_n_values[j];

    snprintf(msg, sizeof(msg), "=== Test %d: N=%u tasks ===\n", j + 1, current_n);
    dbg_send_bytes((const unsigned char *)msg, strlen(msg));

    /* Clear activation counters */
    for (i = 0; i < WL1_MAX_TASKS; i++) {
      wl1_task_activation_count[i] = 0;
    }

    /* Activate N tasks */
    wl1_active_tasks = current_n;
    snprintf(msg, sizeof(msg), "Activating %u tasks...\n", current_n);
    dbg_send_bytes((const unsigned char *)msg, strlen(msg));

    /* Run for 30 seconds */
    snprintf(msg, sizeof(msg), "Running for %d seconds...\n", WL1_DURATION_PER_TEST_SECONDS);
    dbg_send_bytes((const unsigned char *)msg, strlen(msg));

    etimer_set(&test_timer, WL1_DURATION_PER_TEST_SECONDS * CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&test_timer));

    /* Record results for this N */
    dbg_send_bytes((const unsigned char *)"Test complete.\n", 15);
    snprintf(msg, sizeof(msg), "Total log entries: %u\n\n", timing_log_get_count());
    dbg_send_bytes((const unsigned char *)msg, strlen(msg));
  }

  /* Stop ISR noise */
  isr_noise_stop();
  dbg_send_bytes((const unsigned char *)"[DONE] All tests complete. Stopping ISR noise.\n\n", 50);

  /* Dump CSV log */
  dbg_send_bytes((const unsigned char *)"[CSV OUTPUT]\n", 13);
  timing_log_csv_dump();

  /* Summary */
  dbg_send_bytes((const unsigned char *)"\n[SUMMARY]\n", 11);
  snprintf(msg, sizeof(msg),
           "Tests: %u, Log entries: %u, Max N: %u\n",
           wl1_num_test_values, timing_log_get_count(), wl1_test_n_values[wl1_num_test_values - 1]);
  dbg_send_bytes((const unsigned char *)msg, strlen(msg));

  dbg_send_bytes((const unsigned char *)"=== Experiment finished ===\n", 28);

  PROCESS_END();
}

/** @} */

/*---------------------------------------------------------------------------*/
