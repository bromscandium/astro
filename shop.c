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

const char shop[5][30] = {{"##### #   #  ###  #### "},
                          {"#     #   # #   # #   #"},
                          {"##### ##### #   # #### "},
                          {"    # #   # #   # #    "},
                          {"##### #   #  ###  #    "}};

void shop(WINDOW *win, int settings) {
    wclear(win);
    box(win, 0, 0);

    wattron(win, COLOR_PAIR(2));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 29; j++) {
            mvwprintw(win, 2 + i, 19 + j, "%c", shop[i][j]);
        }
    }
    wattroff(win, COLOR_PAIR(2));

    char pricetextor[8][29] = {{"000"}, {"100"}, {"300"}, {"600"},
                               {"000"}, {"10"},  {"250"}, {"600"}};
    char pricetext[8][29] = {{"000"}, {"100"}, {"300"}, {"600"},
                             {"000"}, {"100"}, {"250"}, {"600"}};
    int price[8] = {0, 50, 100, 350, 0, 50, 100, 150};

    for (int i = 0; i < 4; i++) {
        if (settings[10] == i) {
            for (int k = 0; k < 3; k++) {
                pricetext[i][k] = '#';
            }
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (settings[11] == i) {
            for (int k = 0; k < 3; k++) {
                pricetext[i + 4][k] = '#';
            }
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, 11, 14 + (10 * i), "%s", pricetext[i]);
    }
    for (int i = 0; i < 4; i++) {
        mvwprintw(win, 16, 14 + (10 * i), "%s", pricetext[i + 4]);
    }

    mvwprintw(win, 8, 14, "== ");
    mvwprintw(win, 9, 14, "  >");
    mvwprintw(win, 10, 14, "== ");

    mvwprintw(win, 8, 24, "@@@");
    mvwprintw(win, 9, 24, "  @");
    mvwprintw(win, 10, 24, "@@@");

    mvwprintw(win, 8, 34, "X X");
    mvwprintw(win, 9, 34, " X ");
    mvwprintw(win, 10, 34, "X X");

    mvwprintw(win, 8, 44, "UAU");
    mvwprintw(win, 9, 44, "A A");
    mvwprintw(win, 10, 44, "UAU");

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
    int choosing = 0;
    while ((ch = wgetch(win)) != '+') {
        wattron(win, COLOR_PAIR(4));
        mvwprintw(win, 18, 1, "Gold: %04d", settings[0]);
        wattroff(win, COLOR_PAIR(4));
        wrefresh(win);
        mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                  "                                ");
        while (choosing < 0) {
            choosing++;
        }
        while (choosing > 8) {
            choosing--;
        }
        switch (ch) {
            case '\n': {
                if (choosing < 1) {
                    exit = 1;
                } else if (choosing < 5) {
                    if (settings[choosing + 1] == 1 || choosing == 1) {
                        for (int i = 0; i < 4; i++) {
                            if (settings[10] == i) {
                                for (int k = 0; k < 3; k++) {
                                    pricetext[i][k] = pricetextor[i][k];
                                }
                                settings[10] = choosing - 1;
                                for (int k = 0; k < 3; k++) {
                                    pricetext[choosing - 1][k] = '#';
                                }
                                mvwprintw(win, 11, 14 + (10 * (i)), "%s",
                                          pricetext[i]);
                                wattron(win, A_STANDOUT);
                                mvwprintw(win, 11, 14 + (10 * (choosing - 1)),
                                          "%s", pricetext[choosing - 1]);
                                wattroff(win, A_STANDOUT);
                                break;
                            }
                        }
                        break;
                    } else {
                        if (settings[0] >= price[choosing - 1]) {
                            settings[0] = settings[0] - price[choosing - 1];
                            settings[choosing + 1] = 1;
                            mvwprintw(win, 17, (WIDTH / 4) - 21 / 2,
                                      "Restart game to save!");
                        } else {
                            wattron(win, COLOR_PAIR(10));
                            mvwprintw(win, 17, (WIDTH / 4) - 14 / 2,
                                      "No enough gold");
                            wattroff(win, COLOR_PAIR(10));
                        }
                    }
                } else if (choosing > 4) {
                    if (settings[choosing] == 1 || choosing == 5) {
                        for (int i = 0; i < 4; i++) {
                            if (settings[11] == i) {
                                for (int k = 0; k < 3; k++) {
                                    pricetext[i + 4][k] = pricetextor[i + 4][k];
                                }
                                settings[11] = choosing - 5;
                                for (int k = 0; k < 3; k++) {
                                    pricetext[choosing - 1][k] = '#';
                                }
                                mvwprintw(win, 16, 14 + (10 * (i)), "%s",
                                          pricetext[i]);
                                wattron(win, A_STANDOUT);
                                mvwprintw(win, 16, 14 + (10 * (choosing - 5)),
                                          "%s", pricetext[choosing - 1]);
                                wattroff(win, A_STANDOUT);
                                break;
                            }
                        }
                        break;
                    } else {
                        if (settings[0] >= price[choosing - 1]) {
                            settings[0] = settings[0] - price[choosing - 1];
                            settings[choosing] = 1;
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
                if (choosing < 1) {
                    wattron(win, A_NORMAL);
                    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
                    wattroff(win, A_NORMAL);
                    choosing++;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 11, 14, "%s", pricetext[0]);
                    wattroff(win, A_STANDOUT);
                } else {
                    if (choosing < 4) {
                        wattron(win, A_NORMAL);
                        mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s",
                                  pricetext[choosing - 1]);
                        wattroff(win, A_NORMAL);
                        choosing++;
                        wattron(win, A_STANDOUT);
                        mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s",
                                  pricetext[choosing - 1]);
                        wattroff(win, A_STANDOUT);
                    } else if (choosing >= 4) {
                        if (choosing == 4) {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 11, 44, "%s", pricetext[3]);
                            wattroff(win, A_NORMAL);
                            choosing++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 16, 14, "%s", pricetext[4]);
                            wattroff(win, A_STANDOUT);
                        } else if (choosing < 8) {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s",
                                      pricetext[choosing - 1]);
                            wattroff(win, A_NORMAL);
                            choosing++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s",
                                      pricetext[choosing - 1]);
                            wattroff(win, A_STANDOUT);
                        }
                    }
                }
                break;
            }
            case KEY_LEFT: {
                if (choosing < 2) {
                    choosing--;
                    wattron(win, A_STANDOUT);
                    mvwprintw(win, 18, (WIDTH / 4) - 4 / 2, "Back");
                    wattroff(win, A_STANDOUT);
                    wattron(win, A_NORMAL);
                    mvwprintw(win, 11, 14, "%s", pricetext[0]);
                    wattroff(win, A_NORMAL);
                } else {
                    if (choosing < 5) {
                        wattron(win, A_NORMAL);
                        mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s",
                                  pricetext[choosing - 1]);
                        wattroff(win, A_NORMAL);
                        choosing--;
                        wattron(win, A_STANDOUT);
                        mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s",
                                  pricetext[choosing - 1]);
                        wattroff(win, A_STANDOUT);
                    } else if (choosing >= 5) {
                        if (choosing == 5) {
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 11, 44, "%s", pricetext[3]);
                            wattroff(win, A_STANDOUT);
                            choosing--;
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 16, 14, "%s", pricetext[4]);
                            wattroff(win, A_NORMAL);
                        } else {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s",
                                      pricetext[choosing - 1]);
                            wattroff(win, A_NORMAL);
                            choosing--;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s",
                                      pricetext[choosing - 1]);
                            wattroff(win, A_STANDOUT);
                        }
                    }
                }
                break;
            }
        }
        if (exit == 1) {
            refresh_menu(win, settings, i);
            exit = 0;
            break;
        }
    }
}