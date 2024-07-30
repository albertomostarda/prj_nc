#ifndef LEVELS_H
#define LEVELS_H
#include <windows.h>
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
        action_attack,      //9
        action_ENDSTART,    //10
        action_isObstacle,  //11
        action_isEnemy,     //12
        //action_FUNC,
        action_VAR       //13+varVAULUE
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
typedef struct linkVar{
    int type;
    int actIndex;
}linked_var;
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
    //char **art;
} Hero;
// typedef struct passThread{
//     WINDOW *activeWin;
//     int *gLight;
// } ThreadParam;
typedef struct ostile{
    chtype icon;
    Pos location;
} Ostile;


extern WINDOW *map;
extern WINDOW *action;
extern WINDOW *dialogue;
extern Hero pg1;
extern Ostile *enemy;
extern fullVariables correctVar[2];
extern int var_size, curAction_size, enemy_size;
extern int *action_buffer;
extern linked_var *var_buffer;
extern char **mapArr;
extern HANDLE dialogueThread;

void printLvl();
void level_run();
void freeabuffer();
#endif