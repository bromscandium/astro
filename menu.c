#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "game.h"

const char name[5][35] = {
    {"##### ##### ##### ####   ###"},
    {"#   # #       #   #   # #   #"},
    {"##### #####   #   ####  #   #"},
    {"#   #     #   #   #   # #   #"},
    {"#   # #####   #   #   #  ###"}};

const char namelevel[5][40] = {
    {"#     ##### #   # ##### #     #####"},
    {"#     #     #   # #     #     #    "},
    {"#     ##### #   # ##### #     #####"},
    {"#     #      # #  #     #         #"},
    {"##### #####   #   ##### ##### #####"}};

const char nameshop[5][30] = {
    {"##### #   #  ###  #### "},
    {"#     #   # #   # #   #"},
    {"##### ##### #   # #### "},
    {"    # #   # #   # #    "},
    {"##### #   #  ###  #    "}};

const char buttons[5][7] = {"Play", "Levels", "Shop", "Exit"};

void menu(int parameter[], const int xMax, const int yMax, int sizeparameter, struct timespec ts){
    int seconds = parameter[13] % 60;
    int minutes = (parameter[13] / 60) % 60;
    int hours = ((parameter[13] / 60) / 60) % 24;
    WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);

    box(win, 0, 0);
    wrefresh(win);

    wattron(win, COLOR_PAIR(1));
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            mvwprintw(win, 2 + i, 16 + j, "%c", name[i][j]);
            wrefresh(win);
            nanosleep(&ts, NULL);
        }
    }
    wattroff(win, COLOR_PAIR(1));

    wattron(win, A_STANDOUT);
    nanosleep(&ts, NULL);
    mvwprintw(win, 8, (xMax / 4) - 4 / 2, "Play");
    wattroff(win, A_STANDOUT);
    nanosleep(&ts, NULL);
    mvwprintw(win, 10, (xMax / 4) - 6 / 2, "Levels");
    nanosleep(&ts, NULL);
    mvwprintw(win, 12, (xMax / 4) - 4 / 2, "Shop");
    nanosleep(&ts, NULL);
    mvwprintw(win, 14, (xMax / 4) - 4 / 2, "Exit");
    wattron(win, COLOR_PAIR(17));
    mvwprintw(win, 18, 38, "Made by bromscandium");
    wattroff(win, COLOR_PAIR(17));
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 8, 10, "Best: %d", parameter[1]);
    mvwprintw(win, 9, 10, "Destroys: %d", parameter[12]);
    mvwprintw(win, 10, 10, "Time: %02d:%02d:%02d", hours, minutes, seconds);
    wattroff(win, COLOR_PAIR(3));

    int ch;
    int button = 8;
    int i = 0;
    keypad(win, TRUE);
    do
    {
        int exit = 0;
        switch (ch)
        {
        case KEY_UP:
        {
            if (button >= 10)
            {
                wattron(win, A_NORMAL);
                mvwprintw(win, button, (xMax / 4) - strlen(buttons[i]) / 2, "%s", buttons[i]);
                wattroff(win, A_NORMAL);
                i--;
                button = button - 2;
                wattron(win, A_STANDOUT);
                mvwprintw(win, button, (xMax / 4) - strlen(buttons[i]) / 2, "%s", buttons[i]);
                wattroff(win, A_STANDOUT);
            }
            break;
        }
        case KEY_DOWN:
        {
            if (button <= 12)
            {
                wattron(win, A_NORMAL);
                mvwprintw(win, button, (xMax / 4) - strlen(buttons[i]) / 2, "%s", buttons[i]);
                i++;
                wattroff(win, A_NORMAL);
                button = button + 2;
                wattron(win, A_STANDOUT);
                mvwprintw(win, button, (xMax / 4) - strlen(buttons[i]) / 2, "%s", buttons[i]);
                wattroff(win, A_STANDOUT);
            }
            break;
        }
        case '\n':
        {
            if (i == 0)
            {
                FILE *fp = fopen("parameters.txt", "w");

                if (fp == NULL)
                {
                    printf("parameters.txt doesn't exist\nplease, create it\n");
                    return;
                }

                for (int i = 0; i < sizeparameter; i++)
                {
                    fprintf(fp, "%d ", parameter[i]);
                }

                fclose(fp);
                keypad(win, FALSE);
                game(parameter, xMax, yMax, sizeparameter);
                keypad(win, TRUE);

                break;
            }
            else if (i == 1)
            {
                wclear(win);
                box(win, 0, 0);
                // exit

                wattron(win, COLOR_PAIR(18));
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 40; j++)
                    {
                        mvwprintw(win, 2 + i, 13 + j, "%c", namelevel[i][j]);
                    }
                }
                wattroff(win, COLOR_PAIR(18));

                char levels[5] = {'1', '2', '3', '4', '?'};

                for (int j = 0; j < 5; j++)
                {
                    if (j > parameter[9])
                    {
                        wattron(win, COLOR_PAIR(10));
                    }
                    mvwprintw(win, 8, 13 + (j * 8), "###");
                    mvwprintw(win, 9, 13 + (j * 8), "#%c#", levels[j]);
                    mvwprintw(win, 10, 13 + (j * 8), "###");
                    wattroff(win, COLOR_PAIR(10));
                }

                wattron(win, A_STANDOUT);
                mvwprintw(win, 18, (xMax / 4) - 4 / 2, "Back");
                wattroff(win, A_STANDOUT);
                int choosing = 0;
                while ((ch = wgetch(win)) != '+')
                {
                    wrefresh(win);
                    mvwprintw(win, 16, (xMax / 4) - 31 / 2, "                                  ");
                    while (choosing < 0)
                    {
                        choosing++;
                    }
                    if (choosing > 5)
                    {
                        choosing--;
                    }

                    switch (ch)
                    {
                    case '\n':
                    {
                        if (choosing < 1)
                        {
                            exit = 1;
                        }
                        else if (choosing > 0)
                        {
                            if (choosing - 1 > parameter[9])
                            {
                                wattron(win, COLOR_PAIR(10));
                                mvwprintw(win, 16, (xMax / 4) - 31 / 2, "Please, complete previous level");
                                wattroff(win, COLOR_PAIR(10));
                                break;
                            }
                            parameter[2] = choosing - 1;
                            FILE *fp = fopen("parameters.txt", "w");

                            if (fp == NULL)
                            {
                                printf("parameters.txt doesn't exist\nplease, create it\n");
                                return;
                            }

                            for (int i = 0; i < sizeparameter; i++)
                            {
                                fprintf(fp, "%d ", parameter[i]);
                            }

                            fclose(fp);
                            game(parameter, xMax, yMax, sizeparameter);
                            exit = 1;
                        }
                        break;
                    }
                    case KEY_RIGHT:
                    {
                        if (choosing == 0)
                        {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 18, (xMax / 4) - 4 / 2, "Back");
                            wattroff(win, A_NORMAL);
                            choosing++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                            mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#", levels[choosing - 1]);
                            mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                            wattroff(win, A_STANDOUT);
                        }
                        else if (choosing < 5)
                        {
                            wattron(win, A_NORMAL);
                            if (choosing - 1 > parameter[9])
                            {
                                wattron(win, COLOR_PAIR(10));
                                wattroff(win, A_NORMAL);
                            }
                            mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                            mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#", levels[choosing - 1]);
                            mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                            wattroff(win, COLOR_PAIR(10));
                            wattroff(win, A_NORMAL);
                            choosing++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                            mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#", levels[choosing - 1]);
                            mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                            wattroff(win, A_STANDOUT);
                        }
                        break;
                    }
                    case KEY_LEFT:
                    {
                        if (choosing <= 1 && choosing > 0)
                        {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                            mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#", levels[choosing - 1]);
                            mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                            wattroff(win, A_NORMAL);
                            choosing--;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 18, (xMax / 4) - 4 / 2, "Back");
                            wattroff(win, A_STANDOUT);
                        }
                        else if (choosing <= 5 && choosing > 0)
                        {
                            wattron(win, A_NORMAL);
                            if (choosing - 1 > parameter[9])
                            {
                                wattron(win, COLOR_PAIR(10));
                                wattroff(win, A_NORMAL);
                            }
                            mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                            mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#", levels[choosing - 1]);
                            mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                            wattroff(win, COLOR_PAIR(10));
                            wattroff(win, A_NORMAL);
                            choosing--;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 8, 13 + ((choosing - 1) * 8), "###");
                            mvwprintw(win, 9, 13 + ((choosing - 1) * 8), "#%c#", levels[choosing - 1]);
                            mvwprintw(win, 10, 13 + ((choosing - 1) * 8), "###");
                            wattroff(win, A_STANDOUT);
                        }
                        break;
                    }
                    }
                    if (exit == 1)
                    {
                        refresh_menu(name, parameter, xMax, yMax, i);
                        exit = 0;
                        break;
                    }
                }
                break;
            }
            else if (i == 2)
            {

                wclear(win);
                box(win, 0, 0);

                wattron(win, COLOR_PAIR(2));
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 29; j++)
                    {
                        mvwprintw(win, 2 + i, 19 + j, "%c", nameshop[i][j]);
                    }
                }
                wattroff(win, COLOR_PAIR(2));

                char pricetextor[8][29] = {{"000"}, {"100"}, {"300"}, {"600"}, {"000"}, {"10"}, {"250"}, {"600"}};
                char pricetext[8][29] = {{"000"}, {"100"}, {"300"}, {"600"}, {"000"}, {"100"}, {"250"}, {"600"}};
                int price[8] = {0, 50, 100, 350, 0, 50, 100, 150};

                for (int i = 0; i < 4; i++)
                {
                    if (parameter[10] == i)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            pricetext[i][k] = '#';
                        }
                        break;
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    if (parameter[11] == i)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            pricetext[i + 4][k] = '#';
                        }
                        break;
                    }
                }

                for (int i = 0; i < 4; i++)
                {
                    mvwprintw(win, 11, 14 + (10 * i), "%s", pricetext[i]);
                }
                for (int i = 0; i < 4; i++)
                {
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

                for (int i = 0; i < 3; i++)
                {
                    wattron(win, COLOR_PAIR(i + 7));
                    mvwprintw(win, 13, 24 + (10 * i), "COL");
                    mvwprintw(win, 14, 24 + (10 * i), "O O");
                    mvwprintw(win, 15, 24 + (10 * i), "COR");
                    wattroff(win, COLOR_PAIR(i + 7));
                }

                wattron(win, COLOR_PAIR(4));
                mvwprintw(win, 18, 1, "Gold: %04d", parameter[0]);
                wattroff(win, COLOR_PAIR(4));

                wattron(win, A_STANDOUT);
                mvwprintw(win, 18, (xMax / 4) - 4 / 2, "Back");
                wattroff(win, A_STANDOUT);
                wrefresh(win);
                int choosing = 0;
                while ((ch = wgetch(win)) != '+')
                {
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, 18, 1, "Gold: %04d", parameter[0]);
                    wattroff(win, COLOR_PAIR(4));
                    wrefresh(win);
                    mvwprintw(win, 17, (xMax / 4) - 21 / 2, "                                ");
                    while (choosing < 0)
                    {
                        choosing++;
                    }
                    while (choosing > 8)
                    {
                        choosing--;
                    }
                    switch (ch)
                    {
                    case '\n':
                    {
                        if (choosing < 1)
                        {
                            exit = 1;
                        }
                        else if (choosing < 5)
                        {
                            if (parameter[choosing + 1] == 1 || choosing == 1)
                            {
                                for (int i = 0; i < 4; i++)
                                {
                                    if (parameter[10] == i)
                                    {
                                        for (int k = 0; k < 3; k++)
                                        {
                                            pricetext[i][k] = pricetextor[i][k];
                                        }
                                        parameter[10] = choosing - 1;
                                        for (int k = 0; k < 3; k++)
                                        {
                                            pricetext[choosing - 1][k] = '#';
                                        }
                                        mvwprintw(win, 11, 14 + (10 * (i)), "%s", pricetext[i]);
                                        wattron(win, A_STANDOUT);
                                        mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s", pricetext[choosing - 1]);
                                        wattroff(win, A_STANDOUT);
                                        break;
                                    }
                                }
                                break;
                            }
                            else
                            {
                                if (parameter[0] >= price[choosing - 1])
                                {
                                    parameter[0] = parameter[0] - price[choosing - 1];
                                    parameter[choosing + 1] = 1;
                                    mvwprintw(win, 17, (xMax / 4) - 21 / 2, "Restart game to save!");
                                }
                                else
                                {
                                    wattron(win, COLOR_PAIR(10));
                                    mvwprintw(win, 17, (xMax / 4) - 14 / 2, "No enough gold");
                                    wattroff(win, COLOR_PAIR(10));
                                }
                            }
                        }
                        else if (choosing > 4)
                        {
                            if (parameter[choosing] == 1 || choosing == 5)
                            {
                                for (int i = 0; i < 4; i++)
                                {
                                    if (parameter[11] == i)
                                    {
                                        for (int k = 0; k < 3; k++)
                                        {
                                            pricetext[i + 4][k] = pricetextor[i + 4][k];
                                        }
                                        parameter[11] = choosing - 5;
                                        for (int k = 0; k < 3; k++)
                                        {
                                            pricetext[choosing - 1][k] = '#';
                                        }
                                        mvwprintw(win, 16, 14 + (10 * (i)), "%s", pricetext[i]);
                                        wattron(win, A_STANDOUT);
                                        mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s", pricetext[choosing - 1]);
                                        wattroff(win, A_STANDOUT);
                                        break;
                                    }
                                }
                                break;
                            }
                            else
                            {
                                if (parameter[0] >= price[choosing - 1])
                                {
                                    parameter[0] = parameter[0] - price[choosing - 1];
                                    parameter[choosing] = 1;
                                    mvwprintw(win, 17, (xMax / 4) - 21 / 2, "Restart game to save!");
                                }
                                else
                                {
                                    wattron(win, COLOR_PAIR(10));
                                    mvwprintw(win, 17, (xMax / 4) - 14 / 2, "No enough gold");
                                    wattroff(win, COLOR_PAIR(10));
                                }
                            }
                        }
                        break;
                    }
                    case KEY_RIGHT:
                    {
                        if (choosing < 1)
                        {
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 18, (xMax / 4) - 4 / 2, "Back");
                            wattroff(win, A_NORMAL);
                            choosing++;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 11, 14, "%s", pricetext[0]);
                            wattroff(win, A_STANDOUT);
                        }
                        else
                        {
                            if (choosing < 4)
                            {
                                wattron(win, A_NORMAL);
                                mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s", pricetext[choosing - 1]);
                                wattroff(win, A_NORMAL);
                                choosing++;
                                wattron(win, A_STANDOUT);
                                mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s", pricetext[choosing - 1]);
                                wattroff(win, A_STANDOUT);
                            }
                            else if (choosing >= 4)
                            {
                                if (choosing == 4)
                                {
                                    wattron(win, A_NORMAL);
                                    mvwprintw(win, 11, 44, "%s", pricetext[3]);
                                    wattroff(win, A_NORMAL);
                                    choosing++;
                                    wattron(win, A_STANDOUT);
                                    mvwprintw(win, 16, 14, "%s", pricetext[4]);
                                    wattroff(win, A_STANDOUT);
                                }
                                else if (choosing < 8)
                                {
                                    wattron(win, A_NORMAL);
                                    mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s", pricetext[choosing - 1]);
                                    wattroff(win, A_NORMAL);
                                    choosing++;
                                    wattron(win, A_STANDOUT);
                                    mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s", pricetext[choosing - 1]);
                                    wattroff(win, A_STANDOUT);
                                }
                            }
                        }
                        break;
                    }
                    case KEY_LEFT:
                    {
                        if (choosing < 2)
                        {
                            choosing--;
                            wattron(win, A_STANDOUT);
                            mvwprintw(win, 18, (xMax / 4) - 4 / 2, "Back");
                            wattroff(win, A_STANDOUT);
                            wattron(win, A_NORMAL);
                            mvwprintw(win, 11, 14, "%s", pricetext[0]);
                            wattroff(win, A_NORMAL);
                        }
                        else
                        {
                            if (choosing < 5)
                            {
                                wattron(win, A_NORMAL);
                                mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s", pricetext[choosing - 1]);
                                wattroff(win, A_NORMAL);
                                choosing--;
                                wattron(win, A_STANDOUT);
                                mvwprintw(win, 11, 14 + (10 * (choosing - 1)), "%s", pricetext[choosing - 1]);
                                wattroff(win, A_STANDOUT);
                            }
                            else if (choosing >= 5)
                            {
                                if (choosing == 5)
                                {
                                    wattron(win, A_STANDOUT);
                                    mvwprintw(win, 11, 44, "%s", pricetext[3]);
                                    wattroff(win, A_STANDOUT);
                                    choosing--;
                                    wattron(win, A_NORMAL);
                                    mvwprintw(win, 16, 14, "%s", pricetext[4]);
                                    wattroff(win, A_NORMAL);
                                }
                                else
                                {
                                    wattron(win, A_NORMAL);
                                    mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s", pricetext[choosing - 1]);
                                    wattroff(win, A_NORMAL);
                                    choosing--;
                                    wattron(win, A_STANDOUT);
                                    mvwprintw(win, 16, 14 + (10 * (choosing - 5)), "%s", pricetext[choosing - 1]);
                                    wattroff(win, A_STANDOUT);
                                }
                            }
                        }
                        break;
                    }
                    }
                    if (exit == 1)
                    {
                        refresh_menu(name, parameter, xMax, yMax, i);
                        exit = 0;
                        break;
                    }
                }
                break;
            }
            else if (i == 3)
            {
                exit = 1;
                break;
            }
        }
        }
        // exit
        if (exit == 1)
        {
            break;
        }
    } while ((ch = wgetch(win)) != '+');

    endwin();
}

