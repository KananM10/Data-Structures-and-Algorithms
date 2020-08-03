#include <stdio.h>
#include <string.h>
#include "lzw.h"

int main() {
    char *text = "si ton tonton tond mon tonton";
    Dict *lzw = LZ_initEncDic(text);
    Dict *lzwCpy = D_duplicate(lzw);
    printf("-------------------------------------------------------------\n");
    printf("Initial text is: %s\n", text);
    int len = 0;
    int *arrEnc = LZ_encode(lzw, text, &len);
    printf("-------------------------------------------------------------\n");
    printf("ENCODED: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", arrEnc[i]);
    }
    puts("");
    char *arrDec = LZ_decode(lzwCpy, arrEnc, len);
    printf("-------------------------------------------------------------\n");
    printf("DECODED: ");
    for (int i = 0; i < strlen(arrDec); i++) {
        printf("%c", arrDec[i]);
    }
    printf("\n");
}

