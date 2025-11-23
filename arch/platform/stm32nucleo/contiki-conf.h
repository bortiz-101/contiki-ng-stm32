#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

/* Possibly standard includes here, e.g. stdint.h */
/*---------------------------------------------------------------------------*/
/* Include Project Specific conf */
#ifdef PROJECT_CONF_PATH
#include PROJECT_CONF_PATH
#endif /* PROJECT_CONF_PATH */
/*---------------------------------------------------------------------------*/
#include "stm32nucleo-def.h"
/*---------------------------------------------------------------------------*/
/* Include Project Specific conf */
#ifdef BOARD_CONF_PATH
#include BOARD_CONF_PATH
#else /* BOARD_CONF_PATH */
#error "BOARD_CONF_PATH undefined"
#endif /* BOARD_CONF_PATH */
/*/
/*---------------------------------------------------------------------------*/
/* Include CPU-related configuration */
#include "stm32nucleo-conf.h"
/*---------------------------------------------------------------------------*/
#endif /* CONTIKI_CONF_H */
