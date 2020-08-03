#ifndef LZW
#define LZW

#include <stdio.h>
#include "dict.h"

Dict *LZ_initEncDic(char *plainText);
int *LZ_encode(Dict *pEncDic, char *plainText, int *len);
char *LZ_decode(Dict *pEncDic, int *encodedText, int len);

#endif