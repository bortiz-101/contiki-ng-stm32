/*
 * Debug output driver header for STM32F4XX
 */
#ifndef DBG_H_
#define DBG_H_

#include <stdint.h>

void dbg_init(void);
void dbg_putchar(unsigned char c);
void dbg_send_bytes(const unsigned char *buf, unsigned int len);

#endif /* DBG_H_ */
