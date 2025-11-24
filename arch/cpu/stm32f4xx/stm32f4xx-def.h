/**
 * \defgroup stm32f4xx STM32F4 MCU Definitions
 * @{
 */

/**
 * \file
 * STM32F4 series MCU definitions
 *
 * This file provides base MCU configuration and definitions inherited
 * from the ARM Cortex-M4 defaults. It is included early in the
 * configuration chain (from contiki-conf.h) so avoid including
 * OS-level headers here to prevent circular dependencies.
 */

#ifndef STM32F4XX_DEF_H_
#define STM32F4XX_DEF_H_

#include <stdint.h>
#include "stm32f4xx.h"

/* Clock configuration - inherited from ARM CM4 defaults */
#define CLOCK_CONF_SIZE 4
#define CLOCK_CONF_SECOND 128

#endif /* STM32F4XX_DEF_H_ */

/** @} */