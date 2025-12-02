/**
 * @file watchdog-stub.c
 * @brief Watchdog stub implementation for STM32F4
 *
 * This is a minimal stub that provides watchdog_* functions without
 * actually implementing watchdog functionality. Can be replaced with
 * a real implementation later.
 */

#include "os/dev/watchdog.h"

void
watchdog_init(void)
{
  /* Stub: watchdog initialization disabled for now */
}

void
watchdog_start(void)
{
  /* Stub: watchdog start disabled for now */
}

void
watchdog_periodic(void)
{
  /* Stub: watchdog periodic refresh disabled for now */
}

void
watchdog_stop(void)
{
  /* Stub: watchdog stop disabled for now */
}

void
watchdog_reboot(void)
{
  /* Stub: watchdog reboot - infinite loop instead */
  while (1) {
    ;
  }
}
