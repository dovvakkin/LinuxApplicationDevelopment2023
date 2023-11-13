#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

const int GUESS_FROM = 0;
const int GUESS_TO = 100;

void ask_to_pick_a_number(const int from, const int to) {
    printf(_("Pick a number between %d and %d. I will try to guess it [press ENTER]"), from, to);
    getchar();
}

bool ask_if_greater(const int number) {
    char input_buf[256];
    while (1) {
        printf(_("Is your number greater than %d ? y/n: "), number);
        scanf("%s", input_buf);

        if (strcmp(input_buf, _("y")) == 0) {
            return true;
        }
        if (strcmp(input_buf, _("n")) == 0) {
            return false;
        }
    }
}

int guess_number(const int from, const int to) {
    if (from == to) {
        return from;
    }

    const int middle = from + (to - from) / 2;

    const bool greater_middle = ask_if_greater(middle);
    if (greater_middle) {
        return guess_number(middle + 1, to);
    }
    return guess_number(from, middle);
}

void print_guessed_number(const int number) {
    printf(_("You picked number %d\n"), number);
}

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain(GETTEXT_DOMAIN, LOCALE_PATH);
    textdomain(GETTEXT_DOMAIN);

    ask_to_pick_a_number(GUESS_FROM, GUESS_TO);
    const int guessed_number = guess_number(GUESS_FROM, GUESS_TO);
    print_guessed_number(guessed_number);
    return 0;
}
