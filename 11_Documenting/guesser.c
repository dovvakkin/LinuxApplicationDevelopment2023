/** @mainpage Guesser Game
 * @copydetails guesser
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

#include "include/roman.h"

#define _(STRING) gettext(STRING)

const int GUESS_FROM = 1;
const int GUESS_TO = 3999;

char *number_to_str(const unsigned int number, const bool use_roman) {
    if (use_roman) {
        return to_roman(number);
    }

    int len;
    if (number > 0) {
        len = floor(log10(number) + 1);
    } else {
        len = 1;
    }
    char *str = malloc(len * sizeof(char));
    sprintf(str, "%d", number);

    return str;
}

void ask_to_pick_a_number(const unsigned int from, const unsigned int to, bool use_roman) {
    char *from_str = number_to_str(from, use_roman);
    char *to_str = number_to_str(to, use_roman);

    printf(_("Pick a number between %s and %s. I will try to guess it [press ENTER]"), from_str, to_str);
    getchar();

    free(from_str);
    free(to_str);
}

bool ask_if_greater(const unsigned int number, const bool use_roman) {
    char *number_str = number_to_str(number, use_roman);
    char input_buf[256];
    while (1) {
        printf(_("Is your number greater than %s ? y/n: "), number_str);
        scanf("%s", input_buf);

        if (strcmp(input_buf, _("y")) == 0) {
            free(number_str);
            return true;
        }
        if (strcmp(input_buf, _("n")) == 0) {
            free(number_str);
            return false;
        }
    }
    free(number_str);
}

int guess_number(const unsigned int from, const unsigned int to, const bool use_roman) {
    if (from == to) {
        return from;
    }

    const int middle = from + (to - from) / 2;

    const bool greater_middle = ask_if_greater(middle, use_roman);
    if (greater_middle) {
        return guess_number(middle + 1, to, use_roman);
    }
    return guess_number(from, middle, use_roman);
}

void print_guessed_number(const unsigned int number, const bool use_roman) {
    char *number_str = number_to_str(number, use_roman);
    printf(_("You picked number %s\n"), number_str);
    free(number_str);
}

void usage() {
    printf(_("Guesser will use binary search to guess your random number from given interval\n\n"
             "Usage: guesser [OPTION]\n\n"
             "Options:\n"
             "  -h, --help     display this help and exit\n"
             "  -r, --roman    use roman numbers instead of arabic\n"));
}

void version() {
    printf("guesser 1.0\n\nCopyright (C) 2023 dovvakkin\n");
}

typedef struct {
    bool use_roman;
} guesser_args;

guesser_args parse_args(int argc, char *argv[]) {
    guesser_args args;
    args.use_roman = false;
    if (argc > 2) {
        fprintf(stderr, "unknown arguments\n");
        usage();
        exit(1);
    }
    if (argc == 1) {
        return args;
    }
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        usage();
        exit(0);
    }
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        version();
        exit(0);
    }
    if (strcmp(argv[1], "--roman") == 0 || strcmp(argv[1], "-r") == 0) {
        args.use_roman = true;
    }

    return args;
}

/**
 * @page guesser
 * Guesser Game
 *
 * @section SYNOPSIS
 * `guesser` [-h|--help] [-r|--roman]
 *
 * @section DESCRIPTION
 * Program ask you to pick a random number in given interval.
 * Then it try to guess it with some kind of binary search.
 *
 * When run with [-r|--roman] argument use roman numbers instead of arabic.
 */

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(GETTEXT_DOMAIN, LOCALE_PATH);
    textdomain(GETTEXT_DOMAIN);

    const guesser_args args = parse_args(argc, argv);

    ask_to_pick_a_number(GUESS_FROM, GUESS_TO, args.use_roman);
    const int guessed_number = guess_number(GUESS_FROM, GUESS_TO, args.use_roman);
    print_guessed_number(guessed_number, args.use_roman);

    return 0;
}
