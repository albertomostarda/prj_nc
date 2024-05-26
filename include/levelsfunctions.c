#include "levelsfunctions.h"
#include "features.h"
#include "levels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

char** print_map(int sLevel, int lPad, int uPad){
    FILE *fp;
    char *exePath=getPath();
    char fileName[23], buffer[160];
    char *fullpath=(char*)malloc(max_path);
    int fLines=0, fCols=0,wBegy=0, wBegx=0;
    switch (sLevel)
    {
        case 1:
            strcpy(fileName, "resources/levelone.txt");
            break;
    }
    strcat(fullpath, exePath);
    if (strlen(fullpath)!='/')
    {
        fullpath[strlen(fullpath)]='/';
    }
    strcat(fullpath,fileName);
    fp=fopen(fullpath,"r");
    if(fp==NULL){
        mvwprintw(dialogue, 1,1, "File non trovato");
        wrefresh(dialogue);
        napms(5000);
        free(fullpath);
        getch();
    }
    fLines=fCountLines(fp);
    //fCols=fCountCols(fp);
    char **Mmap=(char**)malloc(fLines*sizeof(char*));
    if(Mmap ==NULL){
        fclose(fp);
        free(fullpath);
        return NULL;
    }
    // for (int i = 0; i < fLines; i++) {
    //     if (fgets(buffer, sizeof(buffer), fp) != NULL) {
    //         mvwprintw(dialogue, 1, 1, "Linea %d: %s", i + 1, buffer);
    //         wrefresh(dialogue);
    //         napms(500);
    //         Mmap[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    //         strcpy(Mmap[i], buffer);
    //     }
    // }

   for (int i = 0; i < fLines; i++) {
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if(buffer[strlen(buffer)-1]=='\n'){
                buffer[strlen(buffer)-1]='\0';
            }
            int length = strlen(buffer);
            Mmap[i] = (char*)malloc(length * sizeof(char));
            if (Mmap[i] != NULL) {
                strcpy(Mmap[i], buffer);
            }
        }
    }

    mvwprintw(dialogue, 1,1, "array creato");
    wrefresh(dialogue);
    getch();
    free(fullpath);
    fclose(fp);
    getbegyx(map,wBegy,wBegy);

    for(int i=0;i<fLines;i++){
        wmove(map,wBegy+uPad+i,wBegx+lPad);
        printcolor_str(map,Mmap[i], strlen(Mmap[i]));
        wrefresh(map);
        napms(100);
    }
    // for(int i=0;i<fLines;i++){
    //     mvwprintw(map, wBegy+uPad+i,wBegx+lPad,"%s",Mmap[i]);
    //     wrefresh(map);
    //     napms(200);
    // }
   
    return Mmap;
}

void printcolor_str(WINDOW *tWin,char *colStr, int pLines){
    for(int i=0;i<pLines;i++){
        printcolor_char(tWin,colStr[i]);
    }
}
void printcolor_char(WINDOW *tWin,char cch){
    switch(cch){
        case '#':
            waddch(tWin, walls);
            break;
        case '0':
            waddch(tWin, blank);
            break;
        case '1':
            waddch(tWin, pg1.icon);
            break;
        case '2':
            waddch(tWin, road);
            break;
        case '9':
            waddch(tWin, goal);
            break;
    }
}

void init_action(int sLevel, int lPad, int uPad){
    action_buffer=(int *)realloc(action_buffer, 2*sizeof(int));
    action_buffer[0]=action_START;
    mvwprintw(action, uPad, lPad, "INIZIO");
    wmove(action, uPad+2, lPad+3);
    wrefresh(action);
}