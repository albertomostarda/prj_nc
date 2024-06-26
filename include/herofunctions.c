#include "herofunctions.h"
#include "levels.h"
#include "levelsfunctions.h"
#include "features.h"
#include <ncurses/ncurses.h>

int nSteps; // non ancora usata

int checkObstacle(){
    switch(pg1.rotation){
        case 0:
            if(mapArr[pg1.locate.y-1][pg1.locate.x]=='0'||mapArr[pg1.locate.y-1][pg1.locate.x]=='#'){
                return 1;
            }else{
                return 0;
            }
            break;
        case 1:
            if(mapArr[pg1.locate.y][pg1.locate.x+1]=='0'||mapArr[pg1.locate.y][pg1.locate.x+1]=='#'){
                return 1;
            }else{
                return 0;
            }
            break;
        case 2:
            if(mapArr[pg1.locate.y+1][pg1.locate.x]=='0'||mapArr[pg1.locate.y+1][pg1.locate.x]=='#'){
                return 1;
            }else{
                return 0;
            }
            break;
        case 3:
            if(mapArr[pg1.locate.y][pg1.locate.x-1]=='0'||mapArr[pg1.locate.y][pg1.locate.x-1]=='#'){
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
        // nel caso di piu' condizioni
    }
    while(isClear&&action_buffer[idx]!=action_ENDIF){
        switch (action_buffer[idx])
        {
            case action_IF:
                if_run(action_buffer[idx+1], idx+1);
                break;
            case action_WHILE:
                while_run(action_buffer[idx+1]);
                break;
            case action_DO:
                do_run(action_buffer[idx+1]);
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
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='9'){
                        mapArr[pg1.locate.y][pg1.locate.x]='8';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
                case 1:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.x++;if(mapArr[pg1.locate.y][pg1.locate.x]=='9'){
                        mapArr[pg1.locate.y][pg1.locate.x]='8';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
                case 2:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.y++;
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='9'){
                        mapArr[pg1.locate.y][pg1.locate.x]='8';
                    }else{
                        mapArr[pg1.locate.y][pg1.locate.x]='1';
                    }
                    break;
                case 3:
                    mapArr[pg1.locate.y][pg1.locate.x]='2';
                    pg1.locate.x--;
                    if(mapArr[pg1.locate.y][pg1.locate.x]=='9'){
                        mapArr[pg1.locate.y][pg1.locate.x]='8';
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
        
    }else{
        werase(dialogue);
        box(dialogue,0,0);
        Cprint(dialogue,"L'eroe non puo continuare per questa direzione.",1,1,0);    
    }
}
void while_run(int condition){

}
void do_run(int condition){

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