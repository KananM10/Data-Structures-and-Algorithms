#include "dict.h"

//----------------------------------------------------------------------------------------------------

Dict *D_new(int cap) {
    Dict *dict = (Dict *) malloc(sizeof(Dict));
    dict->size = 0;
    dict->capacity = cap;
    dict->table = (List **) malloc(sizeof(List *));
    *(dict->table) = NULL;
    return dict;
}
//----------------------------------------------------------------------------------------------------

int D_put(Dict *dict, char *key, int value) {
    if (dict->size == 0) {
        *(dict->table) = L_new(key, value);
        dict->size++;
        return 1;
    }

    if (D_search(dict, key) != -1)
        return 0;

    L_append(dict->table, key, value);
    dict->size++;
    return 1;
}

//----------------------------------------------------------------------------------------------------

int D_search(Dict *dict, char *key) {
    return L_search(*(dict->table), key);
}

//----------------------------------------------------------------------------------------------------

Dict *D_duplicate(Dict *dict) {
    Dict *new = D_new(dict->capacity);

    List *temp = *(dict->table);
    while (temp != NULL) {
        D_put(new, temp->key, temp->value);
        temp = temp->pNext;
    }

    return new;
}

//----------------------------------------------------------------------------------------------------

int D_getIndex(Dict *dict, char *key) {
    return L_getIndex(*(dict->table), key);
}

//----------------------------------------------------------------------------------------------------

char *D_getAt(Dict *dict, int index) {
    return L_getAt(*(dict->table), index);
}

//----------------------------------------------------------------------------------------------------

void D_print(Dict *dict) {
    puts("[");
    L_print(*(dict->table));
    puts("]");
}