#include "utils.h"
#include <time.h>
#include <unistd.h>

void movement(char ch, int playerpos[]) {
    if (ch == 'w' || ch == 'W') {
        playerpos[0]--;
        playerpos[1]--;
        playerpos[2]--;
    } else if (ch == 's' || ch == 'S') {
        playerpos[0]++;
        playerpos[1]++;
        playerpos[2]++;
    }
}

void second() {
    struct timespec timer = {
        .tv_sec = 1,
        .tv_nsec = 0
    };
    nanosleep(&timer, NULL);
}