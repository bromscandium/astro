// menu.h
#ifndef MENU_H
#define MENU_H

#include <time.h>

// Function declarations
void menu( int parameter[], const int xMax, const int yMax,  int sizeparameter, struct timespec ts);
void refresh_menu( char name[5][35],  int parameter[], const int xMax, const int yMax,  int i);

#endif // MENU_H
