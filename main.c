#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "menu.h"
#include "main.h"

int main() {
    int settings[14] = {0};
    load_settings(settings);
    if(load_settings(settings) != 0) {
       printf("Can't set settings\n");
       return EXIT_FAILURE;
    }

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

    initscr();
    start_color();
    int num_pairs = sizeof(color_pairs) / sizeof(color_pairs[0]);
    for (int i = 0; i < num_pairs; i++) {
        init_pair(i + 1, color_pairs[i].front_color, color_pairs[i].back_color);
    }

    srand(time(NULL));
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    menu(settings);

    endwin();
    save_settings(settings);
    return EXIT_SUCCESS;
}

int load_settings(int *settings) {
    FILE *file = fopen("settings.txt", "r+");
    if (file == NULL) {
        return -1;
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            count++;
        }
    }

    if (count < 12) {
        fseek(file, 0, SEEK_END);
        for (int i = count; i < 14; i++) {
            fprintf(file, "0");
            if (i < 13) fprintf(file, " ");
        }
    }

    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < 14; i++){
        if (fscanf(file, "%d", &settings[i]) != 1) {
            fclose(file);
            return -1;
        }
    };
    fclose(file);
    return 0;
}

int save_settings(int *settings) {
    FILE *file = fopen("settings.txt", "r+");
    if (file == NULL) {
        return -1;
    }
    for (int i = 0; i < 14; i++){
        if (fprintf(file, "%d", settings[i]) != 1) {
            fclose(file);
            return -1;
        }
        if (i < 13) fprintf(file, " ");
    }
    fclose(file);
    return 0;
}