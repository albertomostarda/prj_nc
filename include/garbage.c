// # herofunction
//  int if_run(int nxtPos, int *varPos, int *OnElse){
//     int idx=nxtPos+1, cond=action_buffer[nxtPos], nestElse=0, canRun=0;
//     switch(cond){
//         case action_isObstacle:
//             canRun=checkObstacle();
//             break;
//         case action_isEnemy:
//             canRun=checkEnemy();
//             break;
//         case action_isNotGoal:
//             canRun=checkNGoal();
//             break;
//     }
//     if(cond){
//         while(action_buffer[idx]!=action_ENDIF){
//             switch(action_buffer[idx]){
//                 case action_IF:
//                     nestElse=enable_else(action_buffer[idx+1]);
//                     idx=if_run(idx+1, varPos, &nestElse);
//                     break;
//                 case action_ELSE:
//                     idx=else_run(idx+1, varPos,&nestElse);
//                     break;
//                 case action_WHILE:
//                 case action_DO:
//                     idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1, varPos);
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
//                         switch(var_buffer[*varPos].type){
//                                 case var_nSteps:
//                                     set_steps(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
//                                     break;
//                                 case var_nTurns:
//                                     set_turns(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
//                                     break;
//                             }
//                             (*varPos)++;
//                     }
//                     break;
//             }
//             idx++;
//         }
//     }
//     return getEndStruct(idx-1, 1);
// }
// int enable_else(int cond){
//     int canRun=1;
//     switch(cond){
//         case action_isObstacle:
//             canRun=checkObstacle();
//             break;
//         case action_isEnemy:
//             canRun=checkEnemy();
//             break;
//         case action_isNotGoal:
//             canRun=checkNGoal();
//             break;
//         default:
//             canRun=1;
//             break;
//     }
//     return !canRun;
// }
// int else_run(int nxtIns, int *varPos, int *fEnable){
//     int idx=nxtIns, nestCond=0;
//     if(*fEnable){
//         while (action_buffer[idx]!=action_ENDELSE)
//         {
//             switch(action_buffer[idx]){
//                 case action_IF:
//                     idx=if_run(idx+1, varPos, &nestCond);
//                     break;
//                 case action_ELSE:
//                     idx=else_run(idx+1, varPos,&nestCond);
//                     break;
//                 case action_WHILE:
//                 case action_DO:
//                     idx=cicle_run(action_buffer[idx],action_buffer[idx+1], idx+1, varPos);
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
//                         switch(var_buffer[*varPos].type){
//                                 case var_nSteps:
//                                     set_steps(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
//                                     break;
//                                 case var_nTurns:
//                                     set_turns(action_buffer[var_buffer[*varPos].actIndex]-action_VAR);
//                                     break;
//                             }
//                             (*varPos)++;
//                     }
//                     break;
//             }
//             idx++;
//         }
//         *fEnable=0;
//     }
//     return getEndStruct(idx-1,2);
// }
// int getEndStruct(int posi, int type) {
//     actionCode caseCode, startCode;
//     int nestLevel = 0;
//     // Determina il codice di inizio e di fine struttura in base al tipo
//     switch(type){
//         case 1:
//             caseCode = action_ENDIF;
//             startCode = action_IF;
//             break;
//         case 2:
//             caseCode = action_ENDELSE;
//             startCode = action_ELSE;
//             break;
//         case 3:
//             caseCode = action_ENDCICLE;
//             startCode = action_WHILE; // Presupponiamo che ci sia un ciclo tipo WHILE o DO
//             break;
//         default:
//             return posi; // Caso di errore, ritorna la posizione attuale
//     }
//     // Scorre attraverso l'action buffer finché non trova il corrispondente END
//     while (posi < curAction_size) {
//         // Se si trova una nuova struttura di inizio (ad esempio un altro IF annidato)
//         if (action_buffer[posi] == startCode) {
//             nestLevel++; // Aumenta il livello di annidamento
//         }
//         // Se si trova la corrispondente fine struttura (ad esempio ENDIF)
//         if (action_buffer[posi] == caseCode) {
//             if (nestLevel == 0) {
//                 // Se non ci sono più annidamenti, termina la funzione
//                 return posi;
//             } else {
//                 // Se ci sono ancora annidamenti, diminuisce il livello
//                 nestLevel--;
//             }
//         }
//         posi++;
//     }
//     // Ritorna la posizione trovata, meno 1 per allinearsi alla logica esistente
//     return posi - 1;
// }
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
// # levelfunction
// void action_add(){
//     switch(sLevel){
//         case 2:
//             addone();
//             return;
//             break;
//     }
// }
// # initlevels
// void free_actionBND(){
//     for(int i=0;i<12;i++){
//         if (correctAction[i].name != NULL) {
//             free(correctAction[i].name);
//             correctAction[i].name=NULL;
//         }
//         if (correctAction[i].descr != NULL) {
//             free(correctAction[i].descr);
//             correctAction[i].descr=NULL;
//         }
//     }
// }
// void free_varBND(){
//     for(int i = 0; i < 2; i++){ // Iterate only over initialized elements
//         if (correctVar[i].name != NULL) {
//             free(correctVar[i].name);
//             correctVar[i].name = NULL;
//         }
//         if (correctVar[i].descr != NULL) {
//             free(correctVar[i].descr);
//             correctVar[i].descr = NULL;
//         }
//     
// }
// # features
//ConsoleSize defaultSize;
//jmp_buf env;
// void resize_handler(){
//     time_t sContinue;
//     SHORT cols = 0, rows = 0;
//     CONSOLE_SCREEN_BUFFER_INFO csbi;
//     SMALL_RECT def={0,0,160,35};

//     while (1) {
//         GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//         rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
//         cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

//         if (rows != 35 || cols != 160) {
//             COORD coord = { 160, 35 };
//             SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//             SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &def);
//             system("MODE 160,35");
//         }
//         Sleep(100);
//     }
// }
// char *getPath() {
//     int j=0;
//     char *path = (char *)malloc(max_path * sizeof(char));
//     if (path == NULL) {
//         printw("Percorso non allocato");
//         refresh();
//         napms(5000);
//         return NULL;
//     }
//     ssize_t len = readlink("/proc/self/exe", path, max_path - 1);
//     for (ssize_t i = len - 1; i >= 0; i--) {
//         if (path[i] == '/') {
//             path[i] = '\0';
//             break;
//         }
//     }
//     char *exePath = (char *)malloc(strlen(path) + 1);
//     strcpy(exePath, path);
//     return exePath;
// }
// void handle_resize(int sig){
//     if(curState==fSTART){
//         //ipotetica chiamata del salto
//     }
//     else if(curState==fRUN){
//     }
// }
// int fCountCols(FILE *tmpFile){
//     int fCols=0;
//     char eFlag='\0';
//     while((eFlag=fgetc(tmpFile))!='\n'){
//         fCols++;
//     }
//     rewind(tmpFile);
//     return fCols;
// }
// void freeabuffer(){
//     // free(var_buffer);
//     // free(action_buffer);
//     // curAction_size=1;
//     // var_size=1;
//     for(int i=0;i<12;i++){
//         free(correctAction[i].name);
//         free(correctAction[i].descr);
//     }
// }
// # dialfunction
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