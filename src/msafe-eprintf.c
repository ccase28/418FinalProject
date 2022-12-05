/**
 * @file msafe-eprintf.c
 * A malloc-safe and async-signal-safe version of various printf functions
 * @author csapp
*/

#include "msafe-eprintf.h"

extern char *__progname;

/* io_msafe_reverse - Reverse a string (from K&R) */
static void io_msafe_reverse(char s[], size_t len) {
    size_t i, j;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* write_digits - write digit values of v in base b to string */
static size_t write_digits(uintmax_t v, char s[], unsigned char b) {
    size_t i = 0;
    do {
        unsigned char c = v % b;
        if (c < 10) {
            s[i++] = (char)(c + '0');
        } else {
            s[i++] = (char)(c - 10 + 'a');
        }
    } while ((v /= b) > 0);
    return i;
}

/* Based on K&R itoa() */
/* intmax_to_string - Convert an intmax_t to a base b string */
static size_t intmax_to_string(intmax_t v, char s[], unsigned char b) {
    bool neg = v < 0;
    size_t len;

    if (neg) {
        len = write_digits((uintmax_t)-v, s, b);
        s[len++] = '-';
    } else {
        len = write_digits((uintmax_t)v, s, b);
    }

    s[len] = '\0';
    io_msafe_reverse(s, len);
    return len;
}

/* uintmax_to_string - Convert a uintmax_t to a base b string */
static size_t uintmax_to_string(uintmax_t v, char s[], unsigned char b) {
    size_t len = write_digits(v, s, b);
    s[len] = '\0';
    io_msafe_reverse(s, len);
    return len;
}

/**
 * @brief   Prints formatted output to a file descriptor.
 * @param fileno   The file descriptor to print output to.
 * @param fmt      The format string used to determine the output.
 * @param ...      The arguments for the format string.
 * @return         The number of bytes written, or -1 on error.
 *
 * @remark   This function is async-signal-safe.
 * @see      io_msafe_vdprintf
 */
ssize_t io_msafe_dprintf(int fileno, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    ssize_t ret = io_msafe_vdprintf(fileno, fmt, argp);
    va_end(argp);
    return ret;
}

/**
 * @brief   Prints formatted output to STDERR_FILENO.
 * @param fmt      The format string used to determine the output.
 * @param ...      The arguments for the format string.
 * @return         The number of bytes written, or -1 on error.
 *
 * @remark   This function is async-signal-safe.
 * @see      io_msafe_vdprintf
 */
ssize_t io_msafe_eprintf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    ssize_t ret = io_msafe_vdprintf(STDERR_FILENO, fmt, argp);
    va_end(argp);
    return ret;
}

struct _format_data {
    const char *str; // String to output
    size_t len;      // Length of string to output
    char buf[128];   // Backing buffer to use for conversions
};

