#ifndef INITLEVELS_H
#define INITLEVELS_H
#include "features.h"
#include "levels.h"
#include <ncurses/ncurses.h>

extern char *action_choice[];
extern Pos choicePos[4];
extern char *action_codename[];
extern int levelLimitation;
extern fullAction correctAction[16];
extern int auPad, alPad;

void init_menu();
char** init_map(int lPad, int uPad );
void init_action();
void bond_action();
void bondVar();
void action_subrun(int status,int *EXITflag);
void free_actionBND();
void free_varBND();

#endif