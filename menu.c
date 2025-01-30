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

const char name[5][35] = {{"##### ##### ##### ####   ###"},
                          {"#   # #       #   #   # #   #"},
                          {"##### #####   #   ####  #   #"},
                          {"#   #     #   #   #   # #   #"},
                          {"#   # #####   #   #   #  ###"}};

const char buttons[4][7] = {"Play", "Levels", "Shop", "Exit"};

bool firstLaunch = true;

void menu(WINDOW *win, int settings[]) {
    refresh_menu(win, settings, 0);

    int ch = 0;
    int selectedButton = 8;
    int options = 0;
    keypad(win, TRUE);

    do {
        ch = wgetch(win);
        switch (ch) {
            case KEY_UP: {
                if (options > 0) {
                    mvwprintw(win, selectedButton,
                              (WIDTH / 4) - strlen(buttons[options]) / 2, "%s",
                              buttons[options]);
                    options--;
                    selectedButton -= 2;
                }
                break;
            }
            case KEY_DOWN: {
                if (options < 3) {
                    mvwprintw(win, selectedButton,
                              (WIDTH / 4) - strlen(buttons[options]) / 2, "%s",
                              buttons[options]);
                    options++;
                    selectedButton += 2;
                }
                break;
            }
            case '\n': {
                if (options == 0) {
                    game(win, settings);
                    refresh_menu(win, settings, 0);
                    break;
                } else if (options == 1) {
                    levels(win, settings);
                    refresh_menu(win, settings, 1);
                    break;
                } else if (options == 2) {
                    shop(win, settings);
                    refresh_menu(win, settings, 2);
                    break;
                } else if (options == 3) {
                    return;
                }
            }
            default: {
                break;
            }
        }
        wattron(win, A_STANDOUT);
        mvwprintw(win, selectedButton,
                  (WIDTH / 4) - strlen(buttons[options]) / 2, "%s",
                  buttons[options]);
        wattroff(win, A_STANDOUT);
    } while (1);
    endwin();
}

void refresh_menu(WINDOW *win, int settings[], int selected) {
    wclear(win);
    box(win, 0, 0);

    int seconds = settings[13] % 60;
    int minutes = (settings[13] / 60) % 60;
    int hours = ((settings[13] / 60) / 60) % 24;
    struct timespec fps = {.tv_nsec = 0};

    if (firstLaunch) {
        fps.tv_nsec = 10000000;
    }

    wattron(win, COLOR_PAIR(1));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 35; j++) {
            mvwprintw(win, 2 + i, 16 + j, "%c", name[i][j]);
            wrefresh(win);
            nanosleep(&fps, NULL);
        }
    }
    if (firstLaunch) firstLaunch = false;
    wattroff(win, COLOR_PAIR(1));

    for (int j = 0; j < 4; j++) {
        if (j == selected) {
            wattron(win, A_STANDOUT);
        }
        mvwprintw(win, 8 + (2 * j), (WIDTH / 4) - strlen(buttons[j]) / 2, "%s",
                  buttons[j]);
        if (j == selected) {
            wattroff(win, A_STANDOUT);
        }
    }

    wattron(win, COLOR_PAIR(17));
    mvwprintw(win, 18, 38, "Made by bromscandium");
    wattroff(win, COLOR_PAIR(17));
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 8, 10, "Best: %d", settings[1]);
    mvwprintw(win, 9, 10, "Destroys: %d", settings[12]);
    mvwprintw(win, 10, 10, "Time: %02d:%02d:%02d", hours, minutes, seconds);
    wattroff(win, COLOR_PAIR(3));

    wrefresh(win);
}