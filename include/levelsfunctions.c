#include "levelsfunctions.h"
#include "initlevels.h"
#include "levels.h"
#include "herofunctions.h"
#include "dialfunctions.h"
#include <ncurses/ncurses.h>
#include <time.h>

int dReload=0;

void printcolor_str(WINDOW *tWin,char *colStr, int pLines, int tmpY){
    for(int i=0;i<pLines;i++){
        printcolor_char(tWin,colStr[i],i, tmpY);
    }
}
void printcolor_char(WINDOW *tWin,char cch, int locX, int locY){
    switch(cch){
        case '#':
            waddch(tWin, walls);
            break;
        case '0':
            waddch(tWin, blank);
            break;
        case '1':
            if(locY!=-1){
                pg1.locate.x=locX;
                pg1.locate.y=locY;
            }
            setRotation(0);
            waddch(tWin, pg1.icon);
            break;
        case '2':
            waddch(tWin, road);
            break;
        case '3':
            setRotation(1);
            waddch(tWin, pg1.icon);
            break;
        case '4':
            waddch(tWin, goal);
            break;
        default:
            if(cch>='5'){
                enemy_size++;
                enemy=(Ostile *)realloc(enemy, enemy_size*sizeof(Ostile));
                enemy[enemy_size-1].icon=(cch-5)|COLOR_PAIR(3);
                enemy[enemy_size-1].location.y=locY;
                enemy[enemy_size-1].location.x=locX;
                waddch(tWin, enemy[enemy_size-1].icon);
            }
            break;
    }
}
void print_action(){
    int conLenght=0, actY=0, indent=1, isCond=0,canGo=1, checkEnd=0, varPos=0, endStart=0;//
    werase(action);
    box(action, 0,0);
    for(int i=0;i<curAction_size&&canGo;i++){
        if(endStart){
            werase(dialogue);
            box(dialogue,0,0);
            Cprint(dialogue, "Non puoi inserire altre cose dopo il FINE_PROGRAMMA.",1,1,0);
            curAction_size--;
            action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
            endStart=0;
            dReload=1;
        }
        else{
            switch (action_buffer[i])
            {
                case action_START:
                    mvwprintw(action, auPad+actY, alPad,"%s", correctAction[action_buffer[i]].name);
                    actY++;
                    break;
                case action_IF:
                    if(isCond){
                        ifError();
                    }else{
                        mvwprintw(action, auPad+actY, alPad+(3*indent),"%s", correctAction[action_buffer[i]].name);
                        conLenght+=strlen(correctAction[action_buffer[i]].name)+alPad+(3*indent)+1;
                        isCond=-1;
                    }
                    break;
                case action_ENDIF:
                    checkEnd=endIFError(i+1);
                    if(isCond>=0){
                        if(checkEnd==0){
                            if(indent>1){
                                indent--;
                            }
                            mvwprintw(action,auPad+actY,alPad+(3*indent),"%s", correctAction[action_buffer[i]].name);
                            actY++;
                        }else if(checkEnd<0){
                            werase(dialogue);
                            box(dialogue,0,0);
                            Cprint(dialogue,"La struttura 'FINE_SE' va sempre inserita dopo la fine dell'utilizzo del 'SE'",1,1,0);
                            curAction_size--;
                            action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
                            print_action();
                            dReload=1;
                        }
                    }else{
                        werase(dialogue);
                        box(dialogue,0,0);
                        Cprint(dialogue, "Devi inserire una condizione valida",1,1,0);
                        curAction_size--;
                        action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
                        dReload=1;
                    }
                    break;
                case action_ENDSTART:
                    if(indent>1){
                        werase(dialogue);
                        box(dialogue,0,0);
                        Cprint(dialogue, "Il 'FINE_PROGRAMMA' VA inserito alla fine del programma",1,1,0);
                        curAction_size--;
                        action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
                        dReload=1;
                    }else{
                        mvwprintw(action, auPad+actY, alPad,"%s", correctAction[action_buffer[i]].name);
                        actY++;
                        endStart=1;
                    }
                    break;
                default:
                    if(isCond==-1||action_buffer[i]>action_ENDSTART&&action_buffer[i]<action_VAR){
                        if(isCond){
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
                        }else{
                            werase(dialogue);
                            box(dialogue, 0, 0);
                            Cprint(dialogue,"Questa e' una condizione e deve essere inserita solo dopo un 'IF','WHILE,'DO-WHILE'",1,1,0);
                            dReload=1;
                        }
                    }
                    else if(action_buffer[i]>=action_VAR){
                        mvwprintw(action, auPad+actY, alPad+(3*indent),"%s= %d;", correctVar[var_buffer[varPos].type].name,action_buffer[var_buffer[varPos].actIndex]-action_VAR);
                        varPos++;
                        actY++;
                    }else if(conLenght!=0){
                        conLenght+=strlen(correctAction[action_buffer[i-1]].name);
                        mvwprintw(action, auPad+actY, conLenght,"%s", correctAction[action_buffer[i]].name);
                    }else{
                        mvwprintw(action, auPad+actY, alPad+(3*indent),"%s", correctAction[action_buffer[i]].name);
                        actY++;
                    }
                    break;
            }
        }
        wrefresh(action);
    }
}
void ifError(){
    werase(dialogue);
    box(dialogue,0,0);
    Cprint(dialogue,"Non puoi inserire due 'IF' di seguito",1,1,0);
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
void delete_action(int lim) {
    if(curAction_size<=lim){
        werase(dialogue);
            box(dialogue, 0, 0);
            Cprint(dialogue, "Non posso cancellare oltre.", 1, 1, 0);
    }else{
        int halfY = getmaxy(action) / 2;
        int halfX = getmaxx(action) / 2;
        int txtLen = 0, highlight = 0, choiceBreak = 1, confirmChoice = 0;
        char confirmYN[2][5] = {"[SI]\0", "[NO]\0"};
        int confirmYN_Pos[2] = {halfX - 6, halfX + 2};

        werase(action);
        box(action, 0, 0);
        // txtLen = strlen("Stai per eliminare l'ultima istruzione inserita") / 2;
        // mvwprintw(action, halfY - 1, halfX - txtLen, "Stai per eliminare l'ultima istruzione inserita");
        Cprint(action,"Stai per eliminare l'ultima istruzione inserita",1,2,0);
        txtLen = strlen("Sei sicuro?") / 2;
        mvwprintw(action, halfY + 1, halfX - txtLen, "Sei sicuro?");
        mvwprintw(action, halfY + 3, confirmYN_Pos[0], "%s", confirmYN[0]);
        mvwprintw(action, halfY + 3, confirmYN_Pos[1], "%s", confirmYN[1]);
        wrefresh(action);
        while (choiceBreak) {
            for (int i = 0; i < 2; i++) {
                if (i == highlight) {
                    wattron(action, A_REVERSE);
                    mvwprintw(action, halfY + 3, confirmYN_Pos[i], "%s", confirmYN[i]);
                    wattroff(action, A_REVERSE);
                } else {
                    mvwprintw(action, halfY + 3, confirmYN_Pos[i], "%s", confirmYN[i]);
                }
            }
            wrefresh(action);
            confirmChoice = wgetch(action);
            switch (confirmChoice) {
                case 'a':
                case 'A':
                case KEY_LEFT:
                    highlight = (highlight == 0) ? 1 : 0;
                    break;
                case 'd':
                case 'D':
                case KEY_RIGHT:
                    highlight = (highlight == 1) ? 0 : 1;
                    break;
                case '\n':
                    choiceBreak = 0;
                    break;
            }
        }

        if (highlight == 0) {
            halfY = getmaxy(dialogue) / 2;
            halfX = getmaxx(dialogue) / 2;
            if(action_buffer[curAction_size-1]>=action_VAR){
                var_size--;
                var_buffer=(linked_var *)realloc(var_buffer, var_size*sizeof(linked_var));
            }
            curAction_size--;
            action_buffer = (int *)realloc(action_buffer, curAction_size * sizeof(int));
            napms(500);
            werase(dialogue);
            box(dialogue, 0, 0);
            Cprint(dialogue, "Istruzione Eliminata con successo.", 1, 1, 0);
        }
        nclearBuff();
        print_action();
    }
}
void print_add(int *limitact, int limit_size){
    werase(action);
    box(action, 0,0);
    int isFound=1;
    for(int aidx=0;aidx<limit_size;aidx++){
        for(int i=0;i<12&&isFound;i++){
            if(limitact[aidx]==correctAction[i].id){
                mvwprintw(action, auPad+aidx,alPad,"%s", correctAction[i].name);
                isFound=0;
            }
        }
        isFound=1;
    }
    wrefresh(action);
}
// void action_add(){
//     switch(sLevel){
//         case 2:
//             addone();
//             return;
//             break;
//     }
// }
int *createAlimit(int *limSize){
    int *aLimit=(int *)malloc(sizeof(int));
    switch(sLevel){
        case 1:
            *limSize=3;
            aLimit=(int *)realloc(aLimit,(*limSize)*sizeof(int));
            aLimit[0]=action_WALK;
            aLimit[1]=action_ENDSTART;
            aLimit[2]=action_VAR;
            break;
        case 2:
            *limSize=4;
            aLimit=(int *)realloc(aLimit,(*limSize)*sizeof(int));
            aLimit[0]=action_WALK;
            aLimit[1]=action_LROTATE;
            aLimit[2]=action_RROTATE;
            aLimit[3]=action_ENDSTART;
            break;
        case 3:
            *limSize=7;
            aLimit=(int *)realloc(aLimit,(*limSize)*sizeof(int));
            aLimit[0]=action_IF;
            aLimit[1]=action_ENDIF;
            aLimit[2]=action_WALK;
            aLimit[3]=action_LROTATE;
            aLimit[4]=action_RROTATE;
            aLimit[5]=action_ENDSTART;
            aLimit[6]=action_isObstacle;
            break;
        case 4:

            break;
        case 5:
            break;
    }
    return aLimit;
}
void addone(){
    int addBreak=1, limitAction_size=0, onFocus=0, addchoice=0;
    //int limited_action[]={1, 2, 13, 14, 15, 16};
    int *limited_action=createAlimit(&limitAction_size);
    print_add(limited_action, limitAction_size);
    while(addBreak){
        for(int i=0;i<limitAction_size;i++){
            if(onFocus==i){
                wattron(action, A_REVERSE);
                mvwprintw(action, auPad+i, alPad, "%s",correctAction[limited_action[i]].name);
                wattroff(action, A_REVERSE);
                werase(dialogue);
                box(dialogue,0,0);
                Cprint(dialogue,correctAction[limited_action[i]].descr, 1,1,0);
            }else{
                mvwprintw(action, auPad+i, alPad, "%s",correctAction[limited_action[i]].name);
            }
        }
        wrefresh(action);
        nclearBuff();
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
                if(correctAction[limited_action[onFocus]].id==action_VAR){
                    addVar(&addBreak);
                }else{
                    curAction_size++;
                    action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
                    action_buffer[curAction_size-1]=correctAction[limited_action[onFocus]].id;
                }
                print_action();
                wrefresh(action);
                addBreak=0;
                break;
            case 'q':
            case 'Q':
                print_action();
                addBreak=0;
                break;
        }
    }
    //aggiungere reset dialoghi
}
void addVar(int *qAdd){
    int limvar_size=1, value=0, vBreak=1, var_val=0;
    int* lim_var=NULL;
    switch(sLevel){
        case 1:
            limvar_size=1;
            lim_var=(int *)realloc(lim_var, limvar_size*sizeof(int));
            lim_var[0]=var_nSteps;
            break;
        // case 2:
        //     limvar_size=0;
        //     break;
        // case 3:
        //     break;
        // case 4:
        //     break;
        // case 5:
        //     break;
        default:
            limvar_size=0;
            break;
    }
    if(limvar_size!=0){
        int high=0, vChoice=0;
        print_addVar(lim_var, limvar_size);
        while(vBreak){
            for(int i=0;i<limvar_size;i++){
                if(high==i){
                    wattron(action, A_REVERSE);
                    mvwprintw(action, auPad+i, alPad, "%s", correctVar[lim_var[i]].name);
                    wattroff(action, A_REVERSE);
                    werase(dialogue);
                    box(dialogue,0,0);
                    Cprint(dialogue, correctVar[lim_var[i]].descr, 1,1,0);
                }else{
                    mvwprintw(action, auPad+i, alPad, "%s", correctAction[lim_var[i]].name);
                }
            }
            wrefresh(action);
            nclearBuff();
            vChoice=wgetch(action);
            nclearBuff();
            switch (vChoice)
            {
                case 'w':
                case 'W':
                case KEY_UP:
                    if(high==0){
                        high=limvar_size-1;
                    }else{
                        high--;
                    }
                    break;
                case 's':
                case 'S':
                case KEY_DOWN:
                    if(high==limvar_size-1){
                        high=0;
                    }else{
                        high++;
                    }
                    break;
                case '\n':
                    var_val=addValue();
                    if(var_val!=0){
                        curAction_size++;
                        action_buffer=(int *)realloc(action_buffer, curAction_size*sizeof(int));
                        action_buffer[curAction_size-1]=var_val+action_VAR;
                        var_size++;
                        var_buffer=(linked_var *)realloc(var_buffer, var_size*sizeof(linked_var));
                        var_buffer[var_size-1].type=lim_var[high];
                        var_buffer[var_size-1].actIndex=curAction_size-1;
                        vBreak=0;
                        *qAdd=0;
                    }else{
                        print_addVar(lim_var, limvar_size);
                    }
                    break;
                case 'q':
                case 'Q':
                    return;
                    break;
            }
        }
    }
}
void print_addVar(int *var_limited, int lVar_size){
    int isFound=1;
    werase(action);
    box(action,0,0);
    for(int i=0;i<lVar_size;i++){
        for(int j=0;isFound&&j<2;j++){
            if(var_limited[i]==correctVar[j].id){
                mvwprintw(action, auPad+i, alPad, "%s", correctVar[var_limited[i]].name);
                isFound=0;
            }
        }
        isFound=1;
    }
    wrefresh(action);
}
void print_addValue(int *val_limit, int lVal_size){
    werase(action);
    box(action,0,0);
    for(int i=0;i<lVal_size;i++){
        mvwprintw(action, auPad+i, alPad, "%d", val_limit[i]);
    }
    wrefresh(action);
}
int addValue(){
    int valBreak=1, val_size=0, focus=0, valCho=0;
    int *val_lim=NULL;
    switch(sLevel){
        case 1:
            val_size=2;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }
    if(val_size!=0){
        val_lim=(int *)realloc(val_lim, val_size*sizeof(int));
        for(int i=0;i<val_size;i++){
            val_lim[i]=i+1;
        }
        print_addValue(val_lim, val_size);
        while(valBreak){
            for(int i=0;i<val_size;i++){
                if(i==focus){
                    wattron(action,A_REVERSE);
                    mvwprintw(action, auPad+i,alPad,"%d", val_lim[i]);
                    wattroff(action, A_REVERSE);
                }else{
                    mvwprintw(action, auPad+i,alPad,"%d", val_lim[i]);
                }
            }
            nclearBuff();
            valCho=wgetch(action);
            nclearBuff();
            switch (valCho)
            {
                case 'W':
                case 'w':
                case KEY_UP:
                    if(focus==0){
                        focus=val_size-1;
                    }else{
                        focus--;
                    }
                    break;
                case 'S':
                case 's':
                case KEY_DOWN:
                    if(focus==val_size-1){
                        focus=0;
                    }else{
                        focus++;
                    }
                    break;
                case '\n':
                    return val_lim[focus];
                    break;
                case 'q':
                case 'Q':
                    return 0;
                    break;
            }
        }
    }
}
void run_actions(int *fexit){
    int i=1,vidx=0;
    if(action_buffer[curAction_size-1]==action_ENDSTART){
        while(action_buffer[i]!=action_ENDSTART){
            switch (action_buffer[i])
            {
                case action_IF:
                    i=if_run(action_buffer[i+1],i+1);
                    break;
                case action_WHILE:
                    i=while_run(action_buffer[i+1],i+1);
                    break;
                case action_DO:
                    i=do_run(action_buffer[i+1],i+1);
                    break;
                case action_WALK:
                    walk();
                    break;
                case action_RROTATE:
                    rotclock();
                    break;
                case action_LROTATE:
                    rotcclock();
                    break;
                case action_attack:
                    if(attack()){
                        werase(dialogue);
                        box(dialogue,0,0);
                        Cprint(dialogue, "Non puoi attaccare a vuoto!",1,1,0);
                        dReload=1;
                    }
                    break;
                default:
                    if(action_buffer[i]>=action_VAR){
                        switch(var_buffer[vidx].type){
                            case var_nSteps:
                                set_steps(action_buffer[var_buffer[vidx].actIndex]-action_VAR);
                                break;
                        }
                        vidx++;
                    }
            }
            i++;
        }
        print_map(map);
        print_action();
        *fexit=checkEndLvl();
        nclearBuff();
        // Cprint(dialogue,"eseguito con successo",1,1,0);
    }else{
        werase(dialogue);
        box(dialogue,0,0);
        Cprint(dialogue, "Devi inserire alla fine del programma 'FINE_PROGRAMMA' per farlo funzionare.",1,1,1);
        dReload=1;
    }
}
void action_run(){
    int choice=0, highlight=0, fBreak=1;
    keypad(action, TRUE);
    //nodelay(action, TRUE);
    while(fBreak){
        for(int i=0;i<4;i++){
            if(i==highlight){
                wattron(action, A_REVERSE);
                mvwprintw(action, choicePos[i].y,choicePos[i].x,"%s",action_choice[i]);
                wattroff(action, A_REVERSE);
            }else{
                mvwprintw(action, choicePos[i].y,choicePos[i].x,"%s",action_choice[i]);
            }
        }
        nclearBuff();
        choice=wgetch(action);
        nclearBuff();
        switch(choice){
            case 'a':
            case 'A':
            case KEY_LEFT:
                if(highlight==0){
                    highlight=3;
                }else{
                    highlight--;
                }
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                if(highlight==3){
                    highlight=0;
                }else{
                    highlight++;
                }
                break;
            case '\n':
                action_subrun(highlight,&fBreak);
                if(fBreak){
                    if(dReload){
                        reloadDialogue();
                        printOneDLine();
                    }else{
                        printOneDLine();
                    }
                }
                break;
            case 'P':
            case 'p':
                if(dialPos>0&&isEmpty==0){
                    dialPos--;
                }
                printOneDLine();
                break;
            case 'N':
            case 'n':
                if(dialPos<dialBuff_size-1&&isEmpty==0){
                    dialPos++;
                }
                printOneDLine();
                break;
        }
    }
    //nodelay(action, FALSE);
}
void action_subrun(int status,int *EXITflag){
    switch (status)
    {
        case 0:
            addone();
            break;
        case 1:
            delete_action(levelLimitation);
            break;
        case 2:
            run_actions(EXITflag);
            break;
        case 3:
            *EXITflag=0;
            break;
    }
    return ;
}
void run_anim(WINDOW *tmp){
    napms(100);
    werase(tmp);
    box(tmp, 0,0);
    Cprint(tmp, "Esecuzione in corso -",1,1,0);
    wrefresh(tmp);
    napms(100);
    Cprint(tmp, "Esecuzione in corso \\",1,1,0);
    wrefresh(tmp);
    napms(100);
    Cprint(tmp, "Esecuzione in corso |",1,1,0);
    wrefresh(tmp);
    napms(100);
    Cprint(tmp, "Esecuzione in corso /",1,1,0);
    wrefresh(tmp);
    napms(100);
    Cprint(tmp, "Esecuzione in corso -",1,1,0);
    wrefresh(tmp);
}
void print_map(WINDOW *tmp){
    int wBegy=0,wBegx=0, uPad=1,lPad=26;
    getbegyx(tmp, wBegy, wBegx);
    werase(tmp);
    box(tmp,0,0);
    for(int i=0;i<22;i++){
        wmove(tmp,wBegy+uPad+i,wBegx+lPad);
        printcolor_str(tmp,mapArr[i], strlen(mapArr[i]), -1);
        wrefresh(tmp);
    }
}
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
void setRotation(int isEnd){
    if(isEnd){
        switch (pg1.rotation)
        {
            case 0:
                pg1.icon='^'|COLOR_PAIR(8);
                break;
            case 1:
                pg1.icon='>'|COLOR_PAIR(8);
                break;
            case 2:
                pg1.icon='V'|COLOR_PAIR(8);
                break;
            case 3:
                pg1.icon='<'|COLOR_PAIR(8);
                break;
        }
    }else{
        switch (pg1.rotation)
        {
            case 0:
                pg1.icon='^'|COLOR_PAIR(7);
                break;
            case 1:
                pg1.icon='>'|COLOR_PAIR(7);
                break;
            case 2:
                pg1.icon='V'|COLOR_PAIR(7);
                break;
            case 3:
                pg1.icon='<'|COLOR_PAIR(7);
                break;
        }
    }
}
int checkEndLvl(){
    //int cho='\0';
    time_t swait=time(NULL);
    if(mapArr[pg1.locate.y][pg1.locate.x]!='3'|| isWalkEnd==0){
        werase(dialogue);
        box(dialogue,0,0);
        if(isWalkEnd==0){
            Cprint(dialogue, "Hai camminato oltre il traguardo, e quindi sei andato a sbattere contro il muro. Riprova!",1,1,1);
        }else{
            Cprint(dialogue, "Non hai raggiunto il traguardo. Premi INVIO per ritentare",1,1,1);
        }
        nclearBuff();
        wmove(action,getcury(action), getcurx(action));
        nodelay(action,TRUE);
        while(wgetch(action)&&(time(NULL)-swait)<10);
        nclearBuff();
        nodelay(action,FALSE);
        mapArr=init_map(26,1);
        switch (sLevel)
        {
            case 1:
            case 2:
            case 3:
                pg1.rotation=0;
                break;
        }
        // free(action_buffer);
        werase(dialogue);
        box(dialogue,0,0);
        wrefresh(dialogue);
        init_action();
        print_map(map);
        print_action();
        return 1;
    }else{
        werase(dialogue);
        werase(action);
        werase(map);
        delwin(dialogue);
        delwin(map);
        delwin(action);
        werase(stdscr);
        box(stdscr,0,0);
        Cprint(stdscr,"Hai superato il livello!",1,1,0);
        mvwprintw(stdscr,getcury(stdscr)+1,(getmaxx(stdscr)/2)-(strlen("CONGRATULAZIONI!")/2),"CONGRATULAZIONI!");
        wrefresh(stdscr);
        if(lvlToDo<=sLevel){
            switch(sLevel){
                case 1:
                    lvlToDo=2;
                    break;
                case 2:
                    lvlToDo=3;
                    break;
            }
        }
        nodelay(stdscr,TRUE);
        nclearBuff();
        while(getch()!='\n'&&(time(NULL)-swait)<10);
        nclearBuff();
        nodelay(stdscr,FALSE);
        return 0;
    }
}
void reloadDialogue(){
    time_t countDwn=time(NULL);
    int inputCh=0;
    SBHprint(dialogue, pContinue,1);
    nodelay(stdscr,TRUE);
    nclearBuff();
    while(getch()!='\n'&&(time(NULL)-countDwn)>10);
    nclearBuff();
    nodelay(stdscr,FALSE);
    dReload=0;
}