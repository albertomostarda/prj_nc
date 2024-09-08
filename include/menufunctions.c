/**
 * @file menufunctions.c
 * @author Alberto Mostarda (mostarda.alberto04@gmail.com)
 * @brief Libreria in cui sono presenti le funzioni per il funzionamento del menu principale e il caricamento e salvataggio dei progressi
 * @version 1.0
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "menufunctions.h"
#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#include <string.h>
#include <time.h>

int menupos_ch[3], selectpos[5];
static char* menu_choice[]={"[NUOVA PARTITA]","[SELEZIONA LIVELLO]","[ESCI]"};
static char* lvl_choice[]={"Livello 1","Livello 2","Livello 3","Livello 4","Livello 5"};
static char* logo[]={
"   _____          _                    _                 _                  ",
"  / ____|        | |          /\\      | |               | |                 ",
" | |     ___   __| | ___     /  \\   __| |_   _____ _ __ | |_ _   _ _ __ ___ ",
" | |    / _ \\ / _` |/ _ \\   / /\\ \\ / _` \\ \\ / / _ \\ '_ \\| __| | | | '__/ _ \\",
" | |___| (_) | (_| |  __/  / ____ \\ (_| |\\ V /  __/ | | | |_| |_| | | |  __/",
"  \\_____\\___/ \\__,_|\\___| /_/    \\_\\__,_| \\_/ \\___|_| |_|\\__|\\__,_|_|  \\___|"
};

/**
 * @brief Funzione che carica, se esistono, gli ultimi progressi salvati.
 * 
 */
void loadSaves(){
    //se i livelli saranno piu di 9 modificare grandezza lvltxt e terminatore
    char *path=getPath(), lvltxt[2];
    int nLenght=strlen(path)+strlen("\\saves\\save.sav");
    path=(char *)realloc(path,nLenght*sizeof(char));
    strcat(path, "\\saves\\save.sav");
    FILE *fp=fopen(path,"r");
    if(fp!=NULL){
        werase(stdscr);
        fgets(lvltxt,sizeof(lvltxt),fp);
        lvltxt[1]='\0';
        lvlToDo=atoi(lvltxt);
        fclose(fp);
        free(path);
    }else{
        fclose(fp);
    }
}
/**
 * @brief Funzione che crea un salvataggio dei progressi effettuati.
 * 
 */
void createSaves(){
    char *path=getPath();
    int nLenght=strlen(path)+strlen("\\saves\\save.sav");
    path=(char *)realloc(path,nLenght*sizeof(char));
    strcat(path, "\\saves\\save.sav");
    FILE *fp=fopen(path,"w");
    fprintf(fp,"%d\0",lvlToDo);
    fclose(fp);
    free(path);
}
/**
 * @brief Funzione che inizializza il menu.
 * 
 */
void init_menu(){
    int midScr=getmaxx(stdscr)/2,midCPos=(getmaxy(stdscr)/2)+2;
    if(lvlToDo==0){
        loadSaves();
    }
    werase(stdscr);
    box(stdscr,0,0);
    artHprint(stdscr,160,logo,6);
    menupos_ch[0]=midCPos-4;
    menupos_ch[1]=midCPos;
    menupos_ch[2]=midCPos+4;
    mvwprintw(stdscr,menupos_ch[0],midScr-(strlen(menu_choice[0])/2),"%s",menu_choice[0]);
    mvwprintw(stdscr,menupos_ch[1],midScr-(strlen(menu_choice[1])/2),"%s",menu_choice[1]);
    mvwprintw(stdscr,menupos_ch[2],midScr-(strlen(menu_choice[2])/2),"%s",menu_choice[2]);
    wrefresh(stdscr);
}
/**
 * @brief Funzione che permette al menu di funzionare.
 * 
 * @param quit 
 */
