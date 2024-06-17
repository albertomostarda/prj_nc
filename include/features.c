#include "features.h"
#include "levels.h"
#include "menufunctions.h"
//#include "test.c" //Luogo felice per provare i codici senza intasare il codice
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses/ncurses.h>
// #include <unistd.h>
#include <time.h>
#include <windows.h>
// #include <signal.h>
#include <setjmp.h> //Probabilmente non lo utilizzero'
//Per tornare a un punto specifico dopo il signal potrei utilizzare il setjmp e longjmp implementando la libreria setjmp.h
//Mi devo ricordare di implementare una var globale per tenere traccia dello funzione in cui si trova il programma
//state_t curState;

const int max_path=4096;
static char *initTxt="Per navigare durante tutto il gioco si possono utilizzare sia le freccette direzionali sia i tasti WASD. Buona Programmazione";
static char *pContinue="Premi INVIO per continuare";
static char *sizeWarn="Per favore evita di ridimensionare la finestra del terminale";
// Giacomo 5-1, avevo la necessita di un testo abbastanza grande per il testing;
static char *testBible="Ora a voi, ricchi: piangete e gridate per le sciagure che cadranno su di voi! Le vostre ricchezze sono marce, i vostri vestiti sono mangiati dalle tarme. Il vostro oro e il vostro argento sono consumati dalla ruggine, la loro ruggine si alzerà ad accusarvi e divorerà le vostre carni come un fuoco.";
int sLevel, rStatus=1;


void nclearBuff(void){
    int buff;
    nodelay(stdscr, TRUE);
    while((buff=getch())!=ERR);
    nodelay(stdscr, FALSE);

}
// char *getPath() {
//     int j=0;
//     char *path = (char *)malloc(max_path * sizeof(char));
//     if (path == NULL) {
//         printw("Percorso non allocato");
//         refresh();
//         napms(5000);
//         return NULL;
//     }
//     ssize_t len = readlink("/proc/self/exe", path, max_path - 1);
//     for (ssize_t i = len - 1; i >= 0; i--) {
//         if (path[i] == '/') {
//             path[i] = '\0';
//             break;
//         }
//     }
//     char *exePath = (char *)malloc(strlen(path) + 1);
//     strcpy(exePath, path);
//     return exePath;
// }
char *getPath(){
    int pathsize=0, isFound=1;
    char *path=(char *)malloc(max_path*sizeof(char));
    GetModuleFileName(NULL, path, max_path);
    pathsize=strlen(path);
    for(int i=pathsize;isFound&&i>=0;i--){
        if(path[i]=='\\'){
            path[i]='\0';
            isFound=0;
        }
    }
    path=(char *)realloc(path,strlen(path));
    return path;
}
// void handle_resize(int sig){
//     if(curState==fSTART){
//         //ipotetica chiamata del salto
//     }
//     else if(curState==fRUN){

//     }
// }
void myPause(void){
    printw("Premi INVIO per continuare . . .");
    refresh();
    getch();
}
void start(){
    time_t start_time;
    int halfContinue=strlen(pContinue)/2;
    system("MODE 160,35");
    //system("resize -s 35 160 >/dev/null"); //per windows;
    //signal(SIGWINCH, handle_resize);
    initscr();
    cbreak();
    noecho();
    start_color();
    initColors();
    refresh();
    //win=newwin(35,160,0,0);
    box(stdscr,0,0);
    wrefresh(stdscr);
    Cprint(stdscr,initTxt,20,0,1);
    //Hprint(win, pContinue,20,0);
    mvwprintw(stdscr,24,(getmaxx(stdscr)/2)-halfContinue,"%s", pContinue);
    wmove(stdscr,25,11);
    SBHprint(stdscr,sizeWarn,20);
    if(!can_change_color()){
        mvwprintw(stdscr,1,1,"%d",COLORS);
        getch();
    }else{
        mvwprintw(stdscr,1,1,"supporta i colori");
        getch();
    }
    start_time=time(NULL);
    nodelay(stdscr,TRUE);
    while(getch()!='\n'&&(time(NULL)-start_time)<10);
    nodelay(stdscr,FALSE);
    nclearBuff();
    werase(stdscr);
    refresh();
}
void run(){
    int isRun=1;
    while(isRun){
        switch(rStatus){
            case 1:
                init_menu();
                menu(&isRun);
                break;
            case 2:
                sLevel=1;
                printLvl_one();
                level_one();
                rStatus=1;
                break;
        }
    }
}
void Cprint(WINDOW *tmp,  char *pText, int hPad, int vPad, int fNL){
    //da aggiustare in vista di righe pari
    int hSize=getmaxx(tmp), vSize=getmaxy(tmp);
    int lidx=0, ridx=0, nStr=0, hStart=0,txtLength=0, midoff=0;
    char **final_txt=Hsplit(hSize,pText,NULL,hPad,fNL,&nStr);
    lidx=ridx=nStr/2;
    if(nStr==0||final_txt==NULL){
        mvwprintw(tmp,1,1,"Errore nella stampa del Testo");
    }
    else if(nStr<3){
        int midStr=nStr / 2;
        for(int i=0;i<nStr;i++){
            txtLength = strlen(final_txt[i]);
            hStart = (hSize / 2) - (txtLength / 2);
            mvwprintw(tmp, (vSize / 2) + i - midStr, hStart, "%s", final_txt[i]);
            wmove(tmp, (vSize / 2) + i - midStr+1,hPad/2);
        }
    }
    else{
        //Gestione delle righe pari
        // if(nStr%2==0){
        //     midoff+1;
        //     lidx--;
        // }
        while(lidx>=0&&ridx<nStr){
            if(midoff==0){
                txtLength=strlen(final_txt[nStr/2]);
                hStart=(hSize/2)-(txtLength/2);
                mvwprintw(tmp, vSize/2,hStart,"%s",final_txt[nStr/2]);
                lidx--;
                ridx++;
                midoff++;
            }
            txtLength=strlen(final_txt[lidx]);
            hStart=(hSize/2)-(txtLength/2);
            mvwprintw(tmp, vSize/2-midoff,hStart,"%s",final_txt[lidx]);
            txtLength=strlen(final_txt[ridx]);
            hStart=(hSize/2)-(txtLength/2);
            mvwprintw(tmp, vSize/2+midoff,hStart,"%s",final_txt[ridx]);
            lidx--;
            ridx++;
            midoff++;
        }
        while(lidx>=0){
            txtLength=strlen(final_txt[lidx]);
            hStart=(hSize/2)-(txtLength/2);
            mvwprintw(tmp, vSize/2-midoff,hStart,"%s",final_txt[lidx]);
            lidx--;
            midoff++;
        }
        while(ridx<nStr){
            txtLength=strlen(final_txt[ridx]);
            hStart=(hSize/2)-(txtLength/2);
            mvwprintw(tmp, vSize/2+midoff,hStart,"%s",final_txt[ridx]);
            ridx++;
            midoff++;
        }
        wmove(tmp, (vSize/2)+midoff+1,hPad/2);
    }
    for (int i = 0; i < nStr; i++) {
        free(final_txt[i]);
    }
    free(final_txt);
    wrefresh(tmp);
}

