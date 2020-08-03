#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

//------------------------------------------------------------------

/* 
 * structures of linked list and hashtable
 */

typedef struct LLNode {
    char *word;
    struct LLNode *pNext;
}LLNode;

typedef struct HashTable {
    int size;
    LLNode **table;
}HashTable;


//------------------------------------------------------------------
/* 
 * function to create new linked list
 */

LLNode *LL_new(char *word) {
    LLNode *newNode = (LLNode *) malloc(sizeof(LLNode));
    newNode->word = word;
    newNode->pNext = NULL;
    return newNode;
}

//------------------------------------------------------------------
/* 
 * function to add item to linked list
 */

void LL_add(LLNode **ppHead, char *word) {
    LLNode *newNode = LL_new(word);
    newNode->pNext = *ppHead;
    *ppHead = newNode;
}

//------------------------------------------------------------------
/* 
 * function to print linked list
 */

void LL_print(LLNode *pHead) {
    if (pHead == NULL) {
        puts("");
        return;
    }

    while (pHead != NULL) {
        printf("[%s] => ", pHead->word);
        pHead = pHead->pNext;
    }
    puts("");
}

//------------------------------------------------------------------
/* 
 * function to remove an item from linked list
 */

void LL_remove(LLNode **ppHead, char *txt) {
    if (*ppHead == NULL) {
        return;
    }

    if (strcmp((*ppHead)->word, txt) == 0) {
        *ppHead = (*ppHead)->pNext;
        return;
    }

    LLNode *temp = *ppHead;
    while (temp->pNext != NULL) {
        if (strcmp(temp->pNext->word, txt) == 0) {
            temp->pNext = temp->pNext->pNext;
            break;
        }
        temp = temp->pNext;
    }
}

//------------------------------------------------------------------
/* 
 * function to get linked list size
 */

int LL_size(LLNode *pHead) {
    LLNode *temp = pHead;
    int size = 0;
    while (temp != NULL) {
        size++;
        temp = temp->pNext;
    }
    return size;
}

//------------------------------------------------------------------
/* 
 * function to create new hashtable
 */

HashTable *HASH_new(int size) {
    HashTable *hT = (HashTable *) malloc(sizeof( HashTable));

    hT->size = size;
    hT->table = (LLNode **) malloc(size * sizeof(LLNode *));

    int i;
    for (i = 0; i < size; i++) {
        hT->table[i] = NULL;
    }

    return hT;
}

//------------------------------------------------------------------
/* 
 * function to find a new index for new text in the hashtable
 */

int HASH_hash(HashTable *hT, char *word) {
    if (hT == NULL || hT->size <= 0)
        return -1;
    int index;
    for (index = 0; *word != '\0'; word++) {
        index = (index * 256 + (int)(*word)) % hT->size;
    }

    return index;
}

//------------------------------------------------------------------
/* 
 * function to add new item to hashtable
 */

void HASH_add(HashTable *hT, char *word) {
    if (hT == NULL || hT->size <= 0)
        return;

    int index = HASH_hash(hT, word);
    LL_add(&(hT->table[index]), word);
}

//------------------------------------------------------------------
/* 
 * function to print hashtable
 */

void HASH_print(HashTable *hT) {
    int i;
    for (i = 0; i < hT->size; i++) {
        printf("[%d]:", i);
        LL_print(hT->table[i]);
    }
}

//------------------------------------------------------------------
/* 
 * function to clean hashtable
 */

void HASH_clean(HashTable **hT) {
    int size = 0;
    for (int i = 0; i < (*hT)->size; i++) {
        if ((*hT)->table[i] != NULL)
            size++;
    }

    HashTable *newHT = HASH_new(size);
    int cur = 0;
    for (int i = 0; i < (*hT)->size; i++) {
        if ((*hT)->table[i] != NULL) {
            newHT->table[cur++] = (*hT)->table[i];
        }
    }

    *hT = newHT;
}

//------------------------------------------------------------------
/* 
 * function which sort hashtables
 */

void HASH_sort(HashTable *hT) {
    int i, j;
    LLNode *t;
  
    for (i = 0; i < hT->size; i++) {
        for (j = i + 1; j < hT->size; j++) { 
            if (LL_size(*(hT->table + j)) < LL_size(*(hT->table + i))) {
                t = *(hT->table + i);
                *(hT->table + i) = *(hT->table + j);
                *(hT->table + j) = t;
            }
        }
    }
}

//------------------------------------------------------------------
/* 
 * main function
 */

void main() {
    FILE *fp = fopen("text.txt", "r");
    char buf[MAX];
    int count = 0;
    LLNode *node = LL_new("");

  
    while(fscanf(fp, "%s", buf) != EOF) {
        count++;
        for (int i = 0; i < MAX; i++) {
            if (buf[i] != '\'' && buf[i] < 65 || buf[i] > 90 && buf[i] < 97 || buf[i] > 122 && buf[i] < 128 || buf[i] > 154 && buf[i] < 160 || buf[i] > 165 && buf[i] < 181 || buf[i] > 183 && buf[i] < 198 || buf[i] > 199 && buf[i] < 209 || buf[i] > 216 && buf[i] != 222 && buf[i] < 224 || buf[i] > 237)
                buf[i] = '\0';
        }
        char *newstr = (char *) malloc(MAX*sizeof(char));
        strcpy(newstr, buf);
        LL_add(&node, newstr);
    }

    printf("The total number of words: %d\n", count);

    HashTable *ht = HASH_new(count);

    LLNode *temp = node;
    while (temp->pNext != NULL) { 
        if (strcmp(temp->word, "") != 0)
            HASH_add(ht, temp->word);
        temp = temp->pNext;
    }

    HASH_clean(&ht);
    printf("The number of distinct words: %d\n", ht->size);

    HASH_sort(ht);
    printf("\nThe most freq used 10 words are\n");
     for (int i = 0; i < 10; i++) {
        printf("%s #%d\n", ht->table[ht->size - i - 1]->word, LL_size(ht->table[ht->size - i - 1]));
    }
    puts("");
    printf("\nThe least freq used 10 words are\n");
    for (int i = 0; i < 10; i++) {
        printf("%s #%d\n", ht->table[i]->word, LL_size(ht->table[i]));
    }
    puts("");
    printf("\nAll the words with their #occurrences:\n");
    for (int i = 0; i < ht->size; i++) {
        printf("%s #%d \n", ht->table[i]->word, LL_size(ht->table[i]));
    }
    puts("");
}

//------------------------------------------------------------------