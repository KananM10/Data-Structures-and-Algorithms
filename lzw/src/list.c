#include "list.h"

//----------------------------------------------------------------------------------------------------

List *L_new(char *key, int value) {
    List *new = (List *) malloc(sizeof(List));
    new->key = key;
    new->value = value;
    new->pNext = NULL;
    return new;
}

//----------------------------------------------------------------------------------------------------


int L_append(List **ppHead, char *key, int value) {

    if (*(ppHead) == NULL) {
        *(ppHead) = L_new(key, value);
        return 1;
    }

    List *temp = *ppHead;
    while (temp->pNext != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return 0;
        }
        temp = temp->pNext;
    }

    temp->pNext = L_new(key, value);
    return 1;
}

//----------------------------------------------------------------------------------------------------

int L_search(List *pHead, char *key) {
    if (pHead == NULL)
        return -1;
        
    List *temp = pHead;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->pNext;
    }
    return -1;
}

//----------------------------------------------------------------------------------------------------

int L_getIndex(List *list, char *key) {
    List *temp = list;
    int c = 0;
    
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0)
            return c;
        temp = temp->pNext;
        c++;
    }
}

//----------------------------------------------------------------------------------------------------

char *L_getAt(List *list, int index) {
    List *temp = list;
    while (temp != NULL) {
        if (temp->value == index) {
            return temp->key;
        }
        temp = temp->pNext;
    }
    return "";
}

//----------------------------------------------------------------------------------------------------

void L_print(List *pHead) {
    List *temp = pHead;
    while (temp != NULL) {
        printf("\t{ %s : %d }\n", temp->key, temp->value);
        temp = temp->pNext;
    }
}