#ifndef INITLEVELS_H
#define INITLEVELS_H
#include "features.h"
#include "levels.h"
#include <ncurses/ncurses.h>

extern char *action_choice[];
extern char *lastVarname;
extern Pos choicePos[4];
extern char *action_codename[];
extern int curAction_size, levelLimitation;
extern fullAction correctAction[18];
extern int auPad, alPad;

char** init_map(int sLevel, int lPad, int uPad );

void init_action();
void bond_action();
void action_run();
void action_subrun(int status,int *EXITflag);



#endif