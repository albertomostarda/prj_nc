#include "herofunctions.h"
#include "levels.h"
#include "levelsfunctions.h"
#include "features.h"
#include <ncurses/ncurses.h>

int nSteps,nRot, isWalkEnd=1; // non ancora usata
Pos lastEnemy={0,0};

int checkObstacle(){
    switch(pg1.rotation){
        case 0:
            if(mapArr[pg1.locate.y-1][pg1.locate.x]=='0'||mapArr[pg1.locate.y-1][pg1.locate.x]=='#'||mapArr[pg1.locate.y-1][pg1.locate.x]>='5'){
                return 1;
            }else{
                return 0;
            }
            break;
        case 1:
            if(mapArr[pg1.locate.y][pg1.locate.x+1]=='0'||mapArr[pg1.locate.y][pg1.locate.x+1]=='#'||mapArr[pg1.locate.y][pg1.locate.x+1]>='5'){
                return 1;
            }else{
                return 0;
            }
            break;
        case 2:
            if(mapArr[pg1.locate.y+1][pg1.locate.x]=='0'||mapArr[pg1.locate.y+1][pg1.locate.x]=='#'||mapArr[pg1.locate.y+1][pg1.locate.x]>='5'){
                return 1;
            }else{
                return 0;
            }
            break;
        case 3:
            if(mapArr[pg1.locate.y][pg1.locate.x-1]=='0'||mapArr[pg1.locate.y][pg1.locate.x-1]=='#'||mapArr[pg1.locate.y][pg1.locate.x-1]>='5'){
                return 1;
            }else{
                return 0;
            }
            break;
    }
}
int if_run(int condition, int condPos){
    int idx=condPos+1, isClear=0;
    
    switch (condition)
    {
        case action_isObstacle:
            isClear=checkObstacle();
            break;
        case action_isEnemy:
            isClear=checkEnemy();
            break;
        // nel caso di piu' condizioni
    }
    while(isClear&&action_buffer[idx]!=action_ENDIF){
        switch (action_buffer[idx])
        {
            case action_IF:
                idx=if_run(action_buffer[idx+1], idx+1);
                break;
            case action_WHILE:
                idx=while_run(action_buffer[idx+1], idx+1);
                break;
            case action_DO:
                idx=do_run(action_buffer[idx+1],idx+1);
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
                    set_steps(action_buffer[idx]-action_VAR);
                }
                break;
        }
        idx++;
    }
    if(action_buffer[idx]==action_ENDIF){
        return idx-1;
    }else{
        return getEndif(condPos+1);
    }
}
int getEndif(int posi){
    while (action_buffer[posi]!=action_ENDIF)
    {
        posi++;
    }
    return posi-1;
}
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
        werase(dialogue);
        box(dialogue,0,0);
        Cprint(dialogue,"L'eroe non puo continuare per questa direzione.",1,1,0);    
        isWalkEnd=0;
    }
}
int while_run(int condition, int condPos){
    int idx=condPos+1, isClear=0;
    switch (condition)
    {
        case action_isObstacle:
            isClear=checkObstacle();
            break;
        case action_isEnemy:
            isClear=checkEnemy();
            break;
        // nel caso di piu' condizioni
    }
    while(isClear){
        switch (condition)
        {
            case action_isObstacle:
                isClear=checkObstacle();
                break;
            case action_isEnemy:
                isClear=checkEnemy();
                break;
            // nel caso di piu' condizioni
        }
        while(action_buffer[idx]!=action_ENDCICLE){
            switch (action_buffer[idx])
            {
                case action_IF:
                    idx=if_run(action_buffer[idx+1], idx+1);
                    break;
                case action_WHILE:
                    idx=while_run(action_buffer[idx+1], idx+1);
                    break;
                case action_DO:
                    idx=do_run(action_buffer[idx+1],idx+1);
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
                        set_steps(action_buffer[idx]-action_VAR);
                    }
                    break;
            }
            idx++;
        }
    }
    if(action_buffer[idx]==action_ENDCICLE){
        return idx-1;
    }else{
        //return getEndif(condPos+1);
    }
}
int do_run(int condition, int condPos){
    int idx=condPos+1, isClear=1;
    
    while(isClear){
        while(action_buffer[idx]!=action_ENDCICLE){
            switch (action_buffer[idx])
            {
                case action_IF:
                    idx=if_run(action_buffer[idx+1], idx+1);
                    break;
                case action_WHILE:
                    idx=while_run(action_buffer[idx+1], idx+1);
                    break;
                case action_DO:
                    idx=do_run(action_buffer[idx+1],idx+1);
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
                        set_steps(action_buffer[idx]-action_VAR);
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
            // nel caso di piu' condizioni
        }
    }
    if(action_buffer[idx]==action_ENDCICLE){
        return idx-1;
    }else{
        //return getEndif(condPos+1);
    }
}

int attack(){
    if(checkEnemy){
        int curEnemyHP=mapArr[lastEnemy.y][lastEnemy.x]-5;
        if(curEnemyHP-1>=0){
            mapArr[lastEnemy.y][lastEnemy.x]--;
        }else{
            mapArr[lastEnemy.y][lastEnemy.x]=2;
        }
        return 0;
    }else{
        return 1;
    }
    
}
void rotcclock(){
    if(pg1.rotation==0){
        pg1.rotation=3;
    }else{
        pg1.rotation--;
    }
}
void rotclock(){
    if(pg1.rotation==3){
        pg1.rotation=0;
    }else{
        pg1.rotation++;
    }
}
void set_steps(int value){
    nSteps=value;
}

int checkEnemy(){
    switch(pg1.rotation){
        case 0:
            if(mapArr[pg1.locate.y-1][pg1.locate.x]>='5'){
                lastEnemy.y=pg1.locate.y-1;
                lastEnemy.x=pg1.locate.x;
                return 1;
            }else{
                return 0;
            }
            break;
        case 1:
            if(mapArr[pg1.locate.y][pg1.locate.x+1]>='5'){
                lastEnemy.y=pg1.locate.y;
                lastEnemy.x=pg1.locate.x+1;
                return 1;
            }else{
                return 0;
            }
            break;
        case 2:
            if(mapArr[pg1.locate.y+1][pg1.locate.x]>='5'){
                lastEnemy.y=pg1.locate.y+1;
                lastEnemy.x=pg1.locate.x;
                return 1;
            }else{
                return 0;
            }
            break;
        case 3:
            if(mapArr[pg1.locate.y][pg1.locate.x-1]>='5'){
                lastEnemy.y=pg1.locate.y;
                lastEnemy.x=pg1.locate.x-1;
                return 1;
            }else{
                return 0;
            }
            break;
    }
}