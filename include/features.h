#ifndef FEATURES_H
#define FEATURES_H
#include <ncurses.h>

typedef enum fStatus{fSTART, fRUN} state_t;
//typedef enum customPos{custDEFAULT, custTOP, custBOT} custPos;
extern WINDOW *win;


void pause(void);
void handle_resize(int sig);
void start();
void run();
void artHprint(WINDOW *tmp, int hSize, char**draw, int dHeight);
//void Hprint(WINDOW *tmp, char *pText, int padding, int forceNL);
void Cprint(WINDOW *tmp, char *pText, int Hpad, int vPad, int fNL, int nHline);
void SBHprint(WINDOW *tmp, char *pText, int padding);
int csearch(char *sample,int start, char find);

#endif