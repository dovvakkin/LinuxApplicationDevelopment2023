#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

WINDOW *TEXT_WIN;
int NLINES;
int NCOLS;
char LINE_FORMATTER[255];

int MINIMUM_VISIBLE_LINES = 1;

struct file_lines {
    int n_lines;
    char **lines;
};

void init_text_win() {
    int height = LINES - 3;
    int width = COLS - 4;
    int startx = 2;
    int starty = 2;

    NLINES = height - 2;
    NCOLS = width - 3;
    sprintf(LINE_FORMATTER, "%%.%ds", NCOLS);

    TEXT_WIN = newwin(height, width, starty, startx);
    box(TEXT_WIN, 0, 0);

    wrefresh(TEXT_WIN);
}

void print_lines_to_window(struct file_lines flines, int start_line, int start_char) {
    werase(TEXT_WIN);

    for (int offset = 0; (start_line + offset) < flines.n_lines && offset < NLINES; offset++) {
        char *line = flines.lines[start_line + offset];

        int line_len = strlen(line);
        line = line_len > start_char ? line + start_char : line + line_len;

        mvwprintw(TEXT_WIN, offset + 1, 1, LINE_FORMATTER, line);
    }
    box(TEXT_WIN, 0, 0);
    wrefresh(TEXT_WIN);
}

void init() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    refresh();
    init_text_win();
    keypad(TEXT_WIN, TRUE);
}

void print_usage() { printf("Usage: show FILE\n"); }

struct file_lines read_lines(const char *path) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("%s: cannot open file\n", path);
        exit(1);
    }

    struct file_lines fl;
    fl.n_lines = 0;
    int n_allocated = 10;
    fl.lines = (char **)malloc(n_allocated * sizeof(char **));

    while ((read = getline(&line, &len, fp)) != -1) {
        if (fl.n_lines == n_allocated) {
            n_allocated += 10;
            fl.lines = realloc(fl.lines, sizeof(char **) * n_allocated);
        }

        fl.lines[fl.n_lines] = (char *)malloc(sizeof(char) * len);
        memcpy(fl.lines[fl.n_lines], line, sizeof(char) * len);
        fl.n_lines++;
    }
    fclose(fp);

    return fl;
}

void delete_lines(struct file_lines flines) {
    for (int i = 0; i < flines.n_lines; i++) {
        free(flines.lines[i]);
    }
    free(flines.lines);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage();
        exit(1);
    }

    struct file_lines flines = read_lines(argv[1]);
    init();
    printw("File: %s, lines: %d", argv[1], flines.n_lines);
    refresh();

    int cur_line = 0;
    int cur_char = 0;
    bool finish = false;

    while (!finish) {
        print_lines_to_window(flines, cur_line, cur_char);

        int ch = wgetch(TEXT_WIN);
        switch (ch) {
        case 'q':
        case 27: // ESC
            finish = true;
            break;
        case KEY_UP:
        case 'k':
            if (cur_line > 0) {
                cur_line--;
            }
            break;
        case KEY_DOWN:
        case 'j':
        case ' ':
            if (cur_line + MINIMUM_VISIBLE_LINES < flines.n_lines) {
                cur_line++;
            }
            break;
        case KEY_LEFT:
        case 'h':
            if (cur_char > 0) {
                cur_char--;
            }
            break;
        case KEY_RIGHT:
        case 'l':
            cur_char++;
            break;
        }
    }

    endwin();
    delete_lines(flines);
    return 0;
}
