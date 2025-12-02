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
 *         Newlib syscalls implementation for STM32F4xx
 * \author
 *         Port maintainer
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

/* Forward declarations for debug I/O */
extern int dbg_putchar(int c);
extern int dbg_getchar(void);

/* Weak functions that can be overridden by user code */
__attribute__((weak)) int __io_putchar(int c)
{
  return dbg_putchar(c);
}

__attribute__((weak)) int __io_getchar(void)
{
  return dbg_getchar();
}

/**
 * \brief   _write() - Write to file descriptor
 * \param   fd      File descriptor (1=stdout, 2=stderr)
 * \param   ptr     Pointer to data
 * \param   len     Number of bytes to write
 * \return  Number of bytes written
 */
int
_write(int fd, const void *ptr, unsigned int len)
{
  if(fd == 1 || fd == 2) {
    /* stdout or stderr */
    const char *buf = (const char *)ptr;
    unsigned int i;

    for(i = 0; i < len; i++) {
      __io_putchar((int)buf[i]);
    }
    return len;
  }

  errno = EBADF;
  return -1;
}

/**
 * \brief   _read() - Read from file descriptor
 * \param   fd      File descriptor (0=stdin)
 * \param   ptr     Pointer to buffer
 * \param   len     Max bytes to read
 * \return  Number of bytes read, -1 on error
 */
int
_read(int fd, void *ptr, unsigned int len)
{
  if(fd == 0) {
    /* stdin */
    char *buf = (char *)ptr;
    unsigned int i;

    for(i = 0; i < len; i++) {
      buf[i] = (char)__io_getchar();
      if(buf[i] == '\r') {
        /* Echo newline */
        __io_putchar('\n');
        buf[i] = '\n';
        break;
      }
    }
    return i + 1;
  }

  errno = EBADF;
  return -1;
}

/**
 * \brief   _close() - Close file descriptor
 * \param   fd      File descriptor
 * \return  0 on success, -1 on error
 */
int
_close(int fd)
{
  if(fd >= 0 && fd <= 2) {
    return 0;
  }
  errno = EBADF;
  return -1;
}

/**
 * \brief   _fstat() - Get file status
 * \param   fd      File descriptor
 * \param   st      Pointer to stat structure
 * \return  0 on success, -1 on error
 */
int
_fstat(int fd, struct stat *st)
{
  if(fd >= 0 && fd <= 2) {
    st->st_mode = S_IFCHR;
    return 0;
  }
  errno = EBADF;
  return -1;
}

/**
 * \brief   _lseek() - Seek file position
 * \param   fd      File descriptor
 * \param   offset  Seek offset
 * \param   whence  Seek origin
 * \return  New file position, -1 on error
 */
int
_lseek(int fd, int offset, int whence)
{
  (void)fd;
  (void)offset;
  (void)whence;
  errno = ESPIPE;
  return -1;
}

/**
 * \brief   _isatty() - Check if fd is a terminal
 * \param   fd      File descriptor
 * \return  1 if terminal, 0 otherwise
 */
int
_isatty(int fd)
{
  if(fd >= 0 && fd <= 2) {
    return 1;
  }
  return 0;
}

/**
 * \brief   _open() - Open file
 * \param   path    File path
 * \param   flags   Open flags
 * \return  File descriptor, -1 on error
 */
int
_open(const char *path, int flags, ...)
{
  (void)path;
  (void)flags;
  errno = ENOENT;
  return -1;
}

/**
 * \brief   _getpid() - Get process ID
 * \return  Process ID (always 1)
 */
int
_getpid(void)
{
  return 1;
}

/**
 * \brief   _kill() - Terminate process
 * \param   pid     Process ID
 * \param   sig     Signal number
 * \return  -1 (always fails)
 */
int
_kill(int pid, int sig)
{
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

/**
 * \brief   _exit() - Exit the program
 * \param   status  Exit status code
 *
 * Halts execution - does not return.
 */
void
_exit(int status)
{
  (void)status;
  while(1) {
    /* Infinite loop - system halted */
  }
}