static size_t _handle_format(const char *fmt, va_list argp,
                             struct _format_data *data) {
    size_t pos = 0;
    bool handled = false;

    if (fmt[0] == '%') {
        // Marked if we need to convert an integer
        char convert_type = '\0';
        union {
            uintmax_t u;
            intmax_t s;
        } convert_value = {.u = 0};

        switch (fmt[1]) {

        // Character format
        case 'c': {
            data->buf[0] = (char)va_arg(argp, int);
            data->buf[1] = '\0';
            data->str = data->buf;
            data->len = 1;
            handled = true;
            pos += 2;
            break;
        }

        // String format
        case 's': {
            data->str = va_arg(argp, char *);
            if (data->str == NULL) {
                data->str = "(null)";
            }
            data->len = strlen(data->str);
            handled = true;
            pos += 2;
            break;
        }

        // Escaped %
        case '%': {
            data->str = fmt;
            data->len = 1;
            handled = true;
            pos += 2;
            break;
        }

        // Pointer type
        case 'p': {
            void *ptr = va_arg(argp, void *);
            if (ptr == NULL) {
                data->str = "(nil)";
                data->len = strlen(data->str);
                handled = true;
            } else {
                convert_type = 'p';
                convert_value.u = (uintmax_t)(uintptr_t)ptr;
            }
            pos += 2;
            break;
        }

        // Int types with no format specifier
        case 'd':
        case 'i':
            convert_type = 'd';
            convert_value.s = (intmax_t)va_arg(argp, int);
            pos += 2;
            break;
        case 'u':
        case 'x':
        case 'o':
            convert_type = fmt[1];
            convert_value.u = (uintmax_t)va_arg(argp, unsigned);
            pos += 2;
            break;

        // Int types with size format: long
        case 'l': {
            switch (fmt[2]) {
            case 'd':
            case 'i':
                convert_type = 'd';
                convert_value.s = (intmax_t)va_arg(argp, long);
                pos += 3;
                break;
            case 'u':
            case 'x':
            case 'o':
                convert_type = fmt[2];
                convert_value.u = (uintmax_t)va_arg(argp, unsigned long);
                pos += 3;
                break;
            }
            break;
        }

        // Int types with size format: size_t
        case 'z': {
            switch (fmt[2]) {
            case 'd':
            case 'i':
                convert_type = 'd';
                convert_value.s = (intmax_t)(uintmax_t)va_arg(argp, size_t);
                pos += 3;
                break;
            case 'u':
            case 'x':
            case 'o':
                convert_type = fmt[2];
                convert_value.u = (uintmax_t)va_arg(argp, size_t);
                pos += 3;
                break;
            }
            break;
        }
        }

        // Convert int type to string
        switch (convert_type) {
        case 'd':
            data->str = data->buf;
            data->len = intmax_to_string(convert_value.s, data->buf, 10);
            handled = true;
            break;
        case 'u':
            data->str = data->buf;
            data->len = uintmax_to_string(convert_value.u, data->buf, 10);
            handled = true;
            break;
        case 'x':
            data->str = data->buf;
            data->len = uintmax_to_string(convert_value.u, data->buf, 16);
            handled = true;
            break;
        case 'o':
            data->str = data->buf;
            data->len = uintmax_to_string(convert_value.u, data->buf, 8);
            handled = true;
            break;
        case 'p':
            strcpy(data->buf, "0x");
            data->str = data->buf;
            data->len =
                uintmax_to_string(convert_value.u, data->buf + 2, 16) + 2;
            handled = true;
            break;
        }
    }

    // Didn't match a format above
    // Handle block of non-format characters
    if (!handled) {
        data->str = fmt;
        data->len = 1 + strcspn(fmt + 1, "%");
        pos += data->len;
    }

    return pos;
}

/**
 * @brief   Prints formatted output to a file descriptor from a va_list.
 * @param fileno   The file descriptor to print output to.
 * @param fmt      The format string used to determine the output.
 * @param argp     The arguments for the format string.
 * @return         The number of bytes written, or -1 on error.
 *
 * @remark   This function is async-signal-safe.
 *
 * This is a reentrant and async-signal-safe implementation of vdprintf, used
 * to implement the associated formatted sio functions.
 *
 * However, since these writes are unbuffered, this is not very efficient, and
 * should only be used when async-signal-safety is necessary.
 *
 * The only supported format specifiers are the following:
 *  -  Int types: %d, %i, %u, %x, %o (with size specifiers l, z)
 *  -  Others: %c, %s, %%, %p
 */
ssize_t io_msafe_vdprintf(int fileno, const char *fmt, va_list argp) {
    size_t pos = 0;
    ssize_t num_written = 0;

    while (fmt[pos] != '\0') {
        // Int to string conversion
        struct _format_data data;
        memset(&data, 0, sizeof(data));

        // Handle format characters
        pos += _handle_format(&fmt[pos], argp, &data);

        // Write output
        if (data.len > 0) {
            ssize_t ret = io_msafe_writen(fileno, (const void *)data.str, data.len);
            if (ret < 0 || (size_t)ret != data.len) {
                return -1;
            }
            num_written += data.len;
        }
    }

    return num_written;
}

/* Async-signal-safe assertion support*/
void __io_msafe_assert_fail(const char *assertion, const char *file,
                       unsigned int line, const char *function) {
    io_msafe_dprintf(STDERR_FILENO, "%s: %s:%u: %s: Assertion `%s' failed.\n",
                __progname, file, line, function, assertion);
    abort();
}


/*
 * io_msafe_writen - Robustly write n bytes (unbuffered)
 */
ssize_t io_msafe_writen(int fd, const void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    const char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno != EINTR) {
                return -1; /* errno set by write() */
            }

            /* Interrupted by sig handler return, call write() again */
            nwritten = 0;
        }
        nleft -= (size_t)nwritten;
        bufp += nwritten;
    }
    return (ssize_t)n;
}
