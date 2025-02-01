// shop.h
#ifndef SHOP_H
#define SHOP_H

#include <curses.h>

// Function declarations
void shop(WINDOW *win, int *settings);
void refresh_shop(WINDOW *win, int selected, int *price, int *settings);

#endif //SHOP_H
