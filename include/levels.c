#include "levels.h"
#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>

WINDOW *map;
WINDOW *action;
WINDOW *dialogue;

void menu(){
    return;
}
void print_map(int sLevel){
    FILE *fp;
    char *exePath=getPath();
    char fileName[13];
    char fullpath[max_path];
    int fLines=0, fCols=0;
    switch (sLevel)
    {
        case 1:
            strcpy(fileName, "levelone.txt\0");
            break;
    }
    strcat(fullpath, exePath);
    if (strlen(fullpath)-1!='/')
    {
        fullpath[strlen(fullpath)-1]='/';
        strcat(fullpath,fileName);
    }else{
        strcat(fullpath,fileName);
    }
    fp=fopen(fullpath,"r");
    fLines=fCountLines(fp);
    fCols=fCountCols(fp);
    char **Mmap=(char**)malloc(fLines*sizeof(char*));
    
}
void printLvl_one(){
    time_t wait;
    map=newwin(24,110,0,0);
    action=newwin(35,60,0,110);
    dialogue=newwin(11,110,24,0);
    wrefresh(map);
    wrefresh(action);
    wrefresh(dialogue);
    box(map, 0,0);
    box(action, 0,0);
    box(dialogue,0,0);
    wrefresh(map);
    wrefresh(action);
    wrefresh(dialogue);
    getch();
    
}
void level_one(){
    
}