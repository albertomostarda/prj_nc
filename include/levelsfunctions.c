#include "levelsfunctions.h"
#include "features.h"
#include "levels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

char *action_choice[]={"INSERISCI","ELIMINA","ESEGUI","ESCI"};
Pos choicePos[4];

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

void init_action(int lPad, int uPad){
    int vSize=0,hSize=0;
    action_buffer=(int *)realloc(action_buffer, 2*sizeof(int));
    getmaxyx(action,vSize,hSize);
    action_buffer[0]=action_START;
    switch (sLevel)
    {
        case 1:
            action_buffer[1]=action_VAR+2;
            mvwprintw(action, uPad+1, lPad+3, "int nPassi= %d;", action_buffer[1]-action_VAR);
            break;
        default:
            break;
    }
    mvwprintw(action, uPad, lPad, "INIZIO");
    choicePos[0].y=vSize-2;
    choicePos[1].y=vSize-2;
    choicePos[2].y=vSize-4;
    choicePos[3].y=vSize-2;
    choicePos[0].x=uPad+5;
    choicePos[1].x=uPad+22;
    choicePos[2].x=uPad+22;
    choicePos[3].x=uPad+37;
    mvwprintw(action, choicePos[0].y, choicePos[0].x, "%s", action_choice[0]);
    mvwprintw(action, choicePos[1].y, choicePos[1].x, "%s", action_choice[1]);
    mvwprintw(action, choicePos[2].y, choicePos[2].x, "%s", action_choice[2]);
    mvwprintw(action, choicePos[3].y, choicePos[3].x, "%s", action_choice[3]);
    wrefresh(action);
}

void action_run(){
    int choice=0, highlight=0, fBreak=1;
    keypad(action, TRUE);
    //nodelay(action, TRUE);
    while(fBreak){
        for(int i=0;i<4;i++){
            if(i==highlight){
                wattron(action, A_REVERSE);
                mvwprintw(action, choicePos[i].y,choicePos[i].x,"%s",action_choice[i]);
                wattroff(action, A_REVERSE);
            }else{
                mvwprintw(action, choicePos[i].y,choicePos[i].x,"%s",action_choice[i]);
            }
        }
        choice=wgetch(action);
        nclearBuff();
        switch(choice){
            case 'a':
            case 'A':
            case KEY_LEFT:
                if(highlight==0){
                    highlight=3;
                }else{
                    highlight--;
                }
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                if(highlight==3){
                    highlight=0;
                }else{
                    highlight++;
                }
                break;
            case '\n':
                action_subrun(highlight,&fBreak);
                break;
        }
    }
    //nodelay(action, FALSE);
}

void action_subrun(int status,int *EXITflag){
    switch (status)
    {
        default:
            return;
            break;
        case 0:
            action_add();
        case 3:
            *EXITflag=0;
            break;
    }
    return ;
}

void action_add(){
    switch(sLevel){
        case 1:
            addone();
            return;
            break;
    }
}
void addone(){
    
}