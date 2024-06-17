#include "menufunctions.h"
#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#include <string.h>

int midCPos, fSelect;
int lvlCompleted=0;
int menupos_ch[3];
static char* menu_choice[]={"[NUOVA PARTITA]","[SELEZIONA LIVELLO]","[ESCI]"};
static char* logo[]={
"   _____          _                    _                 _                  ",
"  / ____|        | |          /\\      | |               | |                 ",
" | |     ___   __| | ___     /  \\   __| |_   _____ _ __ | |_ _   _ _ __ ___ ",
" | |    / _ \\ / _` |/ _ \\   / /\\ \\ / _` \\ \\ / / _ \\ '_ \\| __| | | | '__/ _ \\",
" | |___| (_) | (_| |  __/  / ____ \\ (_| |\\ V /  __/ | | | |_| |_| | | |  __/",
"  \\_____\\___/ \\__,_|\\___| /_/    \\_\\__,_| \\_/ \\___|_| |_|\\__|\\__,_|_|  \\___|"
};

int loadSaves(){
    //se i livelli saranno piu di 9 mod grandezza lvltxt e terminatore
    char *path=getPath(), lvltxt[2];
    strcat(path, "\\saves\\save.sav");
    FILE *fp=fopen(path,"r");
    if(fp!=NULL){
        fgets(lvltxt,sizeof(lvltxt),fp);
        lvltxt[1]='\0';
        lvlCompleted=atoi(lvltxt);
        fclose(fp);
        return 1;
    }else{
        fclose(fp);
        return 0;
    }
}
void init_menu(){
    int midScr=getmaxx(stdscr)/2;
    fSelect=loadSaves();
    midCPos=(getmaxy(stdscr)/2)+2;
    werase(stdscr);
    box(stdscr,0,0);
    artHprint(stdscr,160,logo,6);
    if(fSelect!=0){
        menupos_ch[0]=midCPos-4;
        menupos_ch[1]=midCPos;
        menupos_ch[2]=midCPos+4;
        mvwprintw(stdscr,menupos_ch[0],midScr-(strlen(menu_choice[0])/2),"%s",menu_choice[0]);
        mvwprintw(stdscr,menupos_ch[1],midScr-(strlen(menu_choice[1])/2),"%s",menu_choice[1]);
        mvwprintw(stdscr,menupos_ch[2],midScr-(strlen(menu_choice[2])/2),"%s",menu_choice[2]);
    }else{
        menupos_ch[0]=midCPos-2;
        menupos_ch[2]=midCPos+2;
        mvwprintw(stdscr,menupos_ch[0],midScr-(strlen(menu_choice[0])/2),"%s",menu_choice[0]);
        mvwprintw(stdscr,menupos_ch[2],midScr-(strlen(menu_choice[2])/2),"%s",menu_choice[2]);
    }
    wrefresh(stdscr);
    getch();   
}
void menu(int *quit){
    int midScr=getmaxx(stdscr)/2,rMenu=1, highlight=0,menuch=0;
    keypad(stdscr,TRUE);
    while(*quit){
        for(int i=0;i<3;i++){
            if(fSelect==0){
                if(i==1){
                    i++;
                }
            }
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
                if(fSelect==0){
                    if(highlight==1){
                        highlight=0;
                    }else{
                        if(highlight==0){
                            highlight=2;
                        }else{
                            highlight--;
                    }
                    }
                    
                }else{
                    if(highlight==0){
                        highlight=2;
                    }else{
                        highlight--;
                    }
                }
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                if(fSelect==0){
                    if(highlight==1){
                        highlight=2;
                    }else{
                        if(highlight==2){
                            highlight=0;
                        }else{
                            highlight++;
                        }
                    }
                }else{
                    if(highlight==2){
                        highlight=0;
                    }else{
                        highlight++;
                    }
                }
                break;
            case '\n':
                menu_subrun(highlight, quit);
                break;
        }
    }
    keypad(stdscr,FALSE);
    getch();
    rStatus=2;
    return;
}
void menu_subrun(int mMode, int *mExit){
    switch(mMode){
        case 0:
            printf("0 ok");
            break;
        case 1:
            printf("0 ok");
            break;
        case 2:
            werase(stdscr);
            box(stdscr,0,0);
            Cprint(stdscr, "Arrivederci!",1,1,0);
            napms(100);
            *mExit=0;
            break;
    }
}
