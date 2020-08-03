#include "lzw.h"

//----------------------------------------------------------------------------------------------------

Dict *LZ_initEncDic(char *plainText) {
    Dict *init = D_new(strlen(plainText));

    int count = 0;
    for (int i = 0; i < strlen(plainText); i++) {
        char *str = (char *) malloc(2*sizeof(str));
        str[0] = plainText[i];
        str[1] = '\0';
        if (D_put(init, str, count)) 
            count++;
    }

    return init;
}

//----------------------------------------------------------------------------------------------------

int *LZ_encode(Dict *pEncDic, char *plainText, int *len) {
    int curIndex = 0;
    int *ret = (int *) malloc(256*sizeof(int));
    char *p = (char *) malloc((strlen(plainText))*sizeof(char));
    char *c = (char *) malloc(2*sizeof(char));
    p[0] = '\0';
    c[0] = '\0';
    for (int i = 0; i < strlen(plainText); i++) {
        if (i != 0)
            strncat(c, &(plainText[i]), 1);
        char *t = (char *) malloc((strlen(p)+strlen(c)+1)*sizeof(char));
        t[0] = '\0';
        strncat(t, p, strlen(p));
        strncat(t, c, strlen(c));
        if (D_search(pEncDic, t) != -1) {
            strncat(p, c, strlen(c));
        } else {
            ret[curIndex++] = D_getIndex(pEncDic, p);
            (*len)++;
            D_put(pEncDic, t, pEncDic->size+1);
            strcpy(p, c);
        }
        strncpy(c, "", sizeof(c));
    }
    ret[curIndex++] = D_getIndex(pEncDic, p);
    (*len)++;
    return ret;
}

//----------------------------------------------------------------------------------------------------

char *LZ_decode(Dict *pEncDic, int *encodedText, int len) {
    char *result = (char *) malloc(256*sizeof(char));
    result[0] = '\0';
    int old = encodedText[0];
    int new;
    char *s = (char *) malloc(256*sizeof(char));
    s[0] = '\0';
    char *oldTrans = D_getAt(pEncDic, old);
    strncat(s, oldTrans, strlen(oldTrans));
    char *c = (char *) malloc(2*sizeof(char));
    c[0] = s[0];
    c[1] = '\0';
    strncat(result, s, strlen(s));
    for (int i = 0; i < len - 1; i++) {
        oldTrans = D_getAt(pEncDic, old);
        new = encodedText[i + 1];
        if (new > pEncDic->size) {
            s = oldTrans;
            strncat(s, c, strlen(c));
        } else
            s = D_getAt(pEncDic, new);
        strncat(result, s, strlen(s));
        c[0] = s[0];
        c[1] = '\0';
        char *t = (char *) malloc((strlen(oldTrans)+strlen(c)+1)*sizeof(char));
        t[0] = '\0';
        strncat(t, oldTrans, strlen(oldTrans));
        strncat(t, c, strlen(c));
        D_put(pEncDic, t, pEncDic->size);
        old = new;
    }
    return result;
}
