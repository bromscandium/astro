#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "menu.h"
#include "game.h"
#include "utils.h"

int main() {
    FILE *fp = fopen("parameters.txt", "r");
    if (fp == NULL) {
        printf("parameters.txt doesn't exist\nplease, create it\n");
        return EXIT_FAILURE;
    }

    int parameter[14] = {0};
    int sizeparameter = sizeof(parameter) / sizeof(int);
    struct timespec ts = {
        .tv_sec = 0,
        .tv_nsec = 1000000L
    };
    int yMax = 40, xMax = 121;

    for (int s = 0; s < sizeparameter; s++) {
        if (fscanf(fp, "%d", &parameter[s]) != 1) {
            break;
        }
    }
    fclose(fp);

    srand(time(NULL));
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    init_pair(9, MEGAYELLOW, COLOR_BLUE);
    init_pair(10, COLOR_RED, COLOR_BLACK);
    init_pair(11, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(12, COLOR_GREEN, COLOR_BLACK);
    init_pair(13, COLOR_CYAN, COLOR_BLACK);
    init_pair(14, MEGAYELLOW, COLOR_BLACK);
    init_pair(15, MEGARED, COLOR_BLACK);
    init_pair(16, MEGAWHITE, COLOR_BLACK);
    init_pair(17, MEGAGRAY, COLOR_BLACK);
    init_pair(18, MEGAORANGE, COLOR_BLACK);
    init_pair(19, MEGABLUE, COLOR_BLACK);
    init_pair(20, MEGAPINK, COLOR_BLACK);

    menu(parameter, xMax, yMax, sizeparameter, ts);

    endwin();
    fp = fopen("parameters.txt", "w");
    if (fp == NULL) {
        printf("parameters.txt doesn't exist\nplease, create it\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < sizeparameter; i++) {
        fprintf(fp, "%d ", parameter[i]);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}