char** Hsplit(int HSIZE,  char *pText, char **split_txt,int padding, int forceNL, int *nLines) {
    int textLength = strlen(pText);

    if (textLength > (HSIZE - padding) || forceNL) {
        forceNL = 0;
        int fstSpc = csearch(pText, textLength / 2, ' ');
        if (fstSpc == -1) {
            fstSpc = textLength / 2;
        }
        char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
        char *halfStr = (char *)malloc((textLength - fstSpc) * sizeof(char));
        strncpy(newTxt, pText, fstSpc);
        newTxt[fstSpc] = '\0';
        strcpy(halfStr, pText + fstSpc + 1);

        split_txt = Hsplit(HSIZE, newTxt, split_txt, padding, 0, nLines);
        split_txt = Hsplit(HSIZE, halfStr, split_txt, padding, 0, nLines);

        free(newTxt);
        free(halfStr);
    } else {
        split_txt = (char **)realloc(split_txt, (*nLines + 1) * sizeof(char *));
        split_txt[*nLines] = (char *)malloc((textLength + 1) * sizeof(char));
        strcpy(split_txt[*nLines], pText);
        (*nLines)++;
    }
    return split_txt;
}
void Hprint(WINDOW *tmp,  char *pText, int padding, int forceNL) {
    int hSize = getmaxx(tmp);
    int curY = getcury(tmp);
    int textLength = strlen(pText);
    int nStr=0;

    if (curY == 0) {
        curY = 1;
    }

    char **final_txt = Hsplit(hSize, pText,NULL, padding, forceNL, &nStr);

    for (int i = 0; i < nStr; i++) {
        textLength = strlen(final_txt[i]);
        int cStart = (hSize / 2) - (textLength / 2);
        mvwprintw(tmp, curY + i, cStart, "%s", final_txt[i]);
        wrefresh(tmp);
        wmove(tmp, curY + i + 1, getbegx(tmp) + 1);
    }

    for (int i = 0; i < nStr; i++) {
        free(final_txt[i]);
    }
    free(final_txt);
}
void SBHprint(WINDOW *tmp, char *pText, int padding){
    int hSize= getmaxx(tmp)-getbegx(tmp), txtLength=strlen(pText);
    int cStart=0, curY=getmaxy(tmp)-2;
    cStart=(hSize/2)-(txtLength/2);
    mvwprintw(tmp, curY, cStart, "%s", pText);
    wmove(tmp, getbegy(tmp)+1, getmaxx(tmp)+1);
    wrefresh(tmp);
}
int csearch(  char *sample, int start, char find) {
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

int fCountLines(FILE *tmpFile){
    int fLines=0;
    char eFlag='\0';
    while((eFlag=fgetc(tmpFile))!=EOF){
        if(eFlag=='\n'){
            fLines++;
        }
    }
    rewind(tmpFile);
    return fLines;
}

int fCountCols(FILE *tmpFile){
    int fCols=0;
    char eFlag='\0';
    while((eFlag=fgetc(tmpFile))!='\n'){
        fCols++;
    }
    rewind(tmpFile);
    return fCols;
}
void initColors(){
    init_pair(1, COLOR_WHITE, COLOR_BLACK); //testo normale
    init_pair(2, COLOR_WHITE, COLOR_WHITE); // per #
    init_pair(3, COLOR_RED,COLOR_RED);    // per eventuali nemici
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW); // per il percorso utilizzabile 2
    init_pair(5,COLOR_BLACK,COLOR_BLACK); // per lo spazio vuoto 0
    init_pair(6, COLOR_GREEN, COLOR_GREEN); // per il traguardo 9
    init_pair(7, COLOR_WHITE, COLOR_BLUE);   // per il personaggio
    init_pair(8, COLOR_WHITE, COLOR_GREEN);
}
