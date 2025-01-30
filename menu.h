// menu.h
#ifndef MENU_H
#define MENU_H

#include <curses.h>

// Function declarations
void menu(WINDOW *win, int *settings);
void refresh_menu(WINDOW *win, int *settings, int i);

#endif // MENU_H
