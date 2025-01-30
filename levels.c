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

const char level[5][40] = {{"#     ##### #   # ##### #     #####"},
                           {"#     #     #   # #     #     #    "},
                           {"#     ##### #   # ##### #     #####"},
                           {"#     #      # #  #     #         #"},
                           {"##### #####   #   ##### ##### #####"}};

void levels(WINDOW *win, int settings) {
    wclear(win);
    box(win, 0, 0);
    wattron(win, COLOR_PAIR(18));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 40; j++) {
            mvwprintw(win, 2 + i, 13 + j, "%c", level[i][j]);
        }
    }
    wattroff(win, COLOR_PAIR(18));

    char levels[5] = {'1', '2', '3', '4', '?'};

    for (int j = 0; j < 5; j++) {
        if (j > settings[9]) {
            wattron(win, COLOR_PAIR(10));
        }
        mvwprintw(win, 8, 13 + (j * 8), "###");
        mvwprintw(win, 9, 13 + (j * 8), "#%c#", levels[j]);
        mvwprintw(win, 10, 13 + (j * 8), "###");
        wattroff(win, COLOR_PAIR(10));
    }

    wattron(win, A_STANDOUT);
    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
    wattroff(win, A_STANDOUT);
    int choosing = 0;
    while ((ch = wgetch(win)) != '\n') {
        wrefresh(win);
        mvwprintw(win, 16, (WIDTH / 4) - 31 / 2,
                  "                                  ");
        while (choosing < 0) {
            choosing++;
        }
        if (choosing > 5) {
            choosing--;
        }
        switch (ch) {
            case '\n': {
                if (choosing < 1) {
                    exit = 1;
                } else if (choosing > 0) {
                    if (choosing - 1 > settings[9]) {
                        wattron(win, COLOR_PAIR(10));
                        mvwprintw(win, 16, (WIDTH / 4) - 31 / 2,
                                  "Please, complete previous level");
                        wattroff(win, COLOR_PAIR(10));
                        break;
                    }
                    settings[2] = choosing - 1;
                    game(win, settings);
                    exit = 1;
                }
                break;
            }
            case KEY_RIGHT: {
                if (choosing == 0) {
                    wattron(win, A_NORMAL);
                    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
                    wattroff(win, A_NORMAL);
                    choosing++;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                    mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#",
                              levels[choosing - 1]);
                    mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                    wattroff(win, A_STANDOUT);
                } else if (choosing < 5) {
                    wattron(win, A_NORMAL);
                    if (choosing - 1 > settings[9]) {
                        wattron(win, COLOR_PAIR(10));
                        wattroff(win, A_NORMAL);
                    }
                    mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                    mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#",
                              levels[choosing - 1]);
                    mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                    wattroff(win, COLOR_PAIR(10));
                    wattroff(win, A_NORMAL);
                    choosing++;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                    mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#",
                              levels[choosing - 1]);
                    mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                    wattroff(win, A_STANDOUT);
                }
                break;
            }
            case KEY_LEFT: {
                if (choosing <= 1 && choosing > 0) {
                    wattron(win, A_NORMAL);
                    mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                    mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#",
                              levels[choosing - 1]);
                    mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                    wattroff(win, A_NORMAL);
                    choosing--;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
                    wattroff(win, A_STANDOUT);
                } else if (choosing <= 5 && choosing > 0) {
                    wattron(win, A_NORMAL);
                    if (choosing - 1 > settings[9]) {
                        wattron(win, COLOR_PAIR(10));
                        wattroff(win, A_NORMAL);
                    }
                    mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                    mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#",
                              levels[choosing - 1]);
                    mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                    wattroff(win, COLOR_PAIR(10));
                    wattroff(win, A_NORMAL);
                    choosing--;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                    mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#",
                              levels[choosing - 1]);
                    mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                    wattroff(win, A_STANDOUT);
                }
                break;
            }
        }
    }
}