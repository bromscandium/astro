// main.h
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

// Constants definitions
#define MEGAYELLOW 226
#define MEGARED 160
#define MEGAWHITE 231
#define MEGAGRAY 241
#define MEGAORANGE 208
#define MEGAPINK 196
#define MEGABLUE 105
#define HEIGHT 40
#define WIDTH 121

// Function declarations
int main();
int load_settings(int *settings);
int save_settings(int *settings);

#endif // MAIN_H