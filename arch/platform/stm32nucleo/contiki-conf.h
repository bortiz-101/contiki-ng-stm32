#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

/*---------------------------------------------------------------------------*/
/* Include Project Specific conf */
#ifdef PROJECT_CONF_PATH
#include PROJECT_CONF_PATH
#endif /* PROJECT_CONF_PATH */
/*---------------------------------------------------------------------------*/
#include "stm32f4xx-def.h"
/*---------------------------------------------------------------------------*/
/* Include Board Specific conf */
#ifdef BOARD_CONF_PATH
#include BOARD_CONF_PATH
#else
#error "BOARD_CONF_PATH undefined"
#endif
/*---------------------------------------------------------------------------*/
/* Include Board Specific def */
#ifdef BOARD_DEF_PATH
#include BOARD_DEF_PATH
#else
#error "BOARD_DEF_PATH undefined"
#endif
/*---------------------------------------------------------------------------*/
#endif /* CONTIKI_CONF_H */
