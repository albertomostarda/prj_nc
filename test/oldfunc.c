// void Hprint(WINDOW *tmp, char *pText, int padding, int forceNL){
//     int hSize= getmaxx(tmp)-getbegx(tmp);
//     int cStart=0, curY=getcury(tmp);
//     int textLength = strlen(pText);
//     if(curY==0){
//         curY=1;
//     }
//     if (textLength > (hSize - padding) || forceNL) {
//         forceNL=0;
//         int fstSpc = csearch(pText, textLength / 2, ' ');
//         if (fstSpc == -1) {
//             fstSpc = textLength / 2;
//         }
//         char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
//         char *halfStr = (char *)malloc((textLength - fstSpc) * sizeof(char));
//         strncpy(newTxt, pText, fstSpc);
//         newTxt[fstSpc] = '\0';
//         strcpy(halfStr, pText + fstSpc + 1);
//         halfStr[(textLength - fstSpc)-1]='\0';
//         Hprint(tmp, newTxt, padding,0);
//         Hprint(tmp, halfStr, padding, 0);
//         free(newTxt);
//         free(halfStr);
//     } else {
//         cStart=(hSize/2)-(textLength/2);
//         mvwprintw(tmp, curY, cStart,"%s", pText);
//         wrefresh(tmp);
//         wmove(tmp,curY+1,getbegx(tmp)+1);
//     }
// }

// void Cprint(WINDOW *tmp, char *pText, int hPad, int vPad, int fNL, int nHline){
//     int hSize= getmaxx(tmp)-getbegx(tmp);
//     int vSize= getmaxy(tmp)-getbegy(tmp);
//     int hStart=0;
//     int curY=getcury(tmp);
//     int textLength = strlen(pText);
//     if(curY<=vPad){
//         curY=vPad+1;
//     }
//     if (textLength > (hSize - hPad) || fNL) {
//         fNL=0;
//         int fstSpc = csearch(pText, textLength / 2, ' ');
//         if (fstSpc == -1) {
//             fstSpc = textLength / 2;
//         }
//         char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
//         char *halfStr = (char *)malloc((textLength - fstSpc) * sizeof(char));
//         strncpy(newTxt, pText, fstSpc);
//         newTxt[fstSpc] = '\0';
//         strcpy(halfStr, pText + fstSpc + 1);
//         halfStr[(textLength - fstSpc)-1]='\0';
//         Cprint(tmp, newTxt, hPad,vPad, 0, nHline++);
//         Cprint(tmp, halfStr, hPad,vPad, 0, nHline++);
//         free(newTxt);
//         free(halfStr);
//     } else {
//         hStart=(hSize/2)-(textLength/2);
//         mvwprintw(tmp, curY, cStart,"%s", pText);
//         wrefresh(tmp);
//         wmove(tmp,curY+1,getbegx(tmp)+1);
//     }
// }