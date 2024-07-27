#ifndef DIALFUNCTIONS_H
#define DIALFUNCTIONS_H
#include <windows.h>

extern char **dialogue_buffer;
extern int dialBuff_size, dialPos, isEmpty;

//void reloadDialogue(LPVOID *data);
void printOneDLine();
void loadDialogue();
char* getDialPath();


#endif