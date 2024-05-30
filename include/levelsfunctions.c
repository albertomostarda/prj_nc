#include "levelsfunction.h"
#include "initlevels.h"
#include "levels.h"
#include <ncurses.h>

void printcolor_str(WINDOW *tWin,char *colStr, int pLines){
    for(int i=0;i<pLines;i++){
        printcolor_char(tWin,colStr[i]);
    }
}
void printcolor_char(WINDOW *tWin,char cch){
    switch(cch){
        case '#':
            waddch(tWin, walls);
            break;
        case '0':
            waddch(tWin, blank);
            break;
        case '1':
            waddch(tWin, pg1.icon);
            break;
        case '2':
            waddch(tWin, road);
            break;
        case '9':
            waddch(tWin, goal);
            break;
    }
}

void print_action(){
    int conLenght=0, actY=0, indent=1, isCond=0,canGo=1;//
    werase(action);
    box(action, 0,0);
    for(int i=0;i<curAction_size&&canGo;i++){
            switch (action_buffer[i])
            {
                case action_START:
                    mvwprintw(action, auPad+actY, alPad,"%s", correctAction[action_buffer[i]].name);
                    actY++;
                    break;
                case action_IF:
                    mvwprintw(action, auPad+actY, alPad+(3*indent),"%s", correctAction[action_buffer[i]].name);
                    conLenght+=strlen(correctAction[action_buffer[i]].name)+alPad+(3*indent)+1;
                    isCond=1;
                    break;
                // case action_SPARENT:
                //     conLenght=strlen(correctAction[action_buffer[i-1]].name)+alPad+(3*indent);
                //     mvwprintw(action, auPad+actY, conLenght,"%s", correctAction[action_buffer[i]].name);
                //     break;
                // case action_EPARENT:
                //     canGo=check_Econdition(i);
                //     if(canGo){
                //         conLenght+=strlen(correctAction[action_buffer[i-1]].name);
                //         mvwprintw(action,auPad+actY, conLenght,"%s", correctAction[action_buffer[i]].name);
                //         conLenght=0;
                //         actY++;
                //         indent++;
                //     }else{
                //         actY--;
                //     }
                //     break;
                case action_ENDIF:
                    if(indent>1){
                        indent--;
                    }
                    if(conLenght!=0){
                        mvwprintw(action,auPad+actY,conLenght,"%s", correctAction[action_buffer[i]].name);
                    }else{
                        mvwprintw(action,auPad+actY,alPad+(3*indent),"%s", correctAction[action_buffer[i]].name);
                        actY++;
                    }
                default:
                    if(isCond&&(action_buffer[i]>action_ENDSTART&&action_buffer[i]<action_VAR)){
                        canGo=conditionError(i);
                        if(canGo){
                            isCond=0;
                            mvwprintw(action, auPad+actY, conLenght,"%s", correctAction[action_buffer[i]].name);
                            conLenght=0;
                            actY++;
                            indent++;
                        }else{
                            actY--;
                        }
                    }
                    else if(action_buffer[i]>=action_VAR){
                        mvwprintw(action, auPad+actY, alPad+(3*indent),"int nPassi= %d;", action_buffer[i]-action_VAR);
                        actY++;
                    }/*else if((action_buffer[i]>action_ENDSTART&&action_buffer[i]<action_VAR)&&conLenght!=0)/*caso delle condizioni{
                        mvwprintw(action, auPad+actY, conLenght,"%s", correctAction[action_buffer[i]].name);
                        actY++;
                        indent++;
                    }*/else if(conLenght!=0){
                        conLenght+=strlen(correctAction[action_buffer[i-1]].name);
                        mvwprintw(action, auPad+actY, conLenght,"%s", correctAction[action_buffer[i]].name);
                    }else{
                        mvwprintw(action, auPad+actY, alPad+(3*indent),"%s", correctAction[action_buffer[i]].name);
                        actY++;
                    }
                    break;
            }
        wrefresh(action);
        // if(i!=0){
        //     if(action_buffer[i]>=action_VAR){
        //         mvwprintw(action, auPad+i, alPad+3,"int nPassi= %d;", action_buffer[i]-action_VAR);
        //     }else{
        //         mvwprintw(action, auPad+i, alPad+3,"%s", correctAction[action_buffer[i]].name);
        //     }
        // }
        // else{
        //     mvwprintw(action, auPad+i, alPad,"%s", correctAction[action_buffer[i]].name);
        // }
    }
}
int conditionError(int lastPos){
    if(action_buffer[lastPos]<=action_ENDSTART||action_buffer[lastPos]>=action_VAR){
        int halfY=getmaxy(dialogue)/2, halfX=getmaxx(dialogue)/2, txtLen=0;
        werase(dialogue);
        box(dialogue, 0, 0);
        txtLen=strlen("Nella struttura '%s' non e' presente una condizione valida.");
        mvwprintw(dialogue, halfY-1, halfX-txtLen, "Nella struttura '%s' non e' presente una condizione valida.",correctAction[action_buffer[lastPos-1]].name);
        txtLen=strlen("Per favore inseriscine una valida.");
        mvwprintw(dialogue,halfY+1, halfX-txtLen, "Per favore inseriscine una valida.");
        wmove(dialogue, 3,1);
        wrefresh(dialogue);
        curAction_size--;
        action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
        print_action();
        return 0;
    }
    else if(action_buffer){
        return 1;
    }
}
// int check_Econdition(int lastPos){
//     if((action_buffer[lastPos-1]<=action_ENDSTART||action_buffer[lastPos-1]>=action_VAR)&&action_buffer[lastPos-1]!=action_SPARENT){
//         werase(dialogue);
//         box(dialogue, 0,0);
//         //Cprint(dialogue,"Nella struttura 'IF' non e' presente una condizione valida",1,1,0);
//         //Cprint(dialogue,"Per favore inseriscine una valida.",1,1,0);
//         mvwprintw(dialogue, 1,1, "Nella struttura '%s' non e' presente una condizione valida.", correctAction[action_buffer[lastPos-3]].name);
//         mvwprintw(dialogue, 2,1, "Per favore inseriscine una valida.");
//         wmove(dialogue, 3,1);
//         wrefresh(dialogue);
//         curAction_size-=2;
//         action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
//         print_action();
//         return 0;
//     }else if(action_buffer[lastPos-1]==action_SPARENT){
//         werase(dialogue);
//         box(dialogue, 0,0);
//         mvwprintw(dialogue, 1,1, "Nella struttura '%s' non e' presente la condizione.", correctAction[action_buffer[lastPos-2]].name);
//         mvwprintw(dialogue, 2,1, "Per favore inseriscine una o elimina la struttura.");
//         wmove(dialogue, 3,1);
//         wrefresh(dialogue);
//         curAction_size--;
//         action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
//         print_action();
//         return 0;
//     }else{
//         return 1;
//     }
// }

