#ifndef HEROFUNCTIONS_H
#define HEROFUNCTIONS_H
#include <ncurses/ncurses.h>

extern int nSteps, nRot, isWalkEnd;

// int if_run(int condition, int condPos, int *varPos, int *RCond);
int if_run(int nxtPos, int *varPos, int *OnElse);
int cicle_run(int cType,int condition, int condPos, int *varPos);
int enable_else(int cond);
int else_run(int nxtPos, int *varPos, int *fEnable);
//int do_run(int condition, int condPos, int *varPos);
//void for_run(int condition);
void walk();
void rotcclock();
void rotclock();
void set_steps(int value);
void set_turns(int value);
void attack();
int checkEnemy();
int checkObstacle();
int checkNGoal();
int getEndStruct(int posi, int type);
//int getEndCicle(int lsPos);
//void attack_splash();

#endif