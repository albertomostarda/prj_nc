#ifndef LEVELSFUNCTION_H
#define LEVELSFUNCTION_H
#include <ncurses.h>

void printcolor_str(WINDOW *tWin, char *colStr, int pLines);
void printcolor_char(WINDOW *tWin,char ch);
void print_action();
void print_add(int *limitact, int limit_size);
void action_add();
void addone();
void add_run(int *limit, int limit_size); //sostituire a alla riga 240  
//int check_Econdition(int lastPos);
int conditionError(int lastPos);
void delete_action();
#endif
