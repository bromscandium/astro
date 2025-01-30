// levels.h
#ifndef LEVELS_H
#define LEVELS_H

#include <curses.h>

// Function declarations
void levels(WINDOW *win, int *settings);
void refresh_level(WINDOW *win, int *settings, int selected);

#endif //LEVELS_H
