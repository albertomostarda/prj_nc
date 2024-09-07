/**
 * @file herofunctions.c
 * @author Alberto Mostarda (mostarda.alberto04@gmail.com)
 * @brief in cui sono presenti le funzioni che servono per il funzionamento del personaggio
 * @version 1.0
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "herofunctions.h"
#include "levels.h"
#include "levelsfunctions.h"
#include "features.h"
#include "dialfunctions.h"
#include "errors.h"
#include <ncurses/ncurses.h>
#include <time.h>

int nSteps,nRot=1, isWalkEnd=1; // non ancora usata
Pos lastEnemy;

/**
 * @brief Funzione che verifica la presenza di ostacoli nella casella successiva al personaggio.
 * 
 * @return int 
 */
int checkObstacle(){
    switch(pg1.rotation){
        case 0:
            if(mapArr[pg1.locate.y-1][pg1.locate.x]=='0'||mapArr[pg1.locate.y-1][pg1.locate.x]=='#'||(mapArr[pg1.locate.y-1][pg1.locate.x]>='5'&&mapArr[pg1.locate.y-1][pg1.locate.x]<='9')){
                return 1;
            }else{
                return 0;
            }
            break;
        case 1:
            if(mapArr[pg1.locate.y][pg1.locate.x+1]=='0'||mapArr[pg1.locate.y][pg1.locate.x+1]=='#'||(mapArr[pg1.locate.y][pg1.locate.x+1]>='5'&&mapArr[pg1.locate.y][pg1.locate.x+1]<='9')){
                return 1;
            }else{
                return 0;
            }
            break;
        case 2:
            if(mapArr[pg1.locate.y+1][pg1.locate.x]=='0'||mapArr[pg1.locate.y+1][pg1.locate.x]=='#'||(mapArr[pg1.locate.y+1][pg1.locate.x]>='5'&&mapArr[pg1.locate.y+1][pg1.locate.x]<='9')){
                return 1;
            }else{
                return 0;
            }
            break;
        case 3:
            if(mapArr[pg1.locate.y][pg1.locate.x-1]=='0'||mapArr[pg1.locate.y][pg1.locate.x-1]=='#'||(mapArr[pg1.locate.y][pg1.locate.x-1]>='5'&&mapArr[pg1.locate.y][pg1.locate.x-1]<='9')){
                return 1;
            }else{
                return 0;
            }
            break;
    }
}
/**
 * @brief Funzione che gestisce l’esecuzione della struttura “SE”.
 * 
 * @param condPos 
 * @param varPos 
 * @param RCond 
 * @return int 
 */
