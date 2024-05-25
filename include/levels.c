#include "levels.h"
#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct Position{
    int y;
    int x;
} Pos;

static struct Hero{
    char icon;
    Pos locate;
    char **art;
};

void menu(){
    return;
}

void printLvl1(){
    werase(win);
    WINDOW *map=newwin(24,110,0,0);
    WINDOW *action=newwin(35,60,0,110);
    WINDOW *dialogue=newwin(11,110,24,0);
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
void level1(){
    
}