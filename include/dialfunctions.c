#include "dialfunctions.h"
#include "levels.h"
#include "features.h"
#include <windows.h>
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <time.h>

void reloadDialogue(LPVOID *data){
    ThreadParam *tParam = (ThreadParam*)data;
    time_t waitTime;
    while(1){
        if(*(tParam->gLight)!=0){
            *(tParam->gLight)=0;
            waitTime=time(NULL);
            while((time(NULL)-waitTime)<30);
            printDialogue();
        }
        Sleep(500);
    }
}
char getDialPath(){
    FILE *fp;
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
    if(dialPath[strlen(dialPath)]-1!='\\'){
        
    }
}
void loadDialogue(){
    
}

