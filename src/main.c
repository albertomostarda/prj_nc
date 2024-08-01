#include "../include/features.h"
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    start();
    run();
    werase(stdscr);
    wrefresh(stdscr);
    myPause();
    return 0;
}