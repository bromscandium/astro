#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "menu.h"
#include "main.h"

int main() {
    FILE *file = NULL;
    initialize_settings(&file);
    if(file == NULL) {
       return EXIT_FAILURE;
    }

    int settings[14] = {0};

    for (int i = 0; i < 14 && fscanf(file, "%d", &settings[i]) == 1; i++);
    fclose(file);

    typedef struct {
        short front_color;
        short back_color;
    } ColorPair;

    ColorPair color_pairs[] = {
        {COLOR_BLUE, COLOR_BLACK},
        {COLOR_YELLOW, COLOR_BLACK},
        {COLOR_BLACK, COLOR_BLUE},
        {COLOR_BLACK, COLOR_YELLOW},
        {COLOR_BLACK, COLOR_RED},
        {COLOR_WHITE, COLOR_BLACK},
        {COLOR_YELLOW, COLOR_BLACK},
        {COLOR_BLACK, COLOR_WHITE},
        {MEGAYELLOW, COLOR_BLUE},
        {COLOR_RED, COLOR_BLACK},
        {COLOR_MAGENTA, COLOR_BLACK},
        {COLOR_GREEN, COLOR_BLACK},
        {COLOR_CYAN, COLOR_BLACK},
        {MEGAYELLOW, COLOR_BLACK},
        {MEGARED, COLOR_BLACK},
        {MEGAWHITE, COLOR_BLACK},
        {MEGAGRAY, COLOR_BLACK},
        {MEGAORANGE, COLOR_BLACK},
        {MEGABLUE, COLOR_BLACK},
        {MEGAPINK, COLOR_BLACK}
    };

    srand(time(NULL));
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    int num_pairs = sizeof(color_pairs) / sizeof(color_pairs[0]);
    for (int i = 0; i < num_pairs; i++) {
        init_pair(i + 1, color_pairs[i].front_color, color_pairs[i].back_color);
    }

    menu(settings);

    endwin();

    initialize_settings(&file);
    for (int i = 0; i < 14; i++) fprintf(file, "%d ", settings[i]);
    fclose(file);

    return EXIT_SUCCESS;
}

void initialize_settings(FILE **file) {
    *file = fopen("settings.txt", "r+");
    if (*file == NULL) {
        *file = fopen("settings.txt", "w");
        if (*file == NULL) {
            printf("Can't create a settings file\n");
            return;
        }

        for (int i = 0; i < 14; i++) {
            fprintf(*file, "0");
            if (i < 13) fprintf(*file, " ");
        }
        fclose(*file);
        return;
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(*file)) != EOF) {
        if (ch == ' ') {
            count++;
        }
    }

    if (count < 13) {
        fseek(*file, 0, SEEK_END);
        for (int i = 0; i < 13 - count; i++) {
            fprintf(*file, " 0");
        }
    }

    fclose(*file);
}