#include "features.h"
#include "levels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <signal.h>
#include <setjmp.h> //Probabilmente non lo utilizzero'
//Per tornare a un punto specifico dopo il signal potrei utilizzare il setjmp e longjmp implementando la libreria setjmp.h
//Mi devo ricordare di implementare una var globale per tenere traccia dello funzione in cui si trova il programma
//
state_t curState;
WINDOW *win;

static char *logo[]={
"  __  .__  __         .__          ",
"_/  |_|__|/  |_  ____ |  |   ____  ",
"\\   __\\  \\   __\\/  _ \\|  |  /  _ \\ ",
" |  | |  ||  | (  <_> )  |_(  <_> )",
" |__| |__||__|  \\____/|____/\\____/ "                                  
};

static char *initTxt="Per navigare durante tutto il gioco si possono utilizzare sia le freccette direzionali sia i tasti WASD. Buona Programmazione";
static char *pContinue="Premi INVIO per continuare";
static char *sizeWarn="Perfavore evita di ridimensionare la finestra del terminale";

void nclearBuff(){
    int buff;
    nodelay(stdscr, TRUE);
    while((buff=getch())!=ERR);
    nodelay(stdscr, FALSE);

}

void handle_resize(int sig){
    if(curState==fSTART){
        //ipotetica chiamata del salto
    }
    else if(curState==fRUN){

    }
}
void pause(void){
    printw("Premi INVIO per continuare . . .");
    refresh();
    getch();
}

void run(){
    int isRun=1, status=1;
    while(isRun){
        switch(status){
            case 1:
                menu(win);
                break;
        }
    }
}
void start(){
    time_t start_time;
    system("resize -s 40 160 >/dev/null");
    initscr();
    cbreak();
    noecho();
    refresh();
    signal(SIGWINCH, handle_resize);
    win=newwin(40,160,0,0);
    box(win,0,0);
    wrefresh(win);
    Hprint(win, initTxt,20,1);
    Hprint(win, pContinue,20,0);
    SBHprint(win,sizeWarn,20);
    start_time=time(NULL);
    nodelay(stdscr,true);
    while(getch()!='\n'&&(time(NULL)-start_time)<10);
    nodelay(stdscr,false);
    nclearBuff();
}

void Hprint(WINDOW *tmp, char *pText, int padding, int forceNL){
    int hSize= getmaxx(tmp)-getbegx(tmp);
    int cStart=0, curY=getcury(tmp);
    int textLength = strlen(pText);
    if(curY==0){
        curY=1;
    }
    if (textLength > (hSize - padding) || forceNL) {
        forceNL=0;
        int fstSpc = csearch(pText, textLength / 2, ' ');
        if (fstSpc == -1) {
            fstSpc = textLength / 2;
        }
        char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
        char *halfStr = (char *)malloc((textLength - fstSpc) * sizeof(char));
        strncpy(newTxt, pText, fstSpc);
        newTxt[fstSpc] = '\0';
        strcpy(halfStr, pText + fstSpc + 1);
        halfStr[(textLength - fstSpc)-1]='\0';
        Hprint(tmp, newTxt, padding,0);
        Hprint(tmp, halfStr, padding, 0);
        free(newTxt);
        free(halfStr);
    } else {
        cStart=(hSize/2)-(textLength/2);
        mvwprintw(tmp, curY, cStart,"%s", pText);
        wrefresh(tmp);
        wmove(tmp,curY+1,getbegx(tmp)+1);
    }
}

void Cprint(WINDOW *tmp, char *pText, int hPad, int vPad, int fNL){
    int hSize= getmaxx(tmp)-getbegx(tmp);
    int vSize= getmaxy(tmp)-getbegy(tmp);
    int hStart=0;
    int curY=getcury(tmp);
    int textLength = strlen(pText);

}

void SBHprint(WINDOW *tmp, char *pText, int padding){
    int hSize= getmaxx(tmp)-getbegx(tmp), txtLenght=strlen(pText);
    int cStart=0, curY=getmaxy(tmp)-2;
    cStart=(hSize/2)-(txtLenght/2);
    mvwprintw(tmp, curY, cStart, "%s", pText);
    wmove(tmp, getbegy(tmp)+1, getmaxx(tmp)+1);
    wrefresh(tmp);
}

int csearch(char *sample, int start, char find) {
    for (int i = start; i < strlen(sample); i++) {
        if (sample[i] == find) {
            return i;
        }
    }
    return -1;
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