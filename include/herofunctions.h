#ifndef HEROFUNCTIONS_H
#define HEROFUNCTIONS_H
#include <ncurses/ncurses.h>

extern int nSteps, nRot, isWalkEnd;

int if_run(int condition, int condPos);
int while_run(int condition, int condPos);
int do_run(int condition, int condPos);
//void for_run(int condition);
void walk();
void rotcclock();
void rotclock();
void set_steps(int value);
int attack();
int checkEnemy();
int checkObstacle();
int getEndif(int posi);
void attack_splash();

#endif