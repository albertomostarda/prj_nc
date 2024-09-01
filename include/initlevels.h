#ifndef INITLEVELS_H
#define INITLEVELS_H
#include "features.h"
#include "levels.h"
#include <ncurses/ncurses.h>

extern char *action_choice[];
extern Pos choicePos[4];
extern char *action_codename[];
extern int levelLimitation;
extern fullAction correctAction[17];
extern int auPad, alPad, isStart;

char** init_map(int lPad, int uPad );
void init_action();
void bond_action();
void bondVar();
// void free_actionBND();
// void free_varBND();

#endif