#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdlib.h>
#include <time.h>

typedef struct {
    char *data;
    int size;
    int wall_length;
} lbrnt;

lbrnt make_empty_lbrnt(int size) {
    lbrnt l;
    l.size = size;
    l.wall_length = size * 2 + 1;
    l.data = (char *)malloc(sizeof(char) * l.wall_length * l.wall_length);

    for (int i = 0; i < l.wall_length; i++) {
        for (int j = 0; j < l.wall_length; j++) {
            const int current_idx = i * l.wall_length + j;
            if (i == 0 || i == l.wall_length - 1 || j == 0 || j == l.wall_length - 1) {
                l.data[current_idx] = '#';
                continue;
            }
            if ((i + 1) % 2 == 0 || (j + 1) % 2 == 0) {
                l.data[current_idx] = '.';
                continue;
            }
            l.data[current_idx] = '#';
        }
    }

    return l;
}

void print_lbrnt(const lbrnt l) {
    for (int i = 0; i < l.wall_length; i++) {
        for (int j = 0; j < l.wall_length; j++) {
            printf("%c", l.data[i * l.wall_length + j]);
        }
        printf("\n");
    }
}

// labirint with one wall still labitint
void put_random_wall(lbrnt l) {
    const bool vertical_wall = rand() % 2;

    const int i = (1 + (rand() % (l.size - 1))) * 2 - 1;
    const int j = (1 + (rand() % (l.size - 1))) * 2;
    if (vertical_wall) {
        l.data[i * l.wall_length + j] = '#';
        return;
    }
    l.data[j * l.wall_length + i] = '#';
}

int main() {
    lbrnt l = make_empty_lbrnt(6);

    srand(time(NULL));
    put_random_wall(l);

    print_lbrnt(l);
    return 0;
}
