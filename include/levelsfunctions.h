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
void action_add();
void addone();
//int check_Econdition(int lastPos);
int conditionError(int lastPos);
void ifError();
int endError();
void run_actions();
void delete_action(int lim);
void run_anim(WINDOW *tmp);
void print_map(WINDOW *tmp);
#endif
