/**
 * @file dialfunctions.c
 * @author Alberto Mostarda (mostarda.alberto04@gmail.com)
 * @brief in cui sono presenti le funzioni per la gestione dei dialoghi
 * @version 1.0
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "dialfunctions.h"
#include "levels.h"
#include "features.h"
#include <windows.h>
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <time.h>

char **dialogue_buffer;
int dialBuff_size=0, dialPos=0, isEmpty=1,dReload=0;

/**
 * @brief Funzione che restituisce il percorso del file dei dialoghi.
 * 
 * @return char* 
 */
char* getDialPath(){
    char *pPath=getPath();
    char *fName[]={
        "resources\\dialogueone.txt\0",
        "resources\\dialoguetwo.txt\0",
        "resources\\dialoguethree.txt\0",
        "resources\\dialoguefour.txt\0",
        "resources\\dialoguefive.txt\0"
    };
    char *dialPath=(char *)malloc(max_path);
    strcpy(dialPath, pPath);
    if (dialPath[strlen(dialPath)] != '\\') {
       dialPath[strlen(dialPath)]='\\';
    }
    strcat(dialPath, fName[sLevel-1]);
    return dialPath;
}
/**
 * @brief Funzione che carica da file i dialoghi.
 * 
 */
void loadDialogue(){
    FILE *fp;
    char *pDial=getDialPath(),buffer[2048];
    int dLength=0;
    char *fName[]={
        "resources/dialogueone.txt",
        "resources/dialoguetwo.txt",
        "resources/dialoguethree.txt",
        "resources/dialoguefour.txt",
        "resources/dialoguefive.txt"
    };
    fp=fopen(fName[sLevel-1],"r");
    if(fp==NULL){
        mvwprintw(dialogue,1,1,"Dialoghi non caricati");
        wrefresh(dialogue);
        fclose(fp);
        free(pDial);
        isEmpty=1;
        return ;
    }else
    dialBuff_size = fCountLines(fp);
    dialogue_buffer = (char **)realloc(dialogue_buffer, dialBuff_size * sizeof(char *));
    rewind(fp);
    for(int i = 0; i < dialBuff_size; i++){
        if(fgets(buffer, sizeof(buffer), fp) != NULL){
            dLength = strlen(buffer);
            if(buffer[dLength - 1] == '\n'){
                buffer[dLength - 1] = '\0';
                dLength--;
            }
            dialogue_buffer[i] = (char *)malloc((dLength + 1) * sizeof(char));
            if(dialogue_buffer[i] != NULL){
                strcpy(dialogue_buffer[i], buffer);
                isEmpty=0;
            }
        }
    }
    fclose(fp);
    free(pDial);
}
/**
 * @brief Funzione che stampa una singola linea di dialogo al centro della finestra dei dialoghi.
 * 
 */
void printOneDLine(){
    int maxDY=getmaxy(dialogue)-2, maxDX=getmaxx(dialogue)-1;
    if(isEmpty){
        werase(dialogue);
        box(dialogue,0,0);
        wrefresh(dialogue);
        Cprint(dialogue, "Dialoghi non disponibili",1,1,0);
    }else{
        werase(dialogue);
        box(dialogue,0,0);
        wrefresh(dialogue);
        Cprint(dialogue,dialogue_buffer[dialPos],1,1,0);
        if(dialPos==0){
            mvwprintw(dialogue,maxDY,maxDX-strlen("('N') Prossimo >"),"('N') Prossimo >");
        }else if(dialPos==dialBuff_size-1){
            mvwprintw(dialogue,maxDY,1,"< Precedente ('P')");
        }else{
            mvwprintw(dialogue,maxDY,1,"< Precedente ('P')");
            mvwprintw(dialogue,maxDY,maxDX-strlen("('N') Prossimo >"),"('N') Prossimo >");
        }
        wrefresh(dialogue);
    }
}
/**
 * @brief Funzione che in caso di cambiamento della finestra dei dialoghi, mette in pausa il dialogo presente in quel momento per dieci secondi o fin quando non si preme INVIO ↵.
 * 
 */
void reloadDialogue(){
    time_t countDwn=time(NULL);
    SBHprint(dialogue, pContinue,1);
    nodelay(stdscr,TRUE);
    nclearBuff();
    while(getch()!='\n'&&(time(NULL)-countDwn)>10);
    nclearBuff();
    nodelay(stdscr,FALSE);
    dReload=0;
}