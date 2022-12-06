#ifndef _MSAFE_EPRINTF_H
#define _MSAFE_EPRINTF_H

#include <errno.h>      /* errno */
#include <stdarg.h>     /* va_list */
#include <stdbool.h>    /* bool */
#include <stddef.h>     /* ssize_t */
#include <stdint.h>     /* intmax_t */
#include <stdio.h>      /* stderr */
#include <stdlib.h>     /* abort() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* STDIN_FILENO */

#define _MM_MAX_STDERR_MSG 256

ssize_t io_msafe_dprintf(int fileno, const char *fmt, ...)
        __attribute__((format(printf, 2, 3)));
ssize_t io_msafe_eprintf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
ssize_t io_msafe_vdprintf(int fileno, const char *fmt, va_list argp)
        __attribute__((format(printf, 2, 0)));
ssize_t io_msafe_writen(int fd, const void *usrbuf, size_t n);

/**
 * @brief Debug variant of io_msafe_dprintf. Runs only when 
 * DEBUG is defined.
*/
#ifdef DEBUG
#define io_msafe_eprintf_dbg(...) ((void)io_msafe_eprintf(__VA_ARGS__))
#else
#define io_msafe_eprintf_dbg(...) ((void)sizeof(__VA_ARGS__))
#endif

#define io_msafe_assert(expr)                                                       \
    ((expr) ? (void)0 : __io_msafe_assert_fail(#expr, __FILE__, __LINE__, __func__))

void __io_msafe_assert_fail(const char *assertion, const char *file,
                       unsigned int line, const char *function)
     __attribute__((noreturn));

#endif /* _MSAFE_EPRINTF_H */
