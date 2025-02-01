// game.h
#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <curses.h>

// Function declarations
void game(WINDOW *win, int settings[]);
void movement(const char ch, int playerpos[]);
void results(WINDOW *win, int *settings, int golds, int destroys, int playedtime, int life, int time, int scores);
void second();

#endif // GAME_H