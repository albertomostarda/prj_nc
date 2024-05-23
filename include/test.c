#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>


char ** Hsplit(int HSIZE,char *pText, int padding, int forceNL, int *nLines){
    int textLenght=strlen(pText);
    char **split_txt=NULL;
    if (textLenght > (HSIZE - padding) || forceNL) {
        forceNL = 0;
        int fstSpc = csearch(pText, textLenght / 2, ' ');
        if (fstSpc == -1) {
            fstSpc = textLenght / 2;
        }
        char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
        char *halfStr = (char *)malloc((textLenght - fstSpc) * sizeof(char));
        strncpy(newTxt, pText, fstSpc);
        newTxt[fstSpc] = '\0';
        strcpy(halfStr, pText + fstSpc + 1);
        halfStr[(textLenght - fstSpc) - 1] = '\0';

        split_txt=Hsplit(HSIZE, newTxt, padding, 0, nLines);
        split_txt=Hsplit(HSIZE, halfStr, padding, 0, nLines);

        free(newTxt);
        free(halfStr);
    } else {
        split_txt = (char **)realloc(split_txt,(*nLines) * sizeof(char *));
        split_txt[(*nLines) - 1] = (char *)malloc((textLenght + 1) * sizeof(char));
        strcpy(split_txt[(*nLines) - 1], pText);
        return split_txt;
    }
}


void Hprint(WINDOW *tmp, char *pText, int padding, int forceNL, int *nLines) {
    int hSize = getmaxx(tmp) - getbegx(tmp);
    int cStart = 0, curY = getcury(tmp);
    int textLenght = strlen(pText);

    if (curY == 0) {
        curY = 1;
    }
    if (*nLines == 0) {
        *nLines = 1;
    }

    char **final_txt = Hsplit(hSize,pText,padding,forceNL,nLines);
   

    for (int i = 0; i < *nLines; i++) {
        textLenght = strlen(final_txt[i]);
        cStart = (hSize / 2) - (textLenght / 2);
        mvwprintw(tmp, curY + i, cStart, "%s", final_txt[i]);
        wrefresh(tmp);
        wmove(tmp,curY+1,getbegx(tmp)+1);
    }

    

    for (int i = 0; i < *nLines; i++) {
        free(final_txt[i]);
    }
    free(final_txt);
}
