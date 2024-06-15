#ifndef LEVELS_H
#define LEVELS_H
#include <ncurses/ncurses.h>

//pulire mapArr

typedef enum heroRot{UP,DOWN,RIGHT,LEFT}pgRot;
typedef enum actionCode{
        action_START,       //0
        action_IF,          //1
        action_ENDIF,       //2
        action_WHILE,       //3
        action_DO,          //4
        action_FOR,         //5
        action_FORSTRUCT,   //6
        action_ENDCICLE,    //7
        //action_ENDFUNC,     
        action_WALK,        //8
        action_LROTATE,     //9
        action_RROTATE,     //10
        action_ENDSTART,    //11
        action_isObstacle,  //12
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
extern char **mapArr;

void print_menu();
void menu();
void print_settings();
void settings();
void printLvl_one();
void level_one();
void freeabuffer();
#endif