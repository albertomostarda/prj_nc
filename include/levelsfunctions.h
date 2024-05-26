#ifndef LEVELFUNCTIONS_H
#define LEVELFUNCTIONS_H
#include "features.h"
#include "levels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


char** print_map(int sLevel, int lPad, int uPad );
void printcolor_str(WINDOW *tWin, char *colStr, int pLines);
void printcolor_char(WINDOW *tWin,char ch);
void init_action(int sLevel, int lPad, int uPad);

#endif