void delete_action(){
    int halfY=(getmaxy(action)-getbegy(action))/2, halfX=(getmaxx(action)-getbegx(action))/2;
    int txtLen=0, highlight=0, choiceBreak=1, confirmChoice=0;
    char confirmYN[2][2]={"[SI]","[NO]"};
    int confirmYN_Pos[2]={halfX-6,halfX+6};
    werase(action);
    box(action, 0 ,0);
    txtLen=strlen("Stai per eliminare l'ultima istruzione inserita.");
    mvwprintw(action, halfY-1, halfX-txtLen,"Stai per eliminare l'ultima istruzione inserita.");
    txtLen=strlen("Sei sicuro?");
    mvwprintw(action, halfY+1, halfX-txtLen,"Sei sicuro?");
    while(choiceBreak){
        for(int i=0;i<2;i++){
            if(i==highlight){
                wattron(action, A_REVERSE);
                mvwprintw(action, halfY+3, confirmYN_Pos[i],"%s",confirmYN[i]);
                wattroff(action, A_REVERSE);
            }
        }
        nclearBuff();
        confirmChoice=getch();
        switch(confirmChoice){
            case 'a':
            case 'A':
            case KEY_LEFT:
                if(highlight==0){
                    highlight=1;
                }
                highlight--;
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                if(highlight==1){
                    highlight=0;
                }
                highlight++;
                break;
            case '\n':
                choiceBreak=0;
                break;
        }
        switch(highlight)
        {
            case 0:
                curAction_size--;
                action_buffer=(int *)malloc(curAction_size*sizeof(int));
                break;
            default:
                break;
        }
    }
}

void print_add(int *limitact, int limit_size){
    werase(action);
    box(action, 0,0);
    int isFound=1;
    for(int aidx=0;aidx<limit_size;aidx++){
        for(int i=0;i<18&&isFound;i++){
            if(limitact[aidx]==correctAction[i].id){
                mvwprintw(action, auPad+aidx,alPad,"%s", correctAction[i].name);
                isFound=0;
            }
        }
        isFound=1;
    }
    wrefresh(action);
}
void action_add(){
    switch(sLevel){
        case 1:
            addone();
            return;
            break;
    }
}
void addone(){
    int addBreak=1, limitAction_size, onFocus=0, addchoice=0;
    //int limited_action[]={1, 2, 13, 14, 15, 16}; 
    int limited_action[]={action_IF,action_ENDIF,action_SPARENT,action_EPARENT,action_WALK,action_LROTATE,action_RROTATE,action_ENDSTART, action_isObstacle};
    limitAction_size=sizeof(limited_action)/sizeof(limited_action[0]);
    print_add(limited_action, limitAction_size);
    while(addBreak){
        for(int i=0;i<limitAction_size;i++){
            if(onFocus==i){
                wattron(action, A_REVERSE);
                mvwprintw(action, auPad+i, alPad, "%s",correctAction[limited_action[i]].name);
                wattroff(action, A_REVERSE);
            }else{
                mvwprintw(action, auPad+i, alPad, "%s",correctAction[limited_action[i]].name);;
            }
        }
        addchoice=wgetch(action);
        nclearBuff();
        switch(addchoice){
            case 'w':
            case 'W':
            case KEY_UP:
                if(onFocus==0){
                    onFocus=limitAction_size-1;
                }else{
                    onFocus--;
                }
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                if(onFocus==limitAction_size-1){
                    onFocus=0;
                }else{
                    onFocus++;
                }
                break;
            case '\n':
                werase(action);
                curAction_size++;
                action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
                action_buffer[curAction_size-1]=correctAction[limited_action[onFocus]].id;
                print_action();
                wrefresh(action);
                addBreak=0;
                break;
        }
    }
}