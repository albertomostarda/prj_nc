#ifndef LEVELS_H
#define LEVELS_H
#include <ncurses.h>

typedef enum heroRot{UP,DOWN,RIGHT,LEFT}pgRot;
typedef enum actionCode{
        action_START,
        action_IF,
        action_ENDIF,
        action_COND,
        action_WHILE,
        action_DO,
        action_FOR,
        action_FORSTRUCT,
        action_ENDCICLE,
        action_ENDFUNC,
        action_ENDSTART,
        //action_FUNC,
        action_VAR=30
}actionCode;

typedef struct Position{
    int y;
    int x;
} Pos;
typedef struct player{
    chtype icon;
    Pos locate;
    int rotation;
    char **art;
}Hero;

extern WINDOW *map;
extern WINDOW *action;
extern WINDOW *dialogue;
extern Hero pg1;
static int* action_buffer;

void print_menu();
void menu();
void print_settings();
void settings();
void printLvl_one();
void level_one();
#endif