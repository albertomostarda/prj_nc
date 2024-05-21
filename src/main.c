#include "../include/features.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    WINDOW *console;
    start(console);
    run(console);
    pause();
    return 0;
}