#include "../include/features.h"
#include <ncurses/ncurses.h>
#include <stdio.h>


int main(){
    
    char ch='\0';
    
    initscr();
    printw("ncurses ver: %d, %d, %d\n", NCURSES_VERSION_MAJOR, NCURSES_VERSION_MINOR, NCURSES_VERSION_PATCH);
    refresh();
    pause();
    noecho();
    clear();
    move(10,10);
    while((ch=getch())!='\n'){
        printw("Hai premuto %c\n", ch);
        refresh();
    }

    endwin();
    pause();
    return 0;
}