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

void game(WINDOW *win, int settings[]) {
    wclear(win);
    nodelay(stdscr, TRUE);
    srand(time(NULL));
    box(win, 0, 0);

    char skin[4][9] = {
        {"==   >== "}, {"@@@  @@@@"}, {"X X X X X"}, {"UAUA AUAU"}};
    int color;

    int time = 60;
    int life = 2;

    if (settings[2] == 4) {
        time = 9600;
    } else {
        time = 30 + (30 * settings[2]);
    }

    int seconds = time % 60;
    int minutes = (time / 60) % 60;
    int hours = ((time / 60) / 60) % 23;
    int destroys = 0;
    int golds = 0;
    int scores = 0;
    int playerpos[3] = {9, 10, 11};
    int playedtime = 0;

    int spawntime = rand() % 3 + 4;
    int spawnplace = 0;
    int spawnplacegold[17] = {0};
    int spawnplacegold2[17] = {0};

    int spawntime2 = rand() % 26 + 45;
    int spawnplace2 = 0;
    int spawnplacelife[17] = {0};
    int spawnplacelife2[17] = {0};

    // bullet
    int spawntime3 = 0;
    int spawnplacebullet[34] = {0};
    int spawnplacebullet2[34] = {0};

    // medium
    float spawntime4 = 1.0 + ((float)(rand() % 501) / 1000.0);
    int spawnplace4 = 0;
    int spawnplacecomet[14][14] = {{0}};
    int spawnplacecomet2[14][14] = {{0}};

    // fast
    float spawntime5 = 0.8 + ((float)(rand() % 11) / 10.0);
    int spawnplace5 = 0;
    int spawnplacefast[34] = {0};
    int spawnplacefast2[34] = {0};

    // big
    float spawntime6 = 1.5 + ((float)(rand() % 1001) / 1000.0);
    int spawnplace6 = 0;
    int spawnplacebig[21][21] = {{0}};
    int spawnplacebig2[21][21] = {{0}};

    for (int i = 0; i < 4; i++) {
        if (settings[11] == i) {
            color = settings[11] + 6;
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (settings[10] == i) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    wattron(win, COLOR_PAIR(color));
                    mvwprintw(win, playerpos[i - (1 * i)] + j, 1 + k, "%c",
                              skin[i][k + (3 * j)]);
                    wattroff(win, COLOR_PAIR(color));
                }
            }
            break;
        }
    }

    mvwprintw(win, 1, 51, "%02d:%02d:%02d", hours, minutes, seconds);
    mvwprintw(win, 2, 49, "Golds: %03d", golds);
    mvwprintw(win, 1, 1, "Scores: %d", scores);
    mvwprintw(win, 2, 1, "Destroys: %d", destroys);
    mvwprintw(win, 1, 27, "Lifes: %d", life);
    mvwprintw(win, 18, 10, "W - Up | S - Down | K - Fire | P - Pause");
    wrefresh(win);
    wattron(win, COLOR_PAIR(8));
    int g = 4;
    while (g > 0) {
        g--;
        mvwprintw(win, HEIGHT / 4 + 1, WIDTH / 4, "%d", g);
        wrefresh(win);
        second();
    }
    wattroff(win, COLOR_PAIR(8));
    mvwprintw(win, HEIGHT / 4 + 1, WIDTH / 4, " ");
    wrefresh(win);

    struct timespec ts = {.tv_msec = 0.001 * 10000000000L};
    int check = 100;
    keypad(win, TRUE);

    do {
        box(win, 0, 0);
        check--;
        if (check < 0) {
            check = 100;
            time--;
            playedtime++;
            spawntime--;
            spawntime2--;
            spawntime3--;
            spawntime4--;
            spawntime5--;
            spawntime6--;
            settings[13]++;
        }

        int seconds = time % 60;
        int minutes = (time / 60) % 60;
        int hours = ((time / 60) / 60) % 23;
        if (time < 16) {
            wattron(win, COLOR_PAIR(10));
        }
        mvwprintw(win, 1, 51, "%02d:%02d:%02d", hours, minutes, seconds);
        wattroff(win, COLOR_PAIR(10));
        mvwprintw(win, 2, 49, "Golds: %03d", golds);
        mvwprintw(win, 1, 1, "Scores: %d", scores);
        mvwprintw(win, 2, 1, "Destroys: %d", destroys);
        mvwprintw(win, 1, 27, "Lifes: %d", life);
        mvwprintw(win, 18, 10, "W - Up | S - Down | K - Fire | P - Pause");
        nanosleep(&ts, NULL);
        wrefresh(win);
        // gold
        if (spawntime < 1) {
            spawntime = rand() % 3 + 4;
            spawnplace = rand() % 13 + 4;
            for (int i = 0; i < 17; i++) {
                if (spawnplacegold[i] == 0) {
                    spawnplacegold2[i] = 58;
                    spawnplacegold[i] = spawnplace;
                    wattron(win, COLOR_PAIR(14));
                    mvwprintw(win, spawnplacegold[i], spawnplacegold2[i], "G");
                    wattroff(win, COLOR_PAIR(14));
                    wrefresh(win);
                    break;
                }
            }
        }

        if (check % 4 == 0) {
            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 58; j++) {
                    if (spawnplacegold[i] > 0) {
                        mvwprintw(win, spawnplacegold[i], spawnplacegold2[i],
                                  " ");
                        spawnplacegold2[i]--;
                        if (spawnplacegold2[i] < 1) {
                            wrefresh(win);
                            spawnplacegold[i] = 0;
                            spawnplacegold2[i] = 58;
                            break;
                        }
                        if (spawnplacegold2[i] < 4) {
                            if (spawnplacegold[i] == playerpos[0] ||
                                spawnplacegold[i] == playerpos[1] ||
                                spawnplacegold[i] == playerpos[2]) {
                                wrefresh(win);
                                golds = golds + 3;
                                scores = scores + 2;
                                spawnplacegold[i] = 0;
                                spawnplacegold2[i] = 58;
                                break;
                            }
                        }
                        wattron(win, COLOR_PAIR(14));
                        mvwprintw(win, spawnplacegold[i], spawnplacegold2[i],
                                  "G");
                        wattroff(win, COLOR_PAIR(14));
                        wrefresh(win);
                        break;
                    }
                }
            }
        }
        // life
        if (spawntime2 < 1) {
            spawntime2 = rand() % 26 + 45;
            spawnplace2 = rand() % 13 + 4;
            for (int i = 0; i < 17; i++) {
                if (spawnplacelife[i] == 0) {
                    spawnplacelife2[i] = 58;
                    spawnplacelife[i] = spawnplace2;
                    wattron(win, COLOR_PAIR(15));
                    mvwprintw(win, spawnplacelife[i], spawnplacelife2[i], "L");
                    wattroff(win, COLOR_PAIR(15));
                    wrefresh(win);
                    break;
                }
            }
        }
        if (check % 4 == 0) {
            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 58; j++) {
                    if (spawnplacelife[i] > 0) {
                        mvwprintw(win, spawnplacelife[i], spawnplacelife2[i],
                                  " ");
                        spawnplacelife2[i]--;
                        if (spawnplacelife2[i] < 1) {
                            wrefresh(win);
                            spawnplacelife[i] = 0;
                            spawnplacelife2[i] = 58;
                            break;
                        }
                        if (spawnplacelife2[i] < 4) {
                            if (spawnplacelife[i] == playerpos[0] ||
                                spawnplacelife[i] == playerpos[1] ||
                                spawnplacelife[i] == playerpos[2]) {
                                wrefresh(win);
                                life++;
                                scores = scores + 7;
                                spawnplacelife[i] = 0;
                                spawnplacelife2[i] = 58;
                                break;
                            }
                        }
                        wattron(win, COLOR_PAIR(15));
                        mvwprintw(win, spawnplacelife[i], spawnplacelife2[i],
                                  "L");
                        wattroff(win, COLOR_PAIR(15));
                        wrefresh(win);
                        break;
                    }
                }
            }
        }
        // bullet
        if (check % 2 == 0) {
            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 58; j++) {
                    if (spawnplacebullet[i] > 0) {
                        mvwprintw(win, spawnplacebullet[i],
                                  spawnplacebullet2[i], " ");
                        spawnplacebullet2[i]++;
                        if (spawnplacebullet2[i] > 34) {
                            spawnplacebullet[i] = 0;
                            spawnplacebullet2[i] = 0;
                            wrefresh(win);
                            break;
                        }
                        for (int k = 0; k < 34; k++) {
                            if (spawnplacebullet[i] == spawnplacefast[k] &&
                                spawnplacebullet2[i] > spawnplacefast2[k]) {
                                mvwprintw(win, spawnplacefast[k],
                                          spawnplacefast2[k], " ");
                                destroys++;
                                scores = scores + 15;
                                spawnplacebullet[i] = 0;
                                spawnplacebullet2[i] = 0;
                                spawnplacefast[k] = 0;
                                spawnplacefast2[k] = 0;
                                wrefresh(win);
                                break;
                            }
                        }
                        for (int k = 0; k < 21; k++) {
                            for (int h = 0; h < 3; h++) {
                                if (spawnplacebullet[i] ==
                                        spawnplacebig[h][k] &&
                                    spawnplacebullet2[i] >
                                        spawnplacebig2[h][k]) {
                                    for (int h = 0; h < 3; h++) {
                                        for (int g = 0; g < 3; g++) {
                                            mvwprintw(
                                                win, spawnplacebig[0 + h][k],
                                                spawnplacebig2[0 + g][k], " ");
                                        }
                                    }
                                    spawnplacebig[0][k] = 0;
                                    spawnplacebig2[0][k] = 0;
                                    spawnplacebullet[i] = 0;
                                    spawnplacebullet2[i] = 0;
                                    destroys++;
                                    golds = golds + 4;
                                    scores = scores + 5;
                                    wrefresh(win);
                                    break;
                                }
                            }
                        }
                        for (int k = 0; k < 14; k++) {
                            for (int h = 0; h < 3; h++) {
                                if (spawnplacebullet[i] ==
                                        spawnplacecomet[h][k] &&
                                    spawnplacebullet2[i] >
                                        spawnplacecomet2[h][k]) {
                                    for (int h = 0; h < 2; h++) {
                                        for (int g = 0; g < 2; g++) {
                                            mvwprintw(
                                                win, spawnplacecomet[0 + h][k],
                                                spawnplacecomet2[0 + g][k],
                                                " ");
                                        }
                                    }
                                    spawnplacecomet[0][k] = 0;
                                    spawnplacecomet2[0][k] = 0;
                                    spawnplacebullet[i] = 0;
                                    spawnplacebullet2[i] = 0;
                                    destroys++;
                                    golds = golds + 2;
                                    scores = scores + 10;
                                    wrefresh(win);
                                    break;
                                }
                            }
                        }
                        mvwprintw(win, spawnplacebullet[i],
                                  spawnplacebullet2[i], ">");
                        wrefresh(win);
                        break;
                    }
                }
            }
        }
        // comet
        if (settings[2] == 0 || settings[2] > 2) {
            if (spawntime4 < 1) {
                spawntime4 = 1.0 + ((float)(rand() % 501) / 1000.0);
                if (settings[2] == 3) {
                    spawntime4 = spawntime4 + 0.5;
                }
                spawnplace4 = rand() % 13 + 4;
                for (int i = 0; i < 14; i++) {
                    if (spawnplacecomet[0][i] == 0) {
                        spawnplacecomet2[0][i] = 58;
                        spawnplacecomet2[1][i] = 59;
                        spawnplacecomet[0][i] = spawnplace4;
                        spawnplacecomet[1][i] = spawnplace4 + 1;
                        wattron(win, COLOR_PAIR(19));
                        for (int j = 0; j < 2; j++) {
                            for (int k = 0; k < 2; k++) {
                                mvwprintw(win, spawnplacecomet[0 + j][i],
                                          spawnplacecomet2[0 + k][i], "#");
                            }
                        }
                        wattroff(win, COLOR_PAIR(19));
                        wrefresh(win);
                        break;
                    }
                }
            }
            if (check % 3 == 0) {
                for (int i = 0; i < 14; i++) {
                    if (spawnplacecomet[0][i] > 0) {
                        for (int h = 0; h < 2; h++) {
                            for (int k = 0; k < 2; k++) {
                                mvwprintw(win, spawnplacecomet[0 + h][i],
                                          spawnplacecomet2[0 + k][i], " ");
                                wrefresh(win);
                            }
                        }
                        spawnplacecomet2[0][i]--;
                        spawnplacecomet2[1][i]--;
                        if (spawnplacecomet2[1][i] < 1) {
                            spawnplacecomet2[0][i] = 0;
                            spawnplacecomet2[1][i] = 0;
                            spawnplacecomet[0][i] = 0;
                            spawnplacecomet[0][i] = 0;
                            wrefresh(win);
                            break;
                        }
                        if (spawnplacecomet2[0][i] < 4) {
                            for (int j = 0; j < 2; j++) {
                                if (spawnplacecomet[j][i] == playerpos[0] ||
                                    spawnplacecomet[j][i] == playerpos[1] ||
                                    spawnplacecomet[j][i] == playerpos[2]) {
                                    life--;
                                    mvwprintw(win, 1, 27, "Lifes: %d", life);
                                    spawnplacecomet2[0][i] = 0;
                                    spawnplacecomet2[1][i] = 0;
                                    spawnplacecomet[0][i] = 0;
                                    spawnplacecomet[0][i] = 0;
                                    wrefresh(win);
                                    break;
                                }
                            }
                        }
                        wattron(win, COLOR_PAIR(19));
                        for (int h = 0; h < 2; h++) {
                            for (int k = 0; k < 2; k++) {
                                mvwprintw(win, spawnplacecomet[0 + h][i],
                                          spawnplacecomet2[0 + k][i], "#");
                            }
                        }
                        wattroff(win, COLOR_PAIR(19));
                        wrefresh(win);
                    }
                }
            }
        }

        // fast comet
        if (settings[2] == 1 || settings[2] > 2) {
            if (spawntime5 < 1) {
                spawntime5 = 0.8 + ((float)(rand() % 11) / 10.0);
                if (settings[2] == 3) {
                    spawntime4 = spawntime4 + 0.3;
                }
                spawnplace5 = rand() % 15 + 3;
                for (int i = 0; i < 17; i++) {
                    if (spawnplacefast[i] == 0) {
                        spawnplacefast2[i] = 58;
                        spawnplacefast[i] = spawnplace5;
                        wattron(win, COLOR_PAIR(20));
                        mvwprintw(win, spawnplacefast[i], spawnplacefast2[i],
                                  "#");
                        wattroff(win, COLOR_PAIR(20));
                        wrefresh(win);
                        break;
                    }
                }
            }
            if (check % 2 == 0) {
                for (int i = 0; i < 17; i++) {
                    for (int j = 0; j < 58; j++) {
                        if (spawnplacefast[i] > 0) {
                            mvwprintw(win, spawnplacefast[i],
                                      spawnplacefast2[i], " ");
                            spawnplacefast2[i]--;
                            if (spawnplacefast2[i] < 1) {
                                wrefresh(win);
                                spawnplacefast[i] = 0;
                                spawnplacefast2[i] = 58;
                                break;
                            }
                            if (spawnplacefast2[i] < 4) {
                                if (spawnplacefast[i] == playerpos[0] ||
                                    spawnplacefast[i] == playerpos[1] ||
                                    spawnplacefast[i] == playerpos[2]) {
                                    life--;
                                    mvwprintw(win, 1, 27, "Lifes: %d", life);
                                    spawnplacefast[i] = 0;
                                    spawnplacefast2[i] = 58;
                                    wrefresh(win);
                                    break;
                                }
                            }
                            wattron(win, COLOR_PAIR(20));
                            mvwprintw(win, spawnplacefast[i],
                                      spawnplacefast2[i], "#");
                            wattroff(win, COLOR_PAIR(20));
                            wrefresh(win);
                            break;
                        }
                    }
                }
            }
        }
        // big comet
        if (settings[2] >= 2) {
            if (spawntime6 < 1) {
                spawntime6 = 1.5 + ((float)(rand() % 501) / 2000.0);
                if (settings[2] == 3) {
                    spawntime4 = spawntime4 + 0.4;
                }
                spawnplace6 = rand() % 11 + 5;

                for (int i = 0; i < 21; i++) {
                    if (spawnplacebig[0][i] == 0) {
                        spawnplacebig2[0][i] = 58;
                        spawnplacebig2[1][i] = 59;
                        spawnplacebig2[2][i] = 60;
                        spawnplacebig[0][i] = spawnplace6;
                        spawnplacebig[1][i] = spawnplace6 + 1;
                        spawnplacebig[2][i] = spawnplace6 + 2;
                        wattron(win, COLOR_PAIR(16));
                        for (int j = 0; j < 3; j++) {
                            for (int k = 0; k < 3; k++) {
                                mvwprintw(win, spawnplacebig[0 + j][i],
                                          spawnplacebig2[0 + k][i], "#");
                            }
                        }
                        wattroff(win, COLOR_PAIR(16));
                        wrefresh(win);
                        break;
                    }
                }
            }
            if (check % 6 == 0) {
                for (int i = 0; i < 21; i++) {
                    if (spawnplacebig[0][i] > 0) {
                        for (int h = 0; h < 3; h++) {
                            for (int k = 0; k < 3; k++) {
                                mvwprintw(win, spawnplacebig[0 + h][i],
                                          spawnplacebig2[0 + k][i], " ");
                                wrefresh(win);
                            }
                        }
                        spawnplacebig2[0][i]--;
                        spawnplacebig2[1][i]--;
                        spawnplacebig2[2][i]--;
                        if (spawnplacebig2[2][i] < 1) {
                            spawnplacebig2[0][i] = 0;
                            spawnplacebig2[1][i] = 0;
                            spawnplacebig2[2][i] = 0;
                            spawnplacebig[0][i] = 0;
                            spawnplacebig[1][i] = 0;
                            spawnplacebig[2][i] = 0;
                            wrefresh(win);
                            break;
                        }
                        if (spawnplacebig2[0][i] < 4) {
                            for (int j = 0; j < 3; j++) {
                                if (spawnplacebig[j][i] == playerpos[0] ||
                                    spawnplacebig[j][i] == playerpos[1] ||
                                    spawnplacebig[j][i] == playerpos[2]) {
                                    life--;
                                    mvwprintw(win, 1, 27, "Lifes: %d", life);
                                    spawnplacebig2[0][i] = 0;
                                    spawnplacebig2[1][i] = 0;
                                    spawnplacebig2[2][i] = 0;
                                    spawnplacebig[0][i] = 0;
                                    spawnplacebig[1][i] = 0;
                                    spawnplacebig[2][i] = 0;
                                    wrefresh(win);
                                    break;
                                }
                            }
                        }
                        wattron(win, COLOR_PAIR(16));
                        for (int h = 0; h < 3; h++) {
                            for (int k = 0; k < 3; k++) {
                                mvwprintw(win, spawnplacebig[0 + h][i],
                                          spawnplacebig2[0 + k][i], "#");
                            }
                        }
                        wattroff(win, COLOR_PAIR(16));
                        wrefresh(win);
                    }
                }
            }
        }
        // player
        for (int i = 0; i < 4; i++) {
            if (settings[11] == i) {
                color = settings[11] + 6;
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (settings[10] == i) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        wattron(win, COLOR_PAIR(color));
                        mvwprintw(win, playerpos[i - (1 * i)] + j, 1 + k, "%c",
                                  skin[i][k + (3 * j)]);
                        wattroff(win, COLOR_PAIR(color));
                    }
                }
                break;
            }
        }

        // inputs
        int ch = tolower(getch());
        switch (ch) {
            case 'k': {
                if (spawntime3 < 1) {
                    for (int i = 0; i < 34; i++) {
                        if (spawnplacebullet[i] == 0) {
                            spawnplacebullet2[i] = 4;
                            spawnplacebullet[i] = playerpos[1];
                            spawntime3 = 1;
                            mvwprintw(win, spawnplacebullet[i],
                                      spawnplacebullet2[i], ">");
                            wrefresh(win);
                            break;
                        }
                    }
                }
                break;
            }
            case 'w': {
                if (playerpos[1] > 4 && playerpos[1] < 17) {
                    movement(ch, playerpos);
                    mvwprintw(win, playerpos[0] + 3, 1, "\t");
                    mvwprintw(win, playerpos[1] + 3, 1, "\t");
                    mvwprintw(win, playerpos[2] + 3, 1, "\t");
                    break;
                }
                break;
            }
            case 's': {
                if (playerpos[1] > 3 && playerpos[1] < 16) {
                    mvwprintw(win, playerpos[0], 1, "\t");
                    mvwprintw(win, playerpos[1], 1, "\t");
                    mvwprintw(win, playerpos[2], 1, "\t");
                    movement(ch, playerpos);
                    break;
                }
                break;
            }
            case 'p': {
                wattron(win, A_BLINK);
                mvwprintw(win, 18, 6, "                                                ");
                mvwprintw(win, 18, 6, "P - Continue | Q - Quit [You lose your progress]");
                wrefresh(win);
                do {
                    ch = tolower(wgetch(win));
                    switch (ch) {
                        case 'q': {
                            life = 0;
                            break;
                        }
                        case 'p': {
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                } while (ch != 'q' && ch != 'p');
				mvwprintw(win, 18, 6, "                                                ");
                wattroff(win, A_BLINK);
                break;
            }
            default: {
                break;
            }
        }
    } while (time > 0 && life > 0);
    results(win, settings, golds, destroys, playedtime, life, time, scores);
    wgetch(win);
}