void refresh_menu( char name[5][35],  int parameter[], const int xMax, const int yMax,  int i)
{
    WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
    wclear(win);
    box(win, 0, 0);
    wattron(win, COLOR_PAIR(1));
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            mvwprintw(win, 2 + i, 16 + j, "%c", name[i][j]);
            wrefresh(win);
        }
    }
    wattroff(win, COLOR_PAIR(1));
    char buttons[4][12] = {{"Play"}, {"Levels"}, {"Shop"}, {"Exit"}};
    for (int j = 0; j < 4; j++)
    {
        if (j == i)
        {
            wattron(win, A_STANDOUT);
        }
        mvwprintw(win, 8 + (2 * j), (xMax / 4) - strlen(buttons[j]) / 2, "%s", buttons[j]);
        wattroff(win, A_STANDOUT);
    }
    wattron(win, COLOR_PAIR(17));
    mvwprintw(win, 18, 38, "Made by bromscandium");
    wattroff(win, COLOR_PAIR(17));
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 8, 10, "Best: %d", parameter[1]);
    mvwprintw(win, 9, 10, "Destroys: %d", parameter[12]);
    int seconds = parameter[13] % 60;
    int minutes = (parameter[13] / 60) % 60;
    int hours = ((parameter[13] / 60) / 60) % 24;
    mvwprintw(win, 10, 10, "Time: %02d:%02d:%02d", hours, minutes, seconds);
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
}