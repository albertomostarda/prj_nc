#include "initlevels.h"
#include "features.h"
#include "levels.h"
#include "levelsfunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses/ncurses.h>

char *action_choice[]={"INSERISCI","ELIMINA","ESEGUI","ESCI"};
fullAction correctAction[17];
Pos choicePos[4];
int alPad=5, auPad=3, isStart;
int levelLimitation=0;

char** init_map(int lPad, int uPad){
    FILE *fp;
    char *exePath=getPath();
    char *fileName[]={
        "resources/levelone.txt",
        "resources/leveltwo.txt",
        "resources/levelthree.txt",
        "resources/levelfour.txt",
        "resources/levelfive.txt"
    };
    char buffer[160];
    char *fullpath=(char*)malloc(max_path);
    for(int i=0;i<max_path;i++){
        fullpath[i]='\0';
    }
    int fLines=0, fCols=0,wBegy=0, wBegx=0, lenght=0;
    strcat(fullpath, exePath);
    if (fullpath[strlen(fullpath)]!='\\')
    {
        fullpath[strlen(fullpath)]='\\';
    }
    strcat(fullpath,fileName[sLevel-1]);
    fp=fopen(fileName[sLevel-1],"r");
    if(fp==NULL){
        mvwprintw(dialogue, 1,1, "File non trovato");
        wrefresh(dialogue);
        free(fullpath);
        return 0;
        //aggiungere chiusura/ritorno al Menu
    }
    fLines=fCountLines(fp);
    //fCols=fCountCols(fp);
    char **Mmap=(char**)malloc(fLines*sizeof(char*));
    if(Mmap ==NULL){
        fclose(fp);
        free(fullpath);
        return NULL;
    }
   for (int i = 0; i < fLines; i++) {
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            lenght = strlen(buffer);
            if(buffer[lenght-1]=='\n'){
                buffer[lenght-1]='\0';
            }
            Mmap[i] = (char*)malloc(lenght * sizeof(char));
            if (Mmap[i] != NULL) {
                strcpy(Mmap[i], buffer);
            }
        }
    }
    // mvwprintw(dialogue, 1,1, "array creato");
    // wrefresh(dialogue);
    // getch();
    free(fullpath);
    fclose(fp);
    getbegyx(map,wBegy,wBegy);
    switch(sLevel){
        case 1:
        case 2:
        case 3:
        case 5:
            pg1.rotation=0;
            break;
        case 4:
            pg1.rotation=1;
            break;
    }
    for(int i=0;i<fLines;i++){
        wmove(map,wBegy+uPad+i,wBegx+lPad);
        printcolor_str(map,Mmap[i], strlen(Mmap[i]), i);
        wrefresh(map);
        napms(100);
    }
    return Mmap;
}
void bond_action(){
    actionCode i=0;
    for(int idx=0;idx<17;i++,idx++){
        correctAction[idx].id=i;
    }
    strcpy(correctAction[0].name, "INIZIO");
    strcpy(correctAction[0].descr, "Si utilizza per indicare l'inizio del programma.");
    strcpy(correctAction[1].name, "SE");
    strcpy(correctAction[1].descr, "Se la condizione e' VERA o FALSA, esegue il codice al suo interno.");
    strcpy(correctAction[2].name, "FINE_SE");
    strcpy(correctAction[2].descr, "Serve per chiudere il codice che fa parte del 'SE'.");
    strcpy(correctAction[3].name, "ALTRIMENTI");
    strcpy(correctAction[3].descr, "Viene usato dopo aver chiuso il 'SE'. Se la condizione del 'SE' e' FALSA viene eseguito il suo codice.");
    strcpy(correctAction[4].name, "FINE_ALTRIMENTI");
    strcpy(correctAction[4].descr, "Serve per chiudere il codice che fa parte dell' 'ALTRIMENTI'.");
    strcpy(correctAction[5].name, "MENTRE");
    strcpy(correctAction[5].descr, "Il codice al suo interno verra' ripetuto fin quando la condizione e' VERA.");
    strcpy(correctAction[6].name, "FAI MENTRE");
    strcpy(correctAction[6].descr, "Il codice all'interno viene eseguito almeno una volta e poi se la condizione e' VERA verra' ripetuto.");
    strcpy(correctAction[7].name, "FINE_CICLO");
    strcpy(correctAction[7].descr, "Serve per chiudere il codice che fa parte del 'MENTRE', 'FAI'.");
    strcpy(correctAction[8].name, "cammina");
    strcpy(correctAction[8].descr, "Funzione che permette al personaggio di camminare.");
    strcpy(correctAction[9].name, "ruota_antiorario");
    strcpy(correctAction[9].descr, "Funzione che permette al personaggio di ruotare verso sinistra.");
    strcpy(correctAction[10].name, "ruota_orario");
    strcpy(correctAction[10].descr, "Funzione che permette al personaggio di ruotare verso destra.");
    strcpy(correctAction[11].name, "Attacca");
    strcpy(correctAction[11].descr, "Attacca il nemico togliendogli un punto vita.");
    strcpy(correctAction[12].name, "FINE_PROGRAMMA");
    strcpy(correctAction[12].descr, "Si utilizza per terminare il programma.");
    strcpy(correctAction[13].name, "BLOCCATO");
    strcpy(correctAction[13].descr, "Condizione che e' VERA se il personaggio e' bloccato.");
    strcpy(correctAction[14].name, "E' UN NEMICO?!?");
    strcpy(correctAction[14].descr, "Controlla se nel blocco successivo c'e' un nemico.");
    strcpy(correctAction[15].name, "La Fine non e' Giunta");
    strcpy(correctAction[15].descr, "Condizione che controlla se si e' arrivati al traguardo."); 
    strcpy(correctAction[16].name, "Variabile");
    strcpy(correctAction[16].descr, "Contenitore di valori (numeri).");
}
void bondVar(){
    correctVar[0].id = var_nSteps;
    strcpy(correctVar[0].name, "Passi");
    strcpy(correctVar[0].descr, "Variabile che indica quanti passi deve fare il personaggio.");
    correctVar[1].id = var_nTurns;
    strcpy(correctVar[1].name, "Giri");
    strcpy(correctVar[1].descr, "Variabile che indica quanti giri deve fare il personaggio.");
}
void init_action(){
    int vSize=0,hSize=0;
    curAction_size=1;
    // free_actionBND();
    bond_action();
    // free_varBND();
    bondVar();
    action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
    if(action_buffer == NULL){
        free(action_buffer);
        action_buffer=NULL;
        action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
    }
    getmaxyx(action,vSize,hSize);
    action_buffer[0]=action_START;
    levelLimitation=1;
    switch (sLevel)
    {
        case 1:
        case 2:
        case 3:
            curAction_size++;
            var_size=1;
            action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
            action_buffer[1]=action_VAR+2;
            var_buffer=(linked_var *)realloc(var_buffer, var_size*sizeof(linked_var));
            var_buffer[0].type=var_nSteps;
            var_buffer[0].actIndex=curAction_size-1;
            mvwprintw(action, auPad+1, alPad+3, "%s = %d;", correctVar[var_buffer[0].type].name,action_buffer[1]-action_VAR);
            levelLimitation=2;
            break;
        case 4:
        case 5:
            curAction_size++;
            var_size=1;
            action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
            action_buffer[1]=action_VAR+1;
            var_buffer=(linked_var *)realloc(var_buffer, var_size*sizeof(linked_var));
            var_buffer[0].type=var_nSteps;
            var_buffer[0].actIndex=curAction_size-1;
            mvwprintw(action, auPad+1, alPad+3, "%s = %d;", correctVar[var_buffer[0].type].name,action_buffer[1]-action_VAR);
            levelLimitation=2;
            break;
    }
    mvwprintw(action, auPad, alPad, "INIZIO");
    choicePos[0].y=vSize-2;
    choicePos[1].y=vSize-2;
    choicePos[2].y=vSize-4;
    choicePos[3].y=vSize-2;
    choicePos[0].x=auPad+5;
    choicePos[1].x=auPad+22;
    choicePos[2].x=auPad+22;
    choicePos[3].x=auPad+37;
    mvwprintw(action, choicePos[0].y, choicePos[0].x, "%s", action_choice[0]);
    mvwprintw(action, choicePos[1].y, choicePos[1].x, "%s", action_choice[1]);
    mvwprintw(action, choicePos[2].y, choicePos[2].x, "%s", action_choice[2]);
    mvwprintw(action, choicePos[3].y, choicePos[3].x, "%s", action_choice[3]);
    wrefresh(action);
}