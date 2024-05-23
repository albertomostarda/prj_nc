#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "features.h"


char** Hsplit(int HSIZE, char *pText, int padding, int forceNL, int *nLines, char **split_txt) {
    int textLength = strlen(pText);

    if (textLength > (HSIZE - padding) || forceNL) {
        forceNL = 0;
        int fstSpc = csearch(pText, textLength / 2, ' ');
        if (fstSpc == -1) {
            fstSpc = textLength / 2;
        }
        char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
        char *halfStr = (char *)malloc((textLength - fstSpc) * sizeof(char));
        strncpy(newTxt, pText, fstSpc);
        newTxt[fstSpc] = '\0';
        strcpy(halfStr, pText + fstSpc + 1);

        split_txt = Hsplit(HSIZE, newTxt, padding, 0, nLines, split_txt);
        split_txt = Hsplit(HSIZE, halfStr, padding, 0, nLines, split_txt);

        free(newTxt);
        free(halfStr);
    } else {
        split_txt = (char **)realloc(split_txt, (*nLines + 1) * sizeof(char *));
        split_txt[*nLines] = (char *)malloc((textLength + 1) * sizeof(char));
        strcpy(split_txt[*nLines], pText);
        (*nLines)++;
    }

    return split_txt;
}

void Hprint(WINDOW *tmp, char *pText, int padding, int forceNL) {
    int hSize = getmaxx(tmp) - getbegx(tmp);
    int curY = getcury(tmp);
    int textLength = strlen(pText);
    int nLines=0;

    if (curY == 0) {
        curY = 1;
    }

    char **final_txt = Hsplit(hSize, pText, padding, forceNL, &nLines, NULL);


    for (int i = 0; i < nLines; i++) {
        textLength = strlen(final_txt[i]);
        int cStart = (hSize / 2) - (textLength / 2);
        mvwprintw(tmp, curY + i, cStart, "%s", final_txt[i]);
        wrefresh(tmp);
        wmove(tmp, curY + i + 1, getbegx(tmp) + 1);
    }

    for (int i = 0; i < nLines; i++) {
        free(final_txt[i]);
    }
    free(final_txt);
}


//////////////////////////////////////////
/////////////////////////////////////////