int if_run(int condPos,int *varPos, int *RCond){
    int idx=condPos+1, isClear=0,lRCond=-1, condition=action_buffer[condPos];
    switch (condition)
    {
        case action_isObstacle:
            isClear=checkObstacle();
            break;
        case action_isEnemy:
            isClear=checkEnemy();
            break;
        case action_isNotGoal:
            isClear=checkNGoal();
            break;
    }
    if(isClear==1){
        *RCond=0;
    }else{
        *RCond=1;
    }
    while(isClear&&action_buffer[idx]!=action_ENDIF){
        switch (action_buffer[idx])
        {
            case action_IF:
                idx=if_run(idx+1, varPos, &lRCond);
                break;
            case action_ELSE:
                idx=else_run(idx+1, varPos,&lRCond);
                break;
            case action_WHILE:
            case action_DO:
                idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1, varPos);
                break;
            case action_WALK:
                walk();
                break;
            case action_LROTATE:
                rotcclock();
                break;
            case action_RROTATE:
                rotclock();
                break;
            case action_attack:
                attack();
                break;
            default:
                if(action_buffer[idx]>=action_VAR){
                    switch(var_buffer[*varPos].type){
                            case var_nSteps:
                                set_steps(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
                                break;
                            case var_nTurns:
                                set_turns(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
                                break;
                        }
                        (*varPos)++;
                }
                break;
        }
        idx++;
    }
    if(action_buffer[idx]==action_ENDIF){
        return idx-1;
    }else{
        return getEndStruct(condPos+1,1);
    }
}
/**
 * @brief Funzione che gestisce l’esecuzione della struttura “ALTRIMENTI”.
 * 
 * @param nxtPos 
 * @param varPos 
 * @param lastCond 
 * @return int 
 */
int else_run(int nxtPos, int *varPos, int *lastCond){
    int idx=nxtPos, passRCond=-1;
    if(*lastCond){
        while(action_buffer[idx]!=action_ENDELSE){
            switch (action_buffer[idx])
            {
                case action_IF:
                    idx=if_run(idx+1, varPos, &passRCond);
                    break;
                case action_WHILE:
                case action_DO:
                    idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1, varPos);
                    break;
                case action_WALK:
                    walk();
                    break;
                case action_LROTATE:
                    rotcclock();
                    break;
                case action_RROTATE:
                    rotclock();
                    break;
                case action_attack:
                    attack();
                    break;
                default:
                    if(action_buffer[idx]>=action_VAR){
                        switch(var_buffer[*varPos].type){
                                case var_nSteps:
                                    set_steps(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
                                    break;
                                case var_nTurns:
                                    set_turns(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
                                    break;
                            }
                            (*varPos)++;
                    }
                    break;
            }
            idx++;
        }
    }
    *lastCond=-1;
    if(action_buffer[idx]==action_ENDELSE){
        return idx-1;
    }else{
        return getEndStruct(nxtPos,2);
    }
}
/**
 * @brief Funzione che restituisce la posizione delle strutture “FINE_SE”, ”FINE_CICLO” e “FINE_ALTRIMENTI”.
 * 
 * @param posi 
 * @param type 
 * @return int 
 */
int getEndStruct(int posi, int type){
    actionCode caseCode;
    switch(type){
        case 1:
            caseCode=action_ENDIF;
            break;
        case 2:
            caseCode=action_ENDELSE;
            break;
        case 3:
            caseCode=action_ENDCICLE;
            break;
    }
    while (action_buffer[posi]!=caseCode&& posi < curAction_size)
    {
        posi++;
    }
    return posi-1;
}
/**
 * @brief Funzione che permette al personaggio di camminare nella mappa.
 * 
 */
void walk(){
    int i=0;
    if(checkObstacle()!=1){
        while(i<nSteps){
            switch (pg1.rotation)
            {
                case 0:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.y=pg1.locate.y-1;
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
                        mapArr[pg1.locate.y][pg1.locate.x]='3';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
                case 1:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.x++;
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
                        mapArr[pg1.locate.y][pg1.locate.x]='3';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
                case 2:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.y++;
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
                        mapArr[pg1.locate.y][pg1.locate.x]='3';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
                case 3:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.x--;
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
                        mapArr[pg1.locate.y][pg1.locate.x]='3';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
            }
            run_anim(action);
            napms(500);
            print_map(map);
            i++;
        }
        isWalkEnd=1;
    }else{
        time_t swait=time(NULL);
        werase(dialogue);
        box(dialogue,0,0);
        Cprint(dialogue,"L'eroe non puo continuare per questa direzione.",1,1,0);
        SBHprint(dialogue,pContinue,1);
        nodelay(stdscr,TRUE);
        nclearBuff();
        while(getch()!='\n'&&(time(NULL)-swait)>10);
        nclearBuff();
        nodelay(stdscr, FALSE);
        isWalkEnd=0;
    }
}
/**
 * @brief Funzione che gestisce l’esecuzione delle strutture “MENTRE” e “FAI MENTRE”.
 * 
 * @param cType 
 * @param condition 
 * @param condPos 
 * @param varPos 
 * @return int 
 */
int cicle_run(int cType, int condition, int condPos, int *varPos){
    int idx=condPos+1, isClear=0, tempVPos=*varPos, elsePassC=-1, InsTot=0;
    if(cType==action_WHILE){
        switch (condition)
        {
            case action_isObstacle:
                isClear=checkObstacle();
                break;
            case action_isEnemy:
                isClear=checkEnemy();
                break;
            case action_isNotGoal:
                isClear=checkNGoal();
                break;
        }
    }else if(cType==action_DO){
        isClear=1;
    }
    while(isClear&&InsTot<100){
        idx=condPos+1;
        tempVPos=*varPos;
        elsePassC=-1;
        while(action_buffer[idx]!=action_ENDCICLE){
            switch (action_buffer[idx])
            {
                case action_IF:
                    idx=if_run(idx+1, varPos, &elsePassC);
                    break;
                case action_ELSE:
                    idx=else_run(idx+1, varPos, &elsePassC);
                    break;
                case action_WHILE:
                case action_DO:
                    idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1,varPos);
                    break;
                case action_WALK:
                    walk();
                    break;
                case action_LROTATE:
                    rotcclock();
                    break;
                case action_RROTATE:
                    rotclock();
                    napms(500);
                    print_map(map);
                    break;
                case action_attack:
                    attack();
                    break;
                default:
                    if(action_buffer[idx]>=action_VAR){
                        switch(var_buffer[tempVPos].type){
                            case var_nSteps:
                                set_steps(action_buffer[var_buffer[tempVPos].actIndex]-action_VAR);
                                break;
                            case var_nTurns:
                                set_turns(action_buffer[var_buffer[tempVPos].actIndex]-action_VAR);
                                break;
                        }
                        tempVPos++;
                    }
                    break;
            }
            idx++;
        }
        switch (condition)
        {
            case action_isObstacle:
                isClear=checkObstacle();
                break;
            case action_isEnemy:
                isClear=checkEnemy();
                break;
            case action_isNotGoal:
                isClear=checkNGoal();
                break;
        }
    }
    if(InsTot>=99){
        cOverflowErrMSG();
    }
    *varPos=tempVPos;
    if(action_buffer[idx]==action_ENDCICLE){
        return idx-1;
    }else{
        return getEndStruct(condPos+1,3);
    }
}
/**
 * @brief Funzione che permette al personaggio di attaccare i nemici.
 * 
 */
void attack(){
        char curEnemyHP=mapArr[lastEnemy.y][lastEnemy.x]-5;
        if((curEnemyHP-1)>'0'){
            mapArr[lastEnemy.y][lastEnemy.x]--;
        }else if((curEnemyHP-1)=='0'){
            mapArr[lastEnemy.y][lastEnemy.x]='2';
        }
        napms(1000);
        print_map(map);
}
/**
 * @brief Funzione che ruota in senso antiorario la direzione in cui il personaggio deve proseguire.
 * 
 */
void rotcclock(){
    for(int i=0;i<nRot;i++){
        if(pg1.rotation==0){
            pg1.rotation=3;
        }else{
            pg1.rotation--;
        }
    }
}
/**
 * @brief Funzione che ruota in senso orario la direzione in cui il personaggio deve proseguire.
 * 
 */
void rotclock(){
    for(int i=0;i<nRot;i++){
        if(pg1.rotation==3){
            pg1.rotation=0;
        }else{
            pg1.rotation++;
        }
    }
}
/**
 * @brief Funzione che imposta il numero di passi che il personaggio esegue.
 * 
 * @param value 
 */
void set_steps(int value){
    nSteps=value;
}
/**
 * @brief Funzione che imposta il numero di rotazioni che il personaggio esegue.
 * 
 * @param value 
 */
void set_turns(int value){
    nRot=value;
}
/**
 * @brief Funzione che verifica la presenza dei nemici nella casella successiva al personaggio.
 * 
 * @return int 
 */
int checkEnemy() {
    int y = pg1.locate.y;
    int x = pg1.locate.x;
    int found = 0;
    switch(pg1.rotation) {
        case 0: // Se si trova sopra al pg
            if (mapArr[y-1][x] >= '5' && mapArr[y-1][x] <= '9') {
                lastEnemy.y = y - 1;
                lastEnemy.x = x;
                found = 1;
            }
            break;
        case 1: // Se si trova a destra
            if (mapArr[y][x+1] >= '5' && mapArr[y][x+1] <= '9') {
                lastEnemy.y = y;
                lastEnemy.x = x + 1;
                found = 1;
            }
            break;
        case 2: // Se si trova sotto il pg
            if (mapArr[y+1][x] >= '5' && mapArr[y+1][x] <= '9') {
                lastEnemy.y = y + 1;
                lastEnemy.x = x;
                found = 1;
            }
            break;
        case 3: // Se si trova a sinitra
            if (mapArr[y][x-1] >= '5' && mapArr[y][x-1] <= '9') {
                lastEnemy.y = y;
                lastEnemy.x = x - 1;
                found = 1;
            }
            break;
        default:
            found = 0;
            break;
    }
    return found;
}
/**
 * @brief Funzione che verifica se il personaggio sia arrivato al traguardo.
 * 
 * @return int 
 */
int checkNGoal(){
    if(mapArr[pg1.locate.y][pg1.locate.x]=='3'){
        return 0;
    }else{
        return 1;
    }
}