void results(WINDOW *win, int *settings, int golds, int destroys,
    int playedtime, int life, int time, int scores) {
    second();
    keypad(win, FALSE);
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
	second();

    if (life < 1) {
        char loser[5][35] = {{"#      ###  ##### #####"},
                             {"#     #   # #     #    "},
                             {"#     #   # ##### #####"},
                             {"#     #   #     # #    "},
                             {"#####  ###  ##### #####"}};
        wattron(win, COLOR_PAIR(10));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 35; j++) {
                mvwprintw(win, 2 + i, 19 + j, "%c", loser[i][j]);
            }
        }
        wattroff(win, COLOR_PAIR(10));
    } else if (time < 1) {
        char winner[5][35] = {{"# # #  ###  #   #"},
                              {"# # #   #   ##  #"},
                              {"# # #   #   # # #"},
                              {"# # #   #   #  ##"},
                              {" # #   ###  #   #"}};
        wattron(win, COLOR_PAIR(13));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 35; j++) {
                mvwprintw(win, 2 + i, 21 + j, "%c", winner[i][j]);
            }
        }
        wattroff(win, COLOR_PAIR(13));

        if (settings[9] < 4 && settings[2] == settings[9]) {
            settings[9]++;
        }
        settings[2]++;
    }
    wrefresh(win);
    settings[0] = settings[0] + golds;
    settings[12] = settings[12] + destroys;
    wattron(win, COLOR_PAIR(1));
    second();
    mvwprintw(win, 8, (WIDTH / 4) - 5, "Scores: %04d", scores);
    wrefresh(win);
    second();
    mvwprintw(win, 9, (WIDTH / 4) - 6, "Destroys: %03d", destroys);
    wrefresh(win);
    second();
    mvwprintw(win, 10, (WIDTH / 4) - 4, "Golds: %03d", golds);
    wrefresh(win);
    second();
    mvwprintw(win, 11, (WIDTH / 4) - 10, "Time played: %02d:%02d:%02d",
              ((playedtime / 60) / 60) % 23, (playedtime / 60) % 60,
              playedtime % 60);
    wrefresh(win);
    wattroff(win, COLOR_PAIR(1));

    if (scores > settings[1]) {
        second();
        wattron(win, COLOR_PAIR(2));
        mvwprintw(win, 8, (WIDTH / 4) + 3, "%04d", scores);
        mvwprintw(win, 13, 22, "New best score!");
        wattroff(win, COLOR_PAIR(2));
        wrefresh(win);
        settings[1] = scores;
    }

    second();
    wattron(win, A_STANDOUT);
    mvwprintw(win, 18, (WIDTH / 4) - 12, "Press ENTER to go to menu");
    wattroff(win, A_STANDOUT);

    keypad(win, TRUE);
}

void movement(char ch, int playerpos[]) {
    ch = tolower(ch);
    int delta = (ch == 'w') ? -1 : (ch == 's') ? 1 : 0;

    if (delta != 0) {
        for (int i = 0; i < 3; i++) {
            playerpos[i] += delta;
        }
    }
}

void second() {
    nanosleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
}