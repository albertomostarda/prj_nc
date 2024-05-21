#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int csearch(char *sample, int start, char find) {
    for (int i = start; i < strlen(sample); i++) {
        if (sample[i] == find) {
            return i;
        }
    }
    return -1; // Ritorna -1 se il carattere non viene trovato
}

void Hprint(int maxspc, char *pText, int padding, int forceNL) {
    int textLength = strlen(pText);
    if (textLength > (maxspc - padding) || forceNL) {
        int fstSpc = csearch(pText, textLength / 2, ' ');
        if (fstSpc == -1) {
            fstSpc = textLength / 2; // Se non trova uno spazio, taglia a metà
        }
        char *newTxt = (char *)malloc((fstSpc + 1) * sizeof(char));
        char *halfStr = (char *)malloc((textLength - fstSpc) * sizeof(char));
        
        strncpy(newTxt, pText, fstSpc);
        newTxt[fstSpc] = '\0'; // Termina correttamente la stringa
        
        strcpy(halfStr, pText + fstSpc + 1);
        
        printf("%s\n", newTxt);
        Hprint(maxspc, halfStr, padding, 0);
        
        free(newTxt);
        free(halfStr);
    } else {
        printf("%s", pText);
    }
}
static char *pre = "freccette direzionali sia i tasti WASD. Buona Programmazione";
int main() {
    static char *initTxt = "Per navigare durante tutto il gioco si possono utilizzare sia le freccette direzionali sia i tasti WASD. Buona Programmazione";
    Hprint(160, initTxt, 20, 0);
    getchar();
    return 0;
}
