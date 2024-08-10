#include "herofunctions.h"
#include "levels.h"
#include "levelsfunctions.h"
#include "features.h"
#include "dialfunctions.h"
#include "errors.h"
#include <ncurses/ncurses.h>

int nSteps,nRot=1, isWalkEnd=1; // non ancora usata
Pos lastEnemy;

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
int if_run(int condition, int condPos,int *varPos, int *RCond){
    int idx=condPos+1, isClear=0,lRCond=-1;
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
        // nel caso di piu' condizioni
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
                idx=if_run(action_buffer[idx+1], idx+1, varPos, &lRCond);
                break;
            case action_ELSE:
                if(lRCond!=-1){
                    idx=else_run(idx+1, varPos,&lRCond);
                }
                break;
            case action_WHILE:
                idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1, varPos);
                break;
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
                        *varPos++;
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
int else_run(int nxtPos, int *varPos, int *lastCond){
    int idx=nxtPos, passRCond=-1;
    if(*lastCond==0){
        while(lastCond&&action_buffer[idx]!=action_ENDELSE){
            switch (action_buffer[idx])
            {
                case action_IF:
                    idx=if_run(action_buffer[idx+1], idx+1, varPos, &passRCond);
                    break;
                case action_ELSE:
                    if(passRCond!=-1){
                        idx=else_run(idx+1, varPos, &passRCond);
                    }
                    break;
                case action_WHILE:
                    idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1, varPos);
                    break;
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
                            *varPos++;
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
    }
    while (action_buffer[posi]!=caseCode)
    {
        posi++;
    }
    return posi-1;
}
void walk(){
    int i = 0, isObstacle = checkObstacle(), lastCheck = 0;
    while(isObstacle != 1 && i < nSteps){
        // Salva la posizione corrente del personaggio
        int oldX = pg1.locate.x;
        int oldY = pg1.locate.y;

        switch (pg1.rotation) {
            case 0: // Rotazione verso l'alto
                pg1.locate.y -= 1;
                break;
            case 1: // Rotazione verso destra
                pg1.locate.x += 1;
                break;
            case 2: // Rotazione verso il basso
                pg1.locate.y += 1;
                break;
            case 3: // Rotazione verso sinistra
                pg1.locate.x -= 1;
                break;
        }

        // Controlla se il personaggio è arrivato su un ostacolo o un elemento speciale
        if(mapArr[pg1.locate.y][pg1.locate.x] == '4'){
            mapArr[pg1.locate.y][pg1.locate.x] = '3';
        } else {
            mapArr[pg1.locate.y][pg1.locate.x] = '1';
        }
        if (mapArr[oldY][oldX] != '4') { // Evita di sovrascrivere un traguardo
            mapArr[oldY][oldX] = '2'; // Segna come visitata
        }

        run_anim(action);
        napms(500);
        print_map(map);
        lastCheck = isObstacle;
        isObstacle = checkObstacle();
        i++;
    }

    if(lastCheck != 1){
        isWalkEnd = 1;
    } else {
        werase(dialogue);
        box(dialogue, 0, 0);
        Cprint(dialogue, "L'eroe non può continuare per questa direzione.", 1, 1, 0);    
        isWalkEnd = 0;
    }
}
// void walk(){
//     int i=0, isObstacle=checkObstacle(),lastCheck=0;
//     while(isObstacle!=1&&i<nSteps){
//         switch (pg1.rotation)
//         {
//             case 0:
//                 mapArr[pg1.locate.y][pg1.locate.x]='2';
//                 pg1.locate.y=pg1.locate.y-1;
//                 if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
//                     mapArr[pg1.locate.y][pg1.locate.x]='3';
//                 }else{
//                     mapArr[pg1.locate.y][pg1.locate.x]='1';
//                 }
//                 break;
//             case 1:
//                 mapArr[pg1.locate.y][pg1.locate.x]='2';
//                 pg1.locate.x++;
//                 if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
//                     mapArr[pg1.locate.y][pg1.locate.x]='3';
//                 }else{
//                     mapArr[pg1.locate.y][pg1.locate.x]='1';
//                 }
//                 break;
//             case 2:
//                 mapArr[pg1.locate.y][pg1.locate.x]='2';
//                 pg1.locate.y++;
//                 if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
//                     mapArr[pg1.locate.y][pg1.locate.x]='3';
//                 }else{
//                     mapArr[pg1.locate.y][pg1.locate.x]='1';
//                 }
//                 break;
//             case 3:
//                 mapArr[pg1.locate.y][pg1.locate.x]='2';
//                 pg1.locate.x--;
//                 if(mapArr[pg1.locate.y][pg1.locate.x]=='4'){
//                     mapArr[pg1.locate.y][pg1.locate.x]='3';
//                 }else{
//                     mapArr[pg1.locate.y][pg1.locate.x]='1';
//                 }
//                 break;
//         }
//         run_anim(action);
//         napms(500);
//         print_map(map);
//         lastCheck=isObstacle;
//         isObstacle=checkObstacle();
//         i++;
//     }
//     if(lastCheck!=1){
//         isWalkEnd=1;
//     }else{
//         werase(dialogue);
//         box(dialogue,0,0);
//         Cprint(dialogue,"L'eroe non puo continuare per questa direzione.",1,1,0);    
//         isWalkEnd=0;
//     }
// }
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
            // nel caso aggiungere piu' condizioni
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
                    idx=if_run(action_buffer[idx+1], idx+1, varPos, &elsePassC);
                    break;
                case action_ELSE:
                    if(elsePassC!=-1){
                        idx=else_run(idx+1, varPos, &elsePassC);
                    }
                    break;
                case action_WHILE:
                    idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1,varPos);
                    break;
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
            // nel caso aggiungere piu' condizioni
        }
        InsTot++;
    }
    if(InsTot>=99){
        cOverflowErrMSG();
    }
    *varPos=tempVPos+1;
    if(action_buffer[idx]==action_ENDCICLE){
        return idx-1;
    }else{
        return getEndStruct(condPos+1,3);
    }
}
// int do_run(int condition, int condPos, int *varPos){
//     int idx=condPos+1, isClear=1, tempVPos=*varPos;
//     while(isClear){
//         idx=condPos+1;
//         tempVPos=*varPos;
//         while(action_buffer[idx]!=action_ENDCICLE){
//             switch (action_buffer[idx])
//             {
//                 case action_IF:
//                     idx=if_run(action_buffer[idx+1], idx+1, varPos);
//                     break;
//                 case action_WHILE:
//                     idx=while_run(action_buffer[idx+1], idx+1, varPos);
//                     break;
//                 case action_DO:
//                     idx=do_run(action_buffer[idx+1],idx+1,varPos);
//                     break;
//                 case action_WALK:
//                     walk();
//                     break;
//                 case action_LROTATE:
//                     rotcclock();
//                     break;
//                 case action_RROTATE:
//                     rotclock();
//                     break;
//                 case action_attack:
//                     attack();
//                     break;
//                 default:
//                     if(action_buffer[idx]>=action_VAR){
//                         switch(var_buffer[tempVPos].type){
//                             case var_nSteps:
//                                 set_steps(action_buffer[var_buffer[tempVPos].actIndex]-action_VAR);
//                                 break;
//                             case var_nTurns:
//                                 set_turns(action_buffer[var_buffer[tempVPos].actIndex]-action_VAR);
//                                 break;
//                         }
//                         tempVPos++;
//                     }
//                     break;
//             }
//             idx++;
//         }
//         switch (condition)
//         {
//             case action_isObstacle:
//                 isClear=checkObstacle();
//                 break;
//             case action_isEnemy:
//                 isClear=checkEnemy();
//                 break;
//             // nel caso di piu' condizioni
//         }
//     }
//     *varPos=tempVPos+1;
//     if(action_buffer[idx]==action_ENDCICLE){
//         return idx-1;
//     }else{
//         return getEndCicle(condPos+1);
//     }
// }
void attack(){
        char curEnemyHP=mapArr[lastEnemy.y][lastEnemy.x]-5;
        if((curEnemyHP-1)>'0'){
            mapArr[lastEnemy.y][lastEnemy.x]--;
        }else if((curEnemyHP-1)=='0'){
            mapArr[lastEnemy.y][lastEnemy.x]='2';
        }
        napms(1000);
        print_map(map);
        //attack_splash();
}
void rotcclock(){
    for(int i=0;i<nRot;i++){
        if(pg1.rotation==0){
            pg1.rotation=3;
        }else{
            pg1.rotation--;
        }
    }
}
void rotclock(){
    for(int i=0;i<nRot;i++){
        if(pg1.rotation==3){
            pg1.rotation=0;
        }else{
            pg1.rotation++;
        }
    }
}
void set_steps(int value){
    nSteps=value;
}
void set_turns(int value){
    nRot=value;
}
// int checkEnemy(){
//     switch(pg1.rotation){
//         case 0:  // Se si trova sopra al pg
//             if(mapArr[pg1.locate.y-1][pg1.locate.x]>='5'&&mapArr[pg1.locate.y-1][pg1.locate.x]<='9'){
//                 lastEnemy.y=pg1.locate.y-1;
//                 lastEnemy.x=pg1.locate.x;
//                 return 1;
//             }else{
//                 return 0;
//             }
//             break;
//         case 1:  // Se si trova a destra
//             if(mapArr[pg1.locate.y][pg1.locate.x+1]>='5'&&mapArr[pg1.locate.y][pg1.locate.x+1]<='9'){
//                 lastEnemy.y=pg1.locate.y;
//                 lastEnemy.x=pg1.locate.x+1;
//                 return 1;
//             }else{
//                 return 0;
//             }
//             break;
//         case 2:  // Se si trova sotto il pg
//             if(mapArr[pg1.locate.y+1][pg1.locate.x]>='5'&&mapArr[pg1.locate.y+1][pg1.locate.x]<='9'){
//                 lastEnemy.y=pg1.locate.y+1;
//                 lastEnemy.x=pg1.locate.x;
//                 return 1;
//             }else{
//                 return 0;
//             }
//             break;
//         case 3:  // Se si trova a sinitra
//             if(mapArr[pg1.locate.y][pg1.locate.x-1]>='5'&&mapArr[pg1.locate.y][pg1.locate.x-1]<='9'){
//                 lastEnemy.y=pg1.locate.y;
//                 lastEnemy.x=pg1.locate.x-1;
//                 return 1;
//             }else{
//                 return 0;
//             }
//             break;
//     }
// }
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
int checkNGoal(){
    if(mapArr[pg1.locate.y][pg1.locate.x]=='3'){
        return 0;
    }else{
        return 1;
    }
}
// int getEndCicle(int lsPos){
//     while (action_buffer[lsPos]!=action_ENDCICLE)
//     {
//         lsPos++;
//     }
//     return lsPos-1;
// }
// void attack_splash(){
//     chtype ogColor= getbkgd(stdscr);
//     erase();
//     bkgd(COLOR_PAIR(9));
//     refresh();
//     napms(200);
//     bkgd(ogColor);
//     refresh();
//     print_map(map);
//     print_action();
//     printOneDLine();
// }