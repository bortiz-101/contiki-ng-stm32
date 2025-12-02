#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

/*---------------------------------------------------------------------------*/
/* Include Project Specific conf (highest priority - user overrides) */
#ifdef PROJECT_CONF_PATH
#include PROJECT_CONF_PATH
#endif /* PROJECT_CONF_PATH */
/*---------------------------------------------------------------------------*/

/* Include CPU-specific non-modifiable definitions */
#include "stm32f4xx-def.h"

/* Include Board-specific non-modifiable definitions */
#ifdef BOARD_DEF_PATH
#include BOARD_DEF_PATH
#else
#error "BOARD_DEF_PATH not defined - set in platform Makefile"
#endif

/*---------------------------------------------------------------------------*/
/* 
 * ==================== User Configuration Sections ====================
 * Sections below can be modified by users in project-conf.h
 */
/*---------------------------------------------------------------------------*/

/* Network stack configuration */

/* Define the statistics type - required by uip.h */
typedef unsigned int uip_stats_t;

/* Byte order */
#define UIP_CONF_BYTE_ORDER UIP_LITTLE_ENDIAN

/* Enable IPv6 networking */
#define NETSTACK_CONF_WITH_IPV6 1

/* Configure MAC layer - use nullmac for hello-world */
#ifndef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC csma_driver
#endif

/* Configure RDC (Radio Duty Cycling) - nullrdc for always-on operation */
#ifndef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC nullrdc_driver
#endif

/* Configure network layer - 6LoWPAN compression */
#ifndef NETSTACK_CONF_NETWORK
#define NETSTACK_CONF_NETWORK sicslowpan_driver
#endif

/* Configure radio driver - null radio for hello-world (no radio) */
#ifndef NETSTACK_CONF_RADIO
#define NETSTACK_CONF_RADIO nullradio_driver
#endif

/* Routing protocol - RPL Lite */
#ifndef NETSTACK_CONF_ROUTING
#define NETSTACK_CONF_ROUTING rpl_lite_driver
#endif

/* Memory constraints for resource-limited devices */
#ifndef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM 8
#endif

#ifndef NBR_TABLE_CONF_MAX_NEIGHBORS
#define NBR_TABLE_CONF_MAX_NEIGHBORS 16
#endif

#ifndef NETSTACK_MAX_ROUTE_ENTRIES
#define NETSTACK_MAX_ROUTE_ENTRIES 16
#endif

/* Buffer sizes */
#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE 240
#endif

/*---------------------------------------------------------------------------*/
/* Include Board-specific configurable definitions (lowest priority) */
#ifdef BOARD_CONF_PATH
#include BOARD_CONF_PATH
#endif

/* Include CPU-specific configurable definitions */
#include "stm32f4xx-conf.h"

/*---------------------------------------------------------------------------*/
#endif /* CONTIKI_CONF_H */
