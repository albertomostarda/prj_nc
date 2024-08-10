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
int alPad=5, auPad=3;
int levelLimitation=0;

char** init_map(int lPad, int uPad){
    FILE *fp;
    char *exePath=getPath();
    // char *fileName[]={
    //     "resources\\levelone.txt",
    //     "resources\\leveltwo.txt",
    //     "resources\\levelthree.txt",
    //     "resources\\levelfour.txt",
    //     "resources\\levelfive.txt"
    // };
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
    // switch (sLevel)
    // {
    //     case 1:
    //         strcpy(fileName, "resources\\levelone.txt");
    //         break;
    //     case 2:
    //         strcpy(fileName, "resources\\leveltwo.txt");
    //         break;
    //     case 3:
    //         strcpy(fileName, "resources\\levelthree.txt");
    //         break;
    //     case 4:
    //         strcpy(fileName, "resources\\levelfour.txt");
    //         break;
    //     case 5:
    //         strcpy(fileName, "resources\\levelfive.txt");
    //         break;
    // }
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
        case 4:
            pg1.rotation=1;
            break;
        case 5:
            pg1.rotation=0;
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
    correctAction[0].name = (char *)realloc(correctAction[0].name,strlen("INIZIO") + 1);
    strcpy(correctAction[0].name, "INIZIO");
    correctAction[0].descr = (char *)realloc(correctAction[0].descr,strlen("Si utilizza per indicare l'inizio del programma.") + 1);
    strcpy(correctAction[0].descr, "Si utilizza per indicare l'inizio del programma.");
    correctAction[1].name = (char *)realloc(correctAction[1].name,strlen("SE") + 1);
    strcpy(correctAction[1].name, "SE");
    correctAction[1].descr = (char *)realloc(correctAction[1].descr,strlen("Se la condizione e' VERA o FALSA, esegue il codice al suo interno.") + 1);
    strcpy(correctAction[1].descr, "Se la condizione e' VERA o FALSA, esegue il codice al suo interno.");
    correctAction[2].name = (char *)realloc(correctAction[2].name,strlen("FINE_SE") + 1);
    strcpy(correctAction[2].name, "FINE_SE");
    correctAction[2].descr = (char *)realloc(correctAction[2].descr,strlen("Serve per chiudere il codice che fa parte del 'SE'.") + 1);
    strcpy(correctAction[2].descr, "Serve per chiudere il codice che fa parte del 'SE'.");
    correctAction[3].name = (char *)realloc(correctAction[3].name,strlen("ALTRIMENTI") + 1);
    strcpy(correctAction[3].name, "ALTRIMENTI");
    correctAction[3].descr = (char *)realloc(correctAction[3].descr,strlen("Viene usato dopo aver chiuso il 'SE' (dopo il FINE_SE). Se la condizione del 'SE' e' FALSA viene eseguito il suo codice.") + 1);
    strcpy(correctAction[3].descr, "Viene usato dopo aver chiuso il 'SE' (dopo il FINE_SE). Se la condizione del 'SE' e' FALSA viene eseguito il suo codice.");
    correctAction[4].name = (char *)realloc(correctAction[4].name,strlen("FINE_ALTRIMENTI") + 1);
    strcpy(correctAction[4].name, "FINE_ALTRIMENTI");
    correctAction[4].descr = (char *)realloc(correctAction[4].descr,strlen("Serve per chiudere il codice che fa parte dell' 'ALTRIMENTI'.") + 1);
    strcpy(correctAction[4].descr, "Serve per chiudere il codice che fa parte dell' 'ALTRIMENTI'.");
    correctAction[5].name = (char *)realloc(correctAction[5].name,strlen("MENTRE") + 1);
    strcpy(correctAction[5].name, "MENTRE");
    correctAction[5].descr = (char *)realloc(correctAction[5].descr,strlen("Il codice al suo interno verra' ripetuto fin quando la condizione e' VERA.") + 1);
    strcpy(correctAction[5].descr, "Il codice al suo interno verra' ripetuto fin quando la condizione e' VERA.");
    correctAction[6].name = (char *)realloc(correctAction[6].name,strlen("FAI") + 1);
    strcpy(correctAction[6].name, "FAI MENTRE");
    correctAction[6].descr = (char *)realloc(correctAction[6].descr,strlen("Il codice all'interno viene eseguito almeno una volta e poi se la condizione e' VERA verra' ripetuto.") + 1);
    strcpy(correctAction[6].descr, "Il codice all'interno viene eseguito almeno una volta e poi se la condizione e' VERA verra' ripetuto.");
    correctAction[7].name = (char *)realloc(correctAction[7].name,strlen("FINE_CICLO") + 1);
    strcpy(correctAction[7].name, "FINE_CICLO");
    correctAction[7].descr = (char *)realloc(correctAction[7].descr,strlen("Serve per chiudere il codice che fa parte del 'MENTRE', 'FAI'.") + 1);
    strcpy(correctAction[7].descr, "Serve per chiudere il codice che fa parte del 'MENTRE', 'FAI'.");
    correctAction[8].name = (char *)realloc(correctAction[8].name,strlen("cammina") + 1);
    strcpy(correctAction[8].name, "cammina");
    correctAction[8].descr = (char *)realloc(correctAction[8].descr,strlen("Funzione che permette al personaggio di camminare.") + 1);
    strcpy(correctAction[8].descr, "Funzione che permette al personaggio di camminare.");
    correctAction[9].name = (char *)realloc(correctAction[9].name,strlen("ruota_antiorario") + 1);
    strcpy(correctAction[9].name, "ruota_antiorario");
    correctAction[9].descr = (char *)realloc(correctAction[9].descr,strlen("Funzione che permette al personaggio di ruotare verso sinistra.") + 1);
    strcpy(correctAction[9].descr, "Funzione che permette al personaggio di ruotare verso sinistra.");
    correctAction[10].name = (char *)realloc(correctAction[10].name,strlen("ruota_orario") + 1);
    strcpy(correctAction[10].name, "ruota_orario");
    correctAction[10].descr = (char *)realloc(correctAction[10].descr,strlen("Funzione che permette al personaggio di ruotare verso destra.") + 1);
    strcpy(correctAction[10].descr, "Funzione che permette al personaggio di ruotare verso destra.");
    correctAction[11].name = (char *)realloc(correctAction[11].name,strlen("Attacca") + 1);
    strcpy(correctAction[11].name, "Attacca");
    correctAction[11].descr = (char *)realloc(correctAction[11].descr,strlen("Attacca il nemico togliendogli un punto vita.") + 1);
    strcpy(correctAction[11].descr, "Attacca il nemico togliendogli un punto vita.");
    correctAction[12].name = (char *)realloc(correctAction[12].name,strlen("FINE_PROGRAMMA") + 1);
    strcpy(correctAction[12].name, "FINE_PROGRAMMA");
    correctAction[12].descr = (char *)realloc(correctAction[12].descr,strlen("Si utilizza per terminare il programma.") + 1);
    strcpy(correctAction[12].descr, "Si utilizza per terminare il programma");
    correctAction[13].name = (char *)realloc(correctAction[13].name,strlen("BLOCCATO") + 1);
    strcpy(correctAction[13].name, "BLOCCATO");
    correctAction[13].descr = (char *)realloc(correctAction[13].descr,strlen("Condizione che e' VERA se il personaggio e' bloccato.") + 1);
    strcpy(correctAction[13].descr, "Condizione che e' VERA se il personaggio e' bloccato.");
    correctAction[14].name = (char *)realloc(correctAction[14].name,strlen("E' UN NEMICO?!?") + 1);
    strcpy(correctAction[14].name, "E' UN NEMICO?!?");
    correctAction[14].descr = (char *)realloc(correctAction[14].descr,strlen("Controlla se nel blocco successivo c'e' un nemico. Restituisce VERO se c'e' il nemico, senno' e' FALSO.") + 1);
    strcpy(correctAction[14].descr, "Controlla se nel blocco successivo c'e' un nemico. Restituisce VERO se c'e' il nemico, senno' e' FALSO.");
    correctAction[15].name = (char *)realloc(correctAction[15].name,strlen("La Fine non e' Giunta") + 1);
    strcpy(correctAction[15].name, "La Fine non e' Giunta");
    correctAction[15].descr = (char *)realloc(correctAction[15].descr,strlen("Condizione che controlla se si e' arrivati al traguardo (rettangolo VERDE).") + 1);
    strcpy(correctAction[15].descr, "Condizione che controlla se si e' arrivati al traguardo (rettangolo VERDE).");

    correctAction[16].name = (char *)realloc(correctAction[16].name,strlen("Variabile") + 1);
    strcpy(correctAction[16].name, "Variabile");
    correctAction[16].descr = (char *)realloc(correctAction[16].descr,strlen("Contenitore di valori (numeri).") + 1);
    strcpy(correctAction[16].descr, "Contenitore di valori (numeri).");
}
void bondVar(){
    correctVar[0].id=var_nSteps;
    correctVar[0].name=(char *)malloc(strlen("nPassi")+1);
    strcpy(correctVar[0].name, "Passi");
    correctVar[0].descr=(char *)malloc(strlen("Variabile che indica quanti passi deve fare il personaggio.")+1);
    strcpy(correctVar[0].descr,"Variabile che indica quanti passi deve fare il personaggio.");
    correctVar[1].id=var_nTurns;
    correctVar[1].name=(char *)malloc(strlen("nGiri")+1);
    strcpy(correctVar[1].name, "Giri");
    correctVar[1].descr=(char *)malloc(strlen("Variabile che indica quanti giri deve fare il personaggio.")+1);
    strcpy(correctVar[1].descr,"Variabile che indica quanti giri deve fare il personaggio.");
}
void init_action(){
    int vSize=0,hSize=0;
    curAction_size=1;
    bond_action();
    bondVar();
    action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
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
        default:
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
void free_actionBND(){
    for(int i=0;i<12;i++){
        free(correctAction[i].descr);
        free(correctAction[i].name);
    }
}
void free_varBND(){
    for(int i=0;i<2;i++){
        free(correctVar[i].name);
        free(correctVar[i].descr);
    }
}