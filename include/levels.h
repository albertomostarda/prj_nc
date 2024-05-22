#ifndef LEVELS_H
#define LEVELS_H
#include <ncurses.h>

void afterSignal();
void print_menu(WINDOW *cWin);
void menu(WINDOW *cWin);
void print_settings(WINDOW *cWin);
void settings(WINDOW *cWin);

#endif