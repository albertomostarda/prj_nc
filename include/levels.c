/**
 * @file levels.c
 * @author Alberto Mostarda (mostarda.alberto04@gmail.com)
 * @brief in cui sono presenti le funzioni e le strutture di dati riguardanti i livelli
 * @version 1.0
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "levels.h"
#include "features.h"
#include "initlevels.h"
#include "levelsfunctions.h"
#include "dialfunctions.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses/ncurses.h>
#include <time.h>

WINDOW *map;
WINDOW *action;
WINDOW *dialogue;
char **mapArr;
int* action_buffer;
linked_var *var_buffer;
int curAction_size, var_size=2, enemy_size=0;
Hero pg1;
Ostile *enemy=NULL;
fullVariables correctVar[2];
// HANDLE dialogueThread;
chtype blank=219|COLOR_PAIR(5);
chtype walls=219|COLOR_PAIR(2);
// chtype enemy=219|COLOR_PAIR(3);
chtype road=219|COLOR_PAIR(4);
chtype goal=219|COLOR_PAIR(6);

/**
 * @brief Funzione che permette la corretta stampa del livello.
 * 
 */
void printLvl(){
    //ThreadParam passingTd;
    map=newwin(24,110,0,0);
    action=newwin(35,50,0,110);
    dialogue=newwin(11,110,24,0);
    // passingTd.activeWin=dialogue;
    // passingTd.gLight=&needDReload;
    wrefresh(map);
    wrefresh(action);
    wrefresh(dialogue);
    box(map, 0,0);
    box(action, 0,0);
    box(dialogue,0,0);
    wrefresh(map);
    wrefresh(action);
    wrefresh(dialogue);
    //enemy.icon=219|COLOR_PAIR(3);
    mapArr=init_map(26,1);
    init_action();
    loadDialogue();
    dialPos=0;
    printOneDLine();
    //dialogueThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) reloadDialogue, &passingTd,0,NULL);
}
/**
 * @brief Funzione che permette l’esecuzione del livello.
 * 
 */
void level_run(){
    action_run();
}