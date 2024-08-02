#include "levelsfunctions.h"
#include "levels.h"
#include "dialfunctions.h"
#include "features.h"
#include "initlevels.h"
#include <ncurses/ncurses.h>

int endIFError(int lPos){
    int ifCount=0;
    for(int i=0;i<lPos;i++){
        if(action_buffer[i]==action_IF){
            ifCount++;
        }else if(action_buffer[i]==action_ENDIF){
            ifCount--;
            if(ifCount<0){
                return -1;
            }
        }
    }
    return ifCount; // se =0 tutti gli if chiusi, se >0 mancano degli if aperti, <0 troppi endif
}
void ifErrorMSG(){
    werase(dialogue);
    box(dialogue,0,0);
    Cprint(dialogue,"Non puoi inserire due 'IF' di seguito",1,1,0);
    curAction_size--;
    action_buffer=(int *)realloc(action_buffer,curAction_size*sizeof(int));
    dReload=1;
}
void elseErrorMSG(){
    werase(dialogue);
    box(dialogue,0,0);
    Cprint(dialogue,"Puoi inserire l' 'ALTRIMENTI' solamente dopo il 'FINE_SE'.",1,1,0);
    curAction_size--;
    action_buffer=(int *)realloc(action_buffer,curAction_size*sizeof(int));
    dReload=1;
}
int elseEndError(int lPos){
    int elseCount=0;
    for(int i=0;i<lPos;i++){
        if(action_buffer[i]==action_ELSE){
            elseCount++;
        }else if(action_buffer[i]==action_ENDELSE){
            elseCount--;
            if(elseCount<0){
                return -1;
            }
        }
    }
    return elseCount;
}
void elseEndErrorMSG(){
    werase(dialogue);
    box(dialogue,0,0);
    Cprint(dialogue,"Puoi inserire il' 'FINE_ALTRIMENTI' solamente dopo aver utilizzato l' 'ALTRIMENTI'.",1,1,0);
    curAction_size--;
    action_buffer=(int *)realloc(action_buffer,curAction_size*sizeof(int));
    dReload=1;
}
int conditionError(int lastPos){
    if(action_buffer[lastPos]<=action_ENDSTART||action_buffer[lastPos]>=action_VAR){
        int halfY=getmaxy(dialogue)/2, halfX=getmaxx(dialogue)/2, txtLen=0;
        werase(dialogue);
        box(dialogue, 0, 0);
        txtLen=strlen("Nella struttura '%s' non e' presente una condizione valida.")/2;
        mvwprintw(dialogue, halfY-1, halfX-txtLen, "Nella struttura '%s' non e' presente una condizione valida.",correctAction[action_buffer[lastPos-1]].name);
        txtLen=strlen("Per favore inseriscine una valida.")/2;
        mvwprintw(dialogue,halfY+1, halfX-txtLen, "Per favore inseriscine una valida.");
        wmove(dialogue, 3,1);
        wrefresh(dialogue);
        dReload=1;
        curAction_size--;
        action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
        print_action();
        return 0;
    }
    else{
        return 1;
    }
}
void cicleErrorMSG(int curPos){
    werase(dialogue);
    box(dialogue,0,0);
    switch (action_buffer[curPos])
    {
        case action_WHILE:
            Cprint(dialogue,"Non puoi inserire due 'WHILE' di seguito",1,1,0);
            break;
        case action_DO:
            Cprint(dialogue,"Non puoi inserire due 'DO-WHILE' di seguito",1,1,0);
            break;
    }
    curAction_size--;
    action_buffer=(int *)realloc(action_buffer,curAction_size*sizeof(int));
    dReload=1;
}
int endCicleError(int lPos){
    int CCount=0;
    for(int i=0;i<lPos;i++){
        if(action_buffer[i]==action_WHILE||action_buffer[i]==action_DO){
            CCount++;
        }else if(action_buffer[i]==action_ENDCICLE){
            CCount--;
            if(CCount<0){
                return -1;
            }
        }
    }
    return CCount; // se =0 tutti i cicli chiusi, se >0 mancano dei cicli aperti, <0 troppi fin_cicli
}