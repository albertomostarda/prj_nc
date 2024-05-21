#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

static char *logo[]={
"  __  .__  __         .__          ",
"_/  |_|__|/  |_  ____ |  |   ____  ",
"\\   __\\  \\   __\\/  _ \\|  |  /  _ \\ ",
" |  | |  ||  | (  <_> )  |_(  <_> )",
" |__| |__||__|  \\____/|____/\\____/ "                                  
};

static char *initTxt="Per navigare durante tutto il gioco si possono utilizzare sia le freccette direzionali sia i tasti WASD. Buona Programmazione";

void pause(void){
    printw("Premi INVIO per continuare . . .");
    refresh();
    getchar();
}

void run(WINDOW *win){
    int isRun=1, status=1;
    while(isRun){
        switch(status){
            case 1:
                menu(win);
        }
    }
}
void start(WINDOW *win){
    bool isRes;
    system("resize -s 40 160 >/dev/null");
    initscr();
    win=newwin(0,0,40,160);
    refresh();
    Hprint(win, )
}

void Hprint(WINDOW *tmp, char *pText, int padding){
    int hSize= getmaxx(tmp)-getbegx(tmp);
    if(strlen(pText)>(hSize-padding){
        int fstSpc=csearch(pText,strlen(pText)/2,' ');
        char *halfStr
    }
}

int csearch(char *sample, int start, char find){
    int idxFound=0, isFound=0;

    for(int i=start;i<strlen(sample)&&isFound!=0;i++){
        if(sample[i]==find){
            idxFound=i;
            isFound=1;
        }
    }
    return idxFound;
}

void artHprint(WINDOW *tmp, int hSize, char **draw, int dHeight){
    int avgL=0, cStart=0, curY=0;

    for(int i=0;i<dHeight;i++){
        if(strlen(draw[i])>avgL){
            avgL=strlen(draw[i]);
        }
    }
    cStart=(hSize-avgL)/2;
    curY=getcury(tmp);
    for(int i=0;i<dHeight;i++){
        if(curY==0)
            mvwprintw(tmp, curY+i+1,cStart, "%s",draw[i]);
        else
            mvwprintw(tmp, curY+i,cStart, "%s", draw[i]);
    }
    wrefresh(tmp);
}