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

const char shopName[5][30] = {{"##### #   #  ###  #### "},
                              {"#     #   # #   # #   #"},
                              {"##### ##### #   # #### "},
                              {"    # #   # #   # #    "},
                              {"##### #   #  ###  #    "}};

void shop(WINDOW *win, int *settings) {
    wclear(win);
    box(win, 0, 0);

    int ch = 0;
    int itemSelected = 0;
    char pricetextoriginal[8][4] = {{"000"}, {"100"}, {"300"}, {"600"},
                                    {"000"}, {"10"},  {"250"}, {"600"}};
    char pricetext[8][4] = {{"000"}, {"100"}, {"300"}, {"600"},
                            {"000"}, {"100"}, {"250"}, {"600"}};
    int price[8] = {0, 100, 300, 600, 0, 50, 250, 600};

    wattron(win, COLOR_PAIR(2));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 29; j++) {
            mvwprintw(win, 2 + i, 19 + j, "%c", shopName[i][j]);
        }
    }
    wattroff(win, COLOR_PAIR(2));

    for (int i = 0; i < 4; i++) {
        if (settings[10] == i) {
            for (int k = 0; k < 3; k++) {
                pricetext[i + (settings[10])][k] = '#';
            }
        }
        if (settings[11] == i) {
            for (int k = 0; k < 3; k++) {
                pricetext[i + settings[11] + 4][k] = '#';
            }
        }

        mvwprintw(win, 11, 14 + (10 * i), "%s", pricetext[i]);
        mvwprintw(win, 16, 14 + (10 * i), "%s", pricetext[i + 4]);
    }

    const char *patterns[8] = {"== ", "@@@", "X X", "UAU",
                               "  >", "@",   " X ", "A A"};

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, 8, 14 + (10 * i), "%s", patterns[i]);
        mvwprintw(win, 9, 14 + (10 * i), "%s", patterns[i + 4]);
        mvwprintw(win, 10, 14 + (10 * i), "%s", patterns[i]);
    }

    mvwprintw(win, 13, 14, "COL");
    mvwprintw(win, 14, 14, "O O");
    mvwprintw(win, 15, 14, "COR");

    for (int i = 0; i < 3; i++) {
        wattron(win, COLOR_PAIR(i + 7));
        mvwprintw(win, 13, 24 + (10 * i), "COL");
        mvwprintw(win, 14, 24 + (10 * i), "O O");
        mvwprintw(win, 15, 24 + (10 * i), "COR");
        wattroff(win, COLOR_PAIR(i + 7));
    }

    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 18, 1, "Gold: %04d", settings[0]);
    wattroff(win, COLOR_PAIR(4));

    wattron(win, A_STANDOUT);
    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
    wattroff(win, A_STANDOUT);
    wrefresh(win);

    do {
        ch = wgetch(win);

        switch (ch) {
            case KEY_RIGHT: {
                if (itemSelected < 8) itemSelected++;
                break;
            }
            case KEY_LEFT: {
                if (itemSelected > 0) itemSelected--;
                break;
            }
            case '\n': {
                if (itemSelected == 0) {
                    return;
                } else if (itemSelected >= 1 && itemSelected <= 4) {
                    int index = itemSelected - 1;
                    if (settings[index] == 1) {
                        settings[10] = itemSelected;
                        mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                  "Restart game to save!");
                    } else if (settings[0] >= price[index]) {
                        settings[index] = 1;
                        settings[10] = itemSelected;
                        settings[0] -= price[index];
                        mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                  "Restart game to save!");
                    } else {
                        wattron(win, COLOR_PAIR(10));
                        mvwprintw(win, 17, (WIDTH / 4) - 14 / 2,
                                  "Not enough gold");
                        wattroff(win, COLOR_PAIR(10));
                    }
                } else if (itemSelected >= 5 && itemSelected <= 8) {
                    int index = itemSelected - 1;
                    if (settings[index] == 1) {
                        settings[11] = itemSelected;
                        mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                  "Restart game to save!");
                    } else if (settings[0] >= price[index]) {
                        settings[index] = 1;
                        settings[11] = itemSelected;
                        settings[0] -= price[index];
                        mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                  "Restart game to save!");
                    } else {
                        wattron(win, COLOR_PAIR(10));
                        mvwprintw(win, 17, (WIDTH / 4) - 14 / 2,
                                  "Not enough gold");
                        wattroff(win, COLOR_PAIR(10));
                    }
                }
            } break;
            default: {
                break;
            }
        }
        refresh_shop(win, itemSelected, pricetext);
        wrefresh(win);
    } while (1);
}

void refresh_shop(WINDOW *win, int selected, char pricetext[][4]) {
    int x_positions[] = {14, 24, 34, 44};
    int y_positions[] = {18, 11, 16};

    mvwprintw(win, y_positions[0], (WIDTH / 4) - 4 / 2, "    ");  // Back
    for (int i = 0; i < 4; i++) {
        mvwprintw(win, y_positions[1], x_positions[i], "%s", pricetext[i]);
        mvwprintw(win, y_positions[2], x_positions[i], "%s", pricetext[i + 4]);
    }

    if (selected == 0) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, y_positions[0], (WIDTH / 4) - 4 / 2, "Back");
        wattroff(win, A_STANDOUT);
    } else if (selected >= 1 && selected <= 4) {
        wattron(win, A_NORMAL);
        mvwprintw(win, y_positions[0], (WIDTH / 4) - 4 / 2, "Back");
        wattroff(win, A_NORMAL);
        wattron(win, A_STANDOUT);
        mvwprintw(win, y_positions[1], x_positions[selected - 1], "%s",
                  pricetext[selected - 1]);
        wattroff(win, A_STANDOUT);
    } else if (selected >= 5 && selected <= 8) {
        wattron(win, A_NORMAL);
        mvwprintw(win, y_positions[0], (WIDTH / 4) - 4 / 2, "Back");
        wattroff(win, A_NORMAL);
        wattron(win, A_STANDOUT);
        mvwprintw(win, y_positions[2], x_positions[selected - 5], "%s",
                  pricetext[selected - 1]);
        wattroff(win, A_STANDOUT);
    }

    wrefresh(win);
}