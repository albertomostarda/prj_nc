#ifndef HEROFUNCTIONS_H
#define HEROFUNCTIONS_H
#include <ncurses/ncurses.h>

extern int nSteps, nRot;

int if_run(int condition, int condPos);
void while_run(int condition);
void do_run(int condition);
void for_run(int condition);
void walk();
void rotcclock();
void rotclock();
void set_steps(int value);
int checkObstacle();
int getEndif(int posi);

#endif