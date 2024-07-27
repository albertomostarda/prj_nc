#include "dialfunctions.h"
#include "levels.h"
#include "features.h"
#include <windows.h>
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <time.h>

char **dialogue_buffer;
int dialBuff_size=0, dialPos=0, isEmpty=1;

// void reloadDialogue(LPVOID *data){
//     ThreadParam *tParam = (ThreadParam*)data;
//     time_t waitTime;
//     while(1){
//         if(*(tParam->gLight)!=0){
//             *(tParam->gLight)=0;
//             waitTime=time(NULL);
//             while((time(NULL)-waitTime)<30);
//             printOneDLine();
//         }
//         Sleep(500);
//     }
// }
char* getDialPath(){
    char *pPath=getPath();
    char *fName[]={
        "resources\\dialogueone.txt\0",
        "resources\\dialoguetwo.txt\0",
        "resources\\dialoguethree.txt\0",
        "resources\\dialoguefour.txt\0",
        "resources\\dialoguefive.txt\0"
    };
    // switch(sLevel){
    //     case 1:
    //         strcpy(fName, "resources\\dialogueone.txt");
    //         break;
    //     case 2:
    //         strcpy(fName, "resources\\dialoguetwo.txt");
    //         break;
    //     case 3:
    //         strcpy(fName, "resources\\dialoguethree.txt");
    //         break;
    //     case 4:
    //         strcpy(fName, "resources\\dialoguefour.txt");
    //         break;
    //     case 5:
    //         strcpy(fName, "resources\\dialoguefive.txt");
    //         break;
    // }
    char *dialPath=(char *)malloc(max_path);
    strcpy(dialPath, pPath);
    if (dialPath[strlen(dialPath)] != '\\') {
       dialPath[strlen(dialPath)]='\\';
    }
    strcat(dialPath, fName[sLevel-1]);
    return dialPath;
}
void loadDialogue(){
    FILE *fp;
    char *pDial=getDialPath(), buffer[2048];
    int dLength=0;
    fp=fopen(pDial,"r");
    if(fp==NULL){
        mvwprintw(dialogue,1,1,"Dialoghi non caricati");
        wrefresh(dialogue);
        fclose(fp);
        free(pDial);
        isEmpty=1;
        return ;
        //aggiungere chiusura/ritorno al Menu
    }
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

