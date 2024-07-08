#ifndef DIALFUNCTIONS_H
#define DIALFUNCTIONS_H
#include <windows.h>

extern char **dialogue_buffer;
extern int dialBuff_size;

void reloadDialogue(LPVOID *data);
void printDialogue();
void loadDialogue();
char* getDialPath();


#endif