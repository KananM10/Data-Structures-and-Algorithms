#include <stdio.h>
#include <stdlib.h>


//----------------------------------------------------------------------------
/*
 * structure for node which is linked list node and binary tree node
 */
typedef struct SNode{
    char value;
    int count;
    struct SNode *pNext;
    struct SNode *pLChild;
    struct SNode *pRChild;
}SNode;

//----------------------------------------------------------------------------
/*
 * function to create new node
 */
SNode *Node_new(char value, int count){

	SNode* newNode=(SNode *)malloc(sizeof(SNode));
	newNode->value = value;
	newNode->count = count;
	newNode->pLChild = NULL;
	newNode->pRChild = NULL;
	newNode->pNext = NULL;
}

//----------------------------------------------------------------------------
/*
 * function to add new nodes to the head
 */
void Node_add(SNode **ppHead,SNode *pNode){
    SNode *pTemp = (*ppHead);

    if (pTemp == NULL){
    	*ppHead = pNode;
        return ;
    }

    //ascending order in linked list
    if (pNode->count <= (*ppHead)->count){
    	pNode->pNext = *ppHead;
    	*ppHead = pNode;
    	return ;
    }

    while (pTemp->pNext != NULL){
        if (pTemp->pNext->count > pNode->count){
        	pNode->pNext = pTemp->pNext;
            pTemp->pNext = pNode;
            return ;
        }
        pTemp = pTemp->pNext;
    }
    pTemp->pNext = pNode; 

    
}

//----------------------------------------------------------------------------
/*
 * function to print the node
 */
void Node_print(SNode *pHead){
	if (pHead == NULL){
        puts("");
        return;
    }

    while (pHead != NULL){
        printf("[%c,%d] => ",pHead->value,pHead->count);
        pHead = pHead->pNext;
    }
    printf("NULL\n");
    puts("");
}

//----------------------------------------------------------------------------
