#ifndef LEVELSFUNCTIONS_H
#define LEVELSFUNCTIONS_H
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printcolor_str(WINDOW *tWin, char *colStr, int pLines, int tmpY);
void printcolor_char(WINDOW *tWin,char ch, int locX, int locY);
void print_action();
void print_add(int *limitact, int limit_size);
//void action_add();
void action_run();
void action_subrun(int status, int *EXITflag);
void addone();
void addVar(int *qAdd);
void print_addVar(int *var_limited, int lVar_size);
int addValue();
void print_addValue(int *val_limited, int lVal_size);
int *createAlimit(int *limSize);
//int check_Econdition(int lastPos);
void run_actions(int *fexit);
void delete_action(int lim);
void run_anim(WINDOW *tmp);
void print_map(WINDOW *tmp);
void setRotation(int isEnd);
int checkEndLvl();
#endif
