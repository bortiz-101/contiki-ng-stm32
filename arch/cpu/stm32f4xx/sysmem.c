/*
 * Copyright (c) 2024, STM32 Contiki-NG Port
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * \file
 *         Heap memory management for STM32F4xx (Newlib _sbrk)
 * \author
 *         Port maintainer
 */

/* Suppress false positive array bounds warning for intentional pointer arithmetic */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"

#include <unistd.h>
#include <stdlib.h>

/* Linker symbols (defined in linker script) */
extern char _end;           /* End of BSS (start of heap) */
extern char _estack;        /* End of stack (start of SRAM) */

/* Current heap end pointer */
static char *heap_end = &_end;

/**
 * \brief   _sbrk() - Allocate heap memory
 * \param   incr    Number of bytes to allocate
 * \return  Pointer to allocated block, -1 on error
 *
 * This function is called by malloc() to extend the heap.
 * It uses linker symbols to maintain heap/stack separation.
 */
void *
_sbrk(int incr)
{
  char *prev_heap_end;

  /* Check for invalid allocation */
  if(incr == 0) {
    return heap_end;
  }

  /* Check for negative allocation (heap shrink) */
  if(incr < 0) {
    if((heap_end + incr) < &_end) {
      /* Would shrink heap below its start */
      return (void *)-1;
    }
    heap_end += incr;
    return heap_end;
  }

  prev_heap_end = heap_end;

  /* Check for heap/stack collision (conservative check) */
  if((heap_end + incr) > (&_estack - 256)) {
    /* Heap has grown too large - leave 256 bytes for stack guard */
    return (void *)-1;
  }

  heap_end += incr;
  return (void *)prev_heap_end;
}

/* Restore default warning settings */
#pragma GCC diagnostic pop
