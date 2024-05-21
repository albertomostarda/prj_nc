#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

static char *logo[]={

"     __  .__  __         .__          ",
"  _/  |_|__|/  |_  ____ |  |   ____  ",
" \\   __\\  \\   __\\/  _ \\|  |  /  _ \\ ",
" |  | |  ||  | (  <_> )  |_(  <_> )",
"|__| |__||__|  \\____/|____/\\____/ "                                  
};


void pause(void){
    printw("Premi INVIO per continuare . . .");
    refresh();
    getchar();
}

void start(){
    bool isRes;
    system("resize -s 40 160 >/dev/null");
    initscr();
    WINDOW *win=newwin(40,160,0,0);
    refresh();
    box(win, 0 ,0);
    // isRes=is_term_resized(30,80);
    // if(isRes)
    //     mvwprintw(win, 1, 1, "Si puo fare");
    // else
    //     mvwprintw(win, 1, 1, "No");
    wrefresh(win);
    for(int i=0;i<5;i++){
        mvwprintw(win, i+1,i+1, "%s",logo[i]);
        
    }
    wrefresh(win);
    getch();
    endwin();
    
}