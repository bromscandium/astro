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

    wattron(win, COLOR_PAIR(2));
    for (int i = 0; i < 5; i++) {
        mvwprintw(win, 2 + i, 19, "%s", shopName[i]);
    }
    wattroff(win, COLOR_PAIR(2));

    char pricetextor[8][29] = {{"000"}, {"100"}, {"300"}, {"600"},
                               {"000"}, {"10"},  {"250"}, {"600"}};
    char pricetext[8][29] = {{"000"}, {"100"}, {"300"}, {"600"},
                             {"000"}, {"100"}, {"250"}, {"600"}};
    int price[8] = {0, 50, 100, 350, 0, 50, 100, 150};

    for (int i = 0; i < 4; i++) {
        if (settings[10] == i || settings[11] == i) {
            for (int k = 0; k < 3; k++) {
                pricetext[i + (settings[10] == i ? 0 : 4)][k] = '#';
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

    mvwprintw(win, 13, 24 + (10), "COL");
    mvwprintw(win, 14, 24 + (10), "O O");
    mvwprintw(win, 15, 24 + (10), "COR");

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
        wattron(win, COLOR_PAIR(4));
        mvwprintw(win, 18, 1, "Gold: %04d", settings[0]);
        wattroff(win, COLOR_PAIR(4));
        wrefresh(win);
        mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                  "                                ");
        while (itemSelected < 0) {
            itemSelected++;
        }
        while (itemSelected > 8) {
            itemSelected--;
        }
        switch (ch) {
            case '\n': {
                if (itemSelected == 0) {
                    break;
                } else if (itemSelected < 5) {
                    if (settings[itemSelected + 1] == 1 || itemSelected == 1) {
                        for (int i = 0; i < 4; i++) {
                            if (settings[10] == i) {
                                for (int k = 0; k < 3; k++) {
                                    pricetext[i][k] = pricetextor[i][k];
                                }
                                settings[10] = itemSelected - 1;
                                for (int k = 0; k < 3; k++) {
                                    pricetext[itemSelected - 1][k] = '#';
                                }
                                mvwprintw(win, 11, 14 + (10 * (i)), "%s",
                                          pricetext[i]);
                                wattron(win, A_STANDOUT);
                                mvwprintw(win, 11, 14 + (10 * (itemSelected - 1)),
                                          "%s", pricetext[itemSelected - 1]);
                                wattroff(win, A_STANDOUT);
                                break;
                            }
                        }
                        break;
                    } else {
                        if (settings[0] >= price[itemSelected - 1]) {
                            settings[0] = settings[0] - price[itemSelected - 1];
                            settings[itemSelected + 1] = 1;
                            mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                      "Restart game to save!");
                        } else {
                            wattron(win, COLOR_PAIR(10));
                            mvwprintw(win, 17, (WIDTH / 4) - 14 / 2,
                                      "No enough gold");
                            wattroff(win, COLOR_PAIR(10));
                        }
                    }
                } else if (itemSelected > 4) {
                    if (settings[itemSelected] == 1 || itemSelected == 5) {
                        for (int i = 0; i < 4; i++) {
                            if (settings[11] == i) {
                                for (int k = 0; k < 3; k++) {
                                    pricetext[i + 4][k] = pricetextor[i + 4][k];
                                }
                                settings[11] = itemSelected - 5;
                                for (int k = 0; k < 3; k++) {
                                    pricetext[itemSelected - 1][k] = '#';
                                }
                                mvwprintw(win, 16, 14 + (10 * (i)), "%s",
                                          pricetext[i]);
                                wattron(win, A_STANDOUT);
                                mvwprintw(win, 16, 14 + (10 * (itemSelected - 5)),
                                          "%s", pricetext[itemSelected - 1]);
                                wattroff(win, A_STANDOUT);
                                break;
                            }
                        }
                        break;
                    } else {
                        if (settings[0] >= price[itemSelected - 1]) {
                            settings[0] = settings[0] - price[itemSelected - 1];
                            settings[itemSelected] = 1;
                            mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                      "Restart game to save!");
                        } else {
                            wattron(win, COLOR_PAIR(10));
                            mvwprintw(win, 17, (WIDTH / 4) - 14 / 2,
                                      "No enough gold");
                            wattroff(win, COLOR_PAIR(10));
                        }
                    }
                }
                break;
            }
            case KEY_RIGHT: {
                if (itemSelected < 1) {
                    wattron(win, A_NORMAL);
                    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
                    wattroff(win, A_NORMAL);
                    itemSelected++;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 11, 14, "%s", pricetext[0]);
                    wattroff(win, A_STANDOUT);
                } else {
                    if (itemSelected < 4) {
                        wattron(win, A_NORMAL);
                        mvwprintw(win, 11, 14 + (10 * (itemSelected - 1)), "%s",
                                  pricetext[itemSelected - 1]);
                        wattroff(win, A_NORMAL);
                        itemSelected++;
                        wattron(win, A_STANDOUT);
                        mvwprintw(win, 11, 14 + (10 * (itemSelected - 1)), "%s",
                                  pricetext[itemSelected - 1]);
                        wattroff(win, A_STANDOUT);
                    } else if (itemSelected >= 4) {
                        if (itemSelected == 4) {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 11, 44, "%s", pricetext[3]);
                            wattroff(win, A_NORMAL);
                            itemSelected++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 16, 14, "%s", pricetext[4]);
                            wattroff(win, A_STANDOUT);
                        } else if (itemSelected < 8) {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 16, 14 + (10 * (itemSelected - 5)), "%s",
                                      pricetext[itemSelected - 1]);
                            wattroff(win, A_NORMAL);
                            itemSelected++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 16, 14 + (10 * (itemSelected - 5)), "%s",
                                      pricetext[itemSelected - 1]);
                            wattroff(win, A_STANDOUT);
                        }
                    }
                }
                break;
            }
            case KEY_LEFT: {
                if (itemSelected < 2) {
                    itemSelected--;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
                    wattroff(win, A_STANDOUT);
                    wattron(win, A_NORMAL);
                    mvwprintw(win, 11, 14, "%s", pricetext[0]);
                    wattroff(win, A_NORMAL);
                } else {
                    if (itemSelected < 5) {
                        wattron(win, A_NORMAL);
                        mvwprintw(win, 11, 14 + (10 * (itemSelected - 1)), "%s",
                                  pricetext[itemSelected - 1]);
                        wattroff(win, A_NORMAL);
                        itemSelected--;
                        wattron(win, A_STANDOUT);
                        mvwprintw(win, 11, 14 + (10 * (itemSelected - 1)), "%s",
                                  pricetext[itemSelected - 1]);
                        wattroff(win, A_STANDOUT);
                    } else if (itemSelected >= 5) {
                        if (itemSelected == 5) {
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 11, 44, "%s", pricetext[3]);
                            wattroff(win, A_STANDOUT);
                            itemSelected--;
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 16, 14, "%s", pricetext[4]);
                            wattroff(win, A_NORMAL);
                        } else {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 16, 14 + (10 * (itemSelected - 5)), "%s",
                                      pricetext[itemSelected - 1]);
                            wattroff(win, A_NORMAL);
                            itemSelected--;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 16, 14 + (10 * (itemSelected - 5)), "%s",
                                      pricetext[itemSelected - 1]);
                            wattroff(win, A_STANDOUT);
                        }
                    }
                }
                break;
            }
        }
    } while (itemSelected == 0 && (ch = wgetch(win)) == '\n');
}