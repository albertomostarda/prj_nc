// 2289 linee di codice woho
#include "../include/features.h"
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    start();
    run();
    //stop(); da mettere in features.c
    werase(stdscr);
    wrefresh(stdscr);
    myPause();
    return 0;
}