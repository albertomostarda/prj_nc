#ifndef LEVELS_H
#define LEVELS_H
#include <ncurses.h>

typedef enum heroRot{UP,DOWN,RIGHT,LEFT}pgRot;
typedef enum actionCode{
        action_START,       //0
        action_IF,          //1
        action_ENDIF,       //2
        action_SPARENT,     //3
        action_EPARENT,     //4
        action_WHILE,       //5
        action_DO,          //6
        action_FOR,         //7
        action_FORSTRUCT,   //8
        action_ENDCICLE,    //9
        action_ENDFUNC,     //10
        action_WALK,        //11
        action_LROTATE,     //12
        action_RROTATE,     //13
        action_ENDSTART,    //14
        action_isObstacle,  //15
        //action_FUNC,
        action_VAR=40       //
}actionCode;

typedef struct fullact{
    actionCode id;
    char *name;
} fullAction;

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
extern int* action_buffer;

void print_menu();
void menu();
void print_settings();
void settings();
void printLvl_one();
void level_one();
#endif