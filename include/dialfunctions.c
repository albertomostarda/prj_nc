#include "dialfunctions.h"
#include "levels.h"
#include "features.h"
#include <windows.h>
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <time.h>

char **dialogue_buffer;
int dialBuff_size=0, dialPos=0;

void reloadDialogue(LPVOID *data){
    ThreadParam *tParam = (ThreadParam*)data;
    time_t waitTime;
    while(1){
        if(*(tParam->gLight)!=0){
            *(tParam->gLight)=0;
            waitTime=time(NULL);
            while((time(NULL)-waitTime)<30);
            printOneDLine();
        }
        Sleep(500);
    }
}
char* getDialPath(){
    char *pPath=getPath(), fName[28], *dialPath=NULL;
    switch(sLevel){
        case 1:
            strcpy(fName, "resources\\dialogueone.txt");
            break;
        case 2:
            strcpy(fName, "resources\\dialoguetwo.txt");
            break;
        case 3:
            strcpy(fName, "resources\\dialoguethree.txt");
            break;
        case 4:
            strcpy(fName, "resources\\dialoguefour.txt");
            break;
        case 5:
            strcpy(fName, "resources\\dialoguefive.txt");
            break;
    }
    dialPath=(char *)malloc(strlen(pPath)+strlen(fName)+1);
    strcat(dialPath,pPath);
    if(dialPath[strlen(dialPath)]!='\\'){
        dialPath[strlen(dialPath)]='\\';
    }
    strcat(dialPath,fName);
    return dialPath;
}
void loadDialogue(){
    FILE *fp;
    char *pDial=getDialPath(), buffer[1024];
    int dLenght=0;
    fp=fopen(pDial,"r");
    if(fp==NULL){
        mvwprintw(dialogue,1,1,"Dialoghi non caricati");
        wrefresh(dialogue);
        fclose(fp);
        free(pDial);
        return ;
        //aggiungere chiusura/ritorno al Menu
    }
    dialBuff_size=fCountLines(fp);
    dialogue_buffer=(char **)realloc(dialogue_buffer,dialBuff_size*sizeof(char));
    for(int i=0;i<dialBuff_size;i++){
        if(fgets(buffer,sizeof(buffer),fp)!=NULL){
            dLenght=strlen(buffer);
            if(buffer[dLenght-1]=='\n'){
                buffer[dLenght-1]='\0';
            }
            dialogue_buffer[i]=(char *)realloc(dialogue_buffer[i],dLenght*sizeof(char));
            if(dialogue_buffer[i]!=NULL){
                strcpy(dialogue_buffer[i],buffer);
            }
        }
    }
    fclose(fp);
}
void printOneDLine(){
    int maxDY=getmaxy(dialogue)-1, maxDX=getmaxx(dialogue)-1;
    Cprint(dialogue,dialogue_buffer[dialPos],1,1,0);
    if(dialPos==0){
        mvwprintw(dialogue,maxDY,1,"< Precedente ('P')");
    }else if(dialPos==dialBuff_size-1){
        mvwprintw(dialogue,maxDY,maxDX,"('N') Prossimo >");
    }else{
        mvwprintw(dialogue,maxDY,1,"< Precedente ('P')");
        mvwprintw(dialogue,maxDY,maxDX,"('N') Prossimo >");
    }
    wrefresh(dialogue);
}

