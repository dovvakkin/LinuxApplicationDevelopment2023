/** @file roman.c
 * @brief Convert numbers to roman
 */

#include "strbuf.h"
#include <stdlib.h>

/**
 * @brief Convert @p number to roman system
 *
 * @param n number to convert
 * @return roman string representation, expected to be deleted
 *
 * @p n should be in range 1..3999, 0 converts as 0
 */
char *to_roman(unsigned int n) {
    strbuf *roman = create_strbuf();

    if (n == 0) {
        strbuf_append(roman, "0");
    }

    while (n >= 1000) {
        strbuf_append(roman, "M");
        n -= 1000;
    }
    while (n >= 900) {
        strbuf_append(roman, "CM");
        n -= 900;
    }
    while (n >= 500) {
        strbuf_append(roman, "D");
        n -= 500;
    }
    while (n >= 100) {
        strbuf_append(roman, "C");
        n -= 100;
    }
    while (n >= 90) {
        strbuf_append(roman, "XC");
        n -= 90;
    }
    while (n >= 50) {
        strbuf_append(roman, "L");
        n -= 50;
    }
    while (n >= 40) {
        strbuf_append(roman, "XL");
        n -= 40;
    }
    while (n >= 10) {
        strbuf_append(roman, "X");
        n -= 10;
    }
    while (n >= 9) {
        strbuf_append(roman, "IX");
        n -= 9;
    }
    while (n >= 5) {
        strbuf_append(roman, "V");
        n -= 5;
    }
    while (n >= 4) {
        strbuf_append(roman, "IV");
        n -= 4;
    }
    while (n >= 1) {
        strbuf_append(roman, "I");
        n -= 1;
    }

    char *roman_str = roman->data;
    free(roman);

    return roman_str;
}
