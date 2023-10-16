#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int stop;
    int step;
    int _current;
} range;

void usage() {
    fprintf(stderr, "Prints range based on argumens, one number on line\n");
    fprintf(stderr, "\t1 arg N: [0, 1, … N-1] if N > 0 or [] otherwise\n");
    fprintf(stderr, "\t2 args M, N: [M, M+1, … N-1] if M < N or [] otherwise\n");
    fprintf(stderr, "\t3 args M, N, S: [M, M+S, M+2S, … N-1] if N-M and S same sign or [] otherwise\n");
}

void argparse(int argc, char *argv[], int *range_start, int *range_stop, int *range_step) {
    if (argc < 2 || argc > 4) {
        usage();
        exit(1);
    }

    switch (argc) {
    case 2:
        *range_start = 0;
        *range_stop = atoi(argv[1]);
        *range_step = 1;
        break;
    case 3:
        *range_start = atoi(argv[1]);
        *range_stop = atoi(argv[2]);
        *range_step = 1;
        break;
    case 4:
        *range_start = atoi(argv[1]);
        *range_stop = atoi(argv[2]);
        *range_step = atoi(argv[3]);
        break;
    }
}

void range_init(range *i) {
    i->_current = i->start;
}

bool range_run(range *i) {
    if (i->step > 0) {
        return i->_current < i->stop;
    }

    return i->_current > i->stop;
}

void range_next(range *i) {
    i->_current += i->step;
}

int range_get(range *i) {
    return i->_current;
}

int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);

    for (range_init(&I); range_run(&I); range_next(&I)) {
        printf("%d\n", range_get(&I));
    }
    return 0;
}
