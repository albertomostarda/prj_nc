#include "../include/features.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    start();
    run();
    werase(win);
    wrefresh(win);
    myPause();
    return 0;
}