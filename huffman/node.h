#ifndef __NODE_H__
#define __NODE_H__

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
SNode *Node_new(char value, int count);

//----------------------------------------------------------------------------
/*
 * function to add new nodes to the head
 */
void Node_add(SNode **ppHead,SNode *pNode);

//----------------------------------------------------------------------------
/*
 * function to print the node
 */
void Node_print(SNode *pHead);
//----------------------------------------------------------------------------

#endif