void menu(int *quit){
    int midScr=getmaxx(stdscr)/2,rMenu=1, highlight=0,menuch=0;
    keypad(stdscr,TRUE);
    while(rMenu){
        for(int i=0;i<3;i++){
            if(i==highlight){
                wattron(stdscr, A_REVERSE);
                mvwprintw(stdscr,menupos_ch[i],midScr-(strlen(menu_choice[i])/2),"%s",menu_choice[i]);
                wattroff(stdscr, A_REVERSE);
            }else{
                mvwprintw(stdscr,menupos_ch[i],midScr-(strlen(menu_choice[i])/2),"%s",menu_choice[i]);
            }
        }
        nclearBuff();
        menuch=getch();
        nclearBuff();
        switch (menuch)
        {
            case 'w':
            case 'W':
            case KEY_UP:
                if(highlight==0){
                    highlight=2;
                }else{
                    highlight--;
                }
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                if(highlight==2){
                    highlight=0;
                }else{
                    highlight++;
                }
                break;
            case '\n':
                menu_subrun(highlight, quit, &rMenu);
                break;
        }
    }
    keypad(stdscr,FALSE);
    return;
}
/**
 * @brief Funzione che esegue l’opzione selezionata nel menu.
 * 
 * @param mMode 
 * @param pExit 
 * @param lvlPass 
 */
void menu_subrun(int mMode, int *pExit, int *lvlPass){
    switch(mMode){
        case 0:
            lvlToDo=0;
            createSaves();
            *lvlPass=0;
            sLevel=1;
            rStatus=2;
            break;
        case 1:
            if(lvlToDo>1){
                init_selectLvl();
                selectLvl(lvlPass);
            }else{
                time_t cWait=time(NULL);
                werase(stdscr);
                box(stdscr,0,0);
                Cprint(stdscr, "Devi cominciare una nuova partita prima di selezionare un livello!",1,1,1);
                wmove(stdscr, getcury(stdscr)+1, getcurx(stdscr));
                Hprint(stdscr, pContinue, 1,0);
                nclearBuff();
                nodelay(stdscr, TRUE);
                while(getch()!='\n'&&(time(NULL)-cWait)<10);
                nodelay(stdscr, FALSE);
                nclearBuff();
                *lvlPass=0;
            }
            break;
        case 2:
            werase(stdscr);
            box(stdscr,0,0);
            Cprint(stdscr, "Arrivederci!",1,1,0);
            SBHprint(stdscr,"Premi un tasto qualsiasi per continuare",1);
            nclearBuff();
            getch();
            nclearBuff();
            *lvlPass=0;
            *pExit=0;
            break;
    }
}
/**
 * @brief Funzione che inizializza il menu della scelta del livello.
 * 
 */
void init_selectLvl(){
    int midScr=getmaxx(stdscr)/2, midPos=getmaxy(stdscr)/2,idx=0,fPrint=1;
    werase(stdscr);
    box(stdscr, 0,0);
    for(int i=-2;i<3;i++){
        selectpos[idx]=midPos+(i*4);
        idx++;
    }
    for(int i=0;i<lvlToDo;i++){
        mvwprintw(stdscr, selectpos[i], midScr-(strlen(lvl_choice[i])/2),"%s", lvl_choice[i]);
    }
}
/**
 * @brief Funzione che permette alla selezione del livello di poter funzionare.
 * 
 * @param rQuit 
 */
void selectLvl(int *rQuit){
    int fBreak=1, focus=0, choice=0, midScr=getmaxx(stdscr)/2;
    while(fBreak)
    {
        for(int i=0;i<lvlToDo;i++){
            if(i==focus){
                wattron(stdscr, A_REVERSE);
                mvwprintw(stdscr, selectpos[i], midScr-(strlen(lvl_choice[i])/2),"%s",lvl_choice[i]);
                wattroff(stdscr, A_REVERSE);
            }else{
                mvwprintw(stdscr, selectpos[i], midScr-(strlen(lvl_choice[i])/2),"%s",lvl_choice[i]);
            }
        }
        nclearBuff();
        choice=getch();
        nclearBuff();
        switch (choice)
        {
            case 'W':
            case 'w':
            case KEY_UP:
                if(focus==0){
                    focus=lvlToDo-1;
                }else{
                    focus--;
                }
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                if(focus==lvlToDo-1){
                    focus=0;
                }else{
                    focus++;
                }
                break;
            case 'q':
            case 'Q':
                init_menu();
                fBreak=0;
                break;
            case '\n':
                selectLvl_subrun(focus+1);
                rStatus=2;
                fBreak=0;
                *rQuit=0;
                break;     
        }
    }
}
/**
 * @brief Funzione che esegue l’opzione selezionata nel menu della selezione del livello.
 * 
 * @param mode 
 */
void selectLvl_subrun(int mode){
    switch(mode){
        case 1:
            sLevel=1;
            break;
        case 2:
            sLevel=2;
            break;
        case 3:
            sLevel=3;
            break;
        case 4:
            sLevel=4;
            break;
        case 5:
            sLevel=5;
            break;
    }
}