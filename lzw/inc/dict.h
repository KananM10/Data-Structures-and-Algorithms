#ifndef __DICT_H__
#define __DICT_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct dict{
    List **table;
    int capacity;
    int size;
}Dict;


Dict *D_new(int);
int D_put(Dict *dict, char *key, int value); 
int D_search(Dict *dict, char *key);
Dict *D_duplicate(Dict *dict);
void D_print(Dict *dict);
int D_getIndex(Dict *dict, char *key);
char *D_getAt(Dict *dict, int index);

#endif