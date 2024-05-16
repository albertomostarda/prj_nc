#include "features.h"
#include <stdio.h>
#include <ncurses/ncurses.h>

void pause(void){
    printw("Premi INVIO per continuare . . .");
    refresh();
    getchar();
}