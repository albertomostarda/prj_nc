#ifndef LEVELFUNCTIONS_H
#define LEVELFUNCTIONS_H
#include "features.h"
#include "levels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

extern char *action_choice[];
extern Pos choicePos[4];
extern char *action_codename[];


char** print_map(int sLevel, int lPad, int uPad );
void printcolor_str(WINDOW *tWin, char *colStr, int pLines);
void printcolor_char(WINDOW *tWin,char ch);
void init_action();
void bond_action();
void print_action();
void action_run();
void action_subrun(int status,int *EXITflag);
void print_add(int *limitact, int limit_size);
void action_add();
void addone();


#endif