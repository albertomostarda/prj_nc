#ifndef FEATURES_H
#define FEATURES_H
#include <windows.h>
#include <ncurses/ncurses.h>

// typedef enum fStatus{fSTART, fRUN} state_t;
// typedef struct cSizes{
//     SHORT con_width;
//     SHORT con_height;
// } ConsoleSize;
//typedef enum customPos{custDEFAULT, custTOP, custBOT} custPos;
//extern WINDOW *win;
extern const int max_path;
extern chtype blank, walls, road, goal;
extern char *pContinue;
extern int sLevel, rStatus, lvlToDo;

void nclearBuff(void);
void myPause(void);
//void handle_resize(int sig); // Da cambiare in caso di passaggio a Windows
void start();
void run();
void stop();
void artHprint(WINDOW *tmp, int hSize, char**draw, int dHeight);
void Hprint(WINDOW *tmp,char *pText, int padding, int forceNL);
char** Hsplit(int HSIZE,char *pText, char **split_txt, int padding, int forceNL, int *nLines);
void Cprint(WINDOW *tmp, char *pText, int Hpad, int vPad, int fNL);
void SBHprint(WINDOW *tmp, char *pText, int padding);
int csearch(char *sample,int start, char find);
char* getPath(); // Da cambiare in caso di passaggio a windows
int fCountLines(FILE *tmpFile);
//int fCountCols(FILE *tmpFile);
void initColors();
// void resize_handler();

#endif