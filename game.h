// game.h
#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <curses.h>

// Function declarations
void game(WINDOW *win, int settings[]);
void movement(const char ch, int playerpos[]);
void second();

#endif // GAME_H