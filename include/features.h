#ifndef FEATURES_H
#define FEATURES_H
#include <ncurses.h>


void pause(void);
void start(WINDOW *win);
void run(WINDOW *win);
void artHprint(WINDOW *tmp, int hSize, char**draw, int dHeight);
void Hprint(WINDOW *tmp, char *pText);
void Cprint();
int search();

#endif