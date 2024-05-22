#ifndef FEATURES_H
#define FEATURES_H
#include <ncurses.h>


void pause(void);
void start(WINDOW *win);
void run(WINDOW *win);
void artHprint(WINDOW *tmp, int hSize, char**draw, int dHeight);
void Hprint(WINDOW *tmp, char *pText, int padding, int forceNL);
void Cprint(WINDOW *tmp, char *pText, int Hpad, int vPad, int fNL);
int csearch(char *sample,int start, char find);
char *strcopy(char *sample, int start, int cpSize);

#endif