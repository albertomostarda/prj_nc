#ifndef LEVELS_H
#define LEVELS_H
#include <ncurses.h>

typedef struct Position{
    int y;
    int x;
} Pos;
struct Hero{
    char icon;
    Pos locate;
    char **art;
};


void afterSignal();
void print_menu();
void menu();
void print_settings();
void settings();
void print_map(int sLevel);
void printLvl_one();
void level_one();

#endif