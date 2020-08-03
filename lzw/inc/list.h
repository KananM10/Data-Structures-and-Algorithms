#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
    char *key;
    int value;
    struct list *pNext;
}List;

List *L_new(char *key, int value);
int L_append(List **ppHead, char *key, int value);
int L_search(List *pHead, char *key);
void L_print(List *pHead);
int L_getIndex(List *list, char *key);
char *L_getAt(List *list, int index);

#endif