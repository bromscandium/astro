#include <ctype.h>
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "levels.h"
#include "main.h"
#include "menu.h"
#include "shop.h"

const char levelName[5][40] = {{"#     ##### #   # ##### #     #####"},
                               {"#     #     #   # #     #     #    "},
                               {"#     ##### #   # ##### #     #####"},
                               {"#     #      # #  #     #         #"},
                               {"##### #####   #   ##### ##### #####"}};

void levels(WINDOW *win, int settings[]) {
    wclear(win);
    box(win, 0, 0);

    int ch = 0;
    int levelSelected = 0;

    wattron(win, COLOR_PAIR(18));
    for (int i = 0; i < 5; i++) {
        mvwprintw(win, 2 + i, 13, "%s", levelName[i]);
    }
    wattroff(win, COLOR_PAIR(18));
    refresh_level(win, settings, levelSelected);

    do {
        ch = wgetch(win);
        switch (ch) {
            case KEY_RIGHT: {
                if (levelSelected < 5) levelSelected++;
                break;
            }
            case KEY_LEFT: {
                if (levelSelected > 0) levelSelected--;
                break;
            }
            case '\n':
                if (levelSelected == 0) {
                    return;
                } else if (levelSelected > 0 &&
                           levelSelected - 1 <= settings[9]) {
                    settings[2] = levelSelected - 1;
                    save_settings(settings);
                    game(win, settings);
                } else {
                    wattron(win, COLOR_PAIR(10));
                    mvwprintw(win, 16, (WIDTH / 4) - 31 / 2,
                              "Please, complete previous level");
                    wattroff(win, COLOR_PAIR(10));
                    wrefresh(win);
                }
                break;
            default: {
                break;
            }
        }
        refresh_level(win, settings, levelSelected);
        wrefresh(win);
    } while (1);
}

void refresh_level(WINDOW *win, int *settings, int selected) {
    for (int j = 0; j < 5; j++) {
        if (j > settings[9]) {
            wattron(win, COLOR_PAIR(10));
        }

        mvwprintw(win, 8, 13 + (j * 8), "###");
        mvwprintw(win, 9, 13 + (j * 8), "#%d#", j + 1);
        mvwprintw(win, 10, 13 + (j * 8), "###");

        wattroff(win, COLOR_PAIR(10));
    }
    if (selected == 0) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
        wattron(win, A_STANDOUT);
        mvwprintw(win, 8, 13 + ((selected - 1) * 8), "###");
        mvwprintw(win, 9, 13 + ((selected - 1) * 8), "#%d#", selected);
        mvwprintw(win, 10, 13 + ((selected - 1) * 8), "###");
        wattroff(win, A_STANDOUT);
    }
}