/** @file strbuf.c
 * @brief Small string join library
 *
 * Provide dynamicly allocated string buffer and join functions for strings and substrings
 */

#include "strbuf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int REALLOC_STEP = 3;

/**
 * @brief Create dynamicly allocated string buffer
 * @return strbuf, expected to be deleted
 */
strbuf *create_strbuf() {
    strbuf *buf = malloc(sizeof(strbuf));
    buf->data = malloc(sizeof(char) * REALLOC_STEP);
    buf->data[0] = '\0';
    buf->len = 0;
    buf->allocated = buf->realloc_step = REALLOC_STEP;

    return buf;
}

/**
 * @brief Delete dynamicly allocated string buffer
 * @param buf strbuf to delete
 */
void delete_strbuf(strbuf *buf) {
    free(buf->data);
    free(buf);
}

/**
 * @brief Reallocate buffer data to fit given length
 *
 * @param buf buffer to reallocate its data
 * @param len_to_fit len, reallocated buffer will have same or greated number of elements +1 for null terminator
 */
void strbuf_maybe_realloc_to_fit(strbuf *buf, const int len_to_fit) {
    const int new_old_size_diff = len_to_fit - buf->allocated + 1; // for null terminator
    if (new_old_size_diff > 0) {
        const int realloc_step = buf->realloc_step > new_old_size_diff ? buf->realloc_step : new_old_size_diff;
        const int new_buf_allocated = buf->allocated + realloc_step;
        buf->data = realloc(buf->data, new_buf_allocated);
        buf->allocated = new_buf_allocated;
    }
}

/**
 * @brief Append string (char*) to buffer
 *
 * @param buf buffer to append to
 * @param str string to append to buffer
 */
void strbuf_append(strbuf *buf, const char *str) {
    const int str_len = strlen(str);

    strbuf_maybe_realloc_to_fit(buf, buf->len + str_len);
    strcat(buf->data, str);
    buf->len += str_len;
}

/**
 * @brief Append substring from string (char*) to buffer
 *
 * @param buf buffer to append to
 * @param str string to get substring from
 * @param from start index
 * @param to end index
 */
void strbuf_append_substr(strbuf *buf, const char *str, const int from, const int to) {
    const int substr_len = to - from;

    strbuf_maybe_realloc_to_fit(buf, buf->len + substr_len);
    memcpy(buf->data + buf->len, str + from, substr_len);
    buf->len += substr_len;
    buf->data[buf->len] = '\0';
}
