#ifndef LEVELS_H
#define LEVELS_H
#include <ncurses/ncurses.h>

//pulire mapArr

typedef enum heroRot{UP,DOWN,RIGHT,LEFT}pgRot;
typedef enum actionCode{
        action_START,       //0
        action_IF,          //1
        action_ENDIF,       //2
        //action_ELSE,
        //action_ENDELSE,
        action_WHILE,       //3
        action_DO,          //4
        //action_FOR,         //
        //action_FORSTRUCT,   //
        action_ENDCICLE,    //5
        //action_ENDFUNC,     
        action_WALK,        //6
        action_LROTATE,     //7
        action_RROTATE,     //8
        action_ENDSTART,    //9
        action_isObstacle,  //10
        //action_FUNC,
        action_VAR=40       //11+varVAULUE
}actionCode;
typedef enum varCode{
    var_nSteps,
    var_nTurns
}varCode;
typedef struct fullvar{
    varCode id;
    char *name;
    char *descr;
}fullVariables;
typedef struct fullact{
    actionCode id;
    char *name;
    char *descr;
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
} Hero;

extern WINDOW *map;
extern WINDOW *action;
extern WINDOW *dialogue;
extern Hero pg1;
extern fullVariables correctVar[2];
extern int var_size, curAction_size;
extern int *action_buffer, *var_buffer;
extern char **mapArr;

void printLvl();
void level_run();
void freeabuffer();
#endif