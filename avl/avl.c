#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//------------------------------------------------------------------------
/*
 * function to create new avl tree
 */
bst *BST_new(int data)
{
    bst *newNode = (bst *)malloc(sizeof(bst));

    newNode->nData = data;
    newNode->pLeft = newNode->pRight = NULL;
    newNode->height = 1;

    return newNode;
}

//------------------------------------------------------------------------
/*
 * function to print avl tree inorder
 */
void BST_inorder(bst *root)
{
    if (root == NULL)
        return;

    BST_inorder(root->pLeft);
    printf("[D:%d H:%d]", root->nData, root->height);
    BST_inorder(root->pRight);
}

//------------------------------------------------------------------------
/*
 * function to print avl tree preorder
 */
void BST_prerder(bst *root)
{
    if (root == NULL)
        return;

    printf("[D:%d H:%d]", root->nData, root->height);
    BST_prerder(root->pLeft);
    BST_prerder(root->pRight);
}

//------------------------------------------------------------------------
/*
 * function to get the height of the tree
 */
int BST_getHeight(bst *root)
{
    return (root == NULL) ? 0 : root->height;
}

//------------------------------------------------------------------------
/*
 * function to get the balance of the tree
 */
int BST_getBalance(bst *node)
{
    return (node == NULL) ? 0
                          : BST_getHeight(node->pLeft) -
                                BST_getHeight(node->pRight);
}

//------------------------------------------------------------------------
/*
 * function to get the max of 2 inputs
 */
int max(int x, int y)
{
    return (x > y) ? x : y;
}

//------------------------------------------------------------------------
/*
 * function that returns the min successor
 */
bst *BST_successor(bst *node)
{
    if (node == NULL || node->pRight == NULL)
        return NULL;

    bst *temp = node->pRight;
    while (temp != NULL && temp->pLeft != NULL)
        temp = temp->pLeft;

    return temp;
}

//------------------------------------------------------------------------
/*
 * function that returns the max predecessor
 */
bst *BST_predecessor(bst *node)
{
    if (node == NULL || node->pLeft == NULL)
        return NULL;

    bst *temp = node->pLeft;
    while (temp != NULL && temp->pRight != NULL)
        temp = temp->pRight;

    return temp;
}

//------------------------------------------------------------------------
/*
 *
 */
void BST_rightRotate(bst **ppNode)
{
    //TO BE DONE
    bst *left = (*ppNode)->pLeft;
    bst *leftRight = left->pRight;

    (*ppNode)->pLeft = leftRight;
    left->pRight = *ppNode;

    (*ppNode)->height = 1 +
                        max(BST_getHeight((*ppNode)->pLeft),
                            BST_getHeight((*ppNode)->pRight));
    left->height = 1 + max(BST_getHeight(left->pLeft),
                           BST_getHeight(left->pRight));

    (*ppNode) = left;
}

//------------------------------------------------------------------------
/*
 *
 */
void BST_leftRotate(bst **ppNode)
{
    //TO BE DONE
    bst *right = (*ppNode)->pRight;
    bst *rightLeft = right->pLeft;

    (*ppNode)->pRight = rightLeft;
    right->pLeft = (*ppNode);

    (*ppNode)->height = 1 +
                        max(BST_getHeight((*ppNode)->pLeft),
                            BST_getHeight((*ppNode)->pRight));
    right->height = 1 + max(BST_getHeight(right->pLeft),
                            BST_getHeight(right->pRight));

    *ppNode = right;
}

//------------------------------------------------------------------------
/*
 * function that adds item to the tree
 */
void BST_add(bst **ppRoot, int data)
{
    bst *newNode = BST_new(data);
    if (*ppRoot == NULL)
    {
        *ppRoot = newNode;
        return;
    }

    if (data <= (*ppRoot)->nData)
    {
        BST_add(&((*ppRoot)->pLeft), data);
    }
    else
    {
        BST_add(&((*ppRoot)->pRight), data);
    }
    //TO BE DONE
    //update height
    (*ppRoot)->height = 1 +
                        max(BST_getHeight((*ppRoot)->pLeft),
                            BST_getHeight((*ppRoot)->pRight));

    BST_rebalance(ppRoot);
}

//------------------------------------------------------------------------
/*
 * function that removes item from the tree
 */
void BST_remove(bst **ppRoot, int data)
{
    if (ppRoot == NULL || *ppRoot == NULL)
        return;
    if ((*ppRoot)->nData > data)
        BST_remove(&((*ppRoot)->pLeft), data);
    else if ((*ppRoot)->nData < data)
        BST_remove(&((*ppRoot)->pRight), data);
    else
    {
        if ((*ppRoot)->pLeft == NULL)
            *ppRoot = (*ppRoot)->pRight;
        else if ((*ppRoot)->pRight == NULL)
            *ppRoot = (*ppRoot)->pLeft;
        else
        {
            bst *temp = BST_successor(*ppRoot);
            (*ppRoot)->nData = temp->nData;
            BST_remove(&((*ppRoot)->pRight), temp->nData);
        }
    }
    //if there is no more node left behind
    if (*ppRoot == NULL)
        return;
    BST_rebalance(ppRoot);
}

//------------------------------------------------------------------------
/*
 * function that rebalances the tree
 */
void BST_rebalance(bst **ppNode)
{
    int bF = BST_getBalance(*ppNode);
    if (bF > 1)
    { //left heavy
        int bFLeft = BST_getBalance((*ppNode)->pLeft);
        if (bFLeft > 0)
        { //right right
            BST_rightRotate(ppNode);
        }
        else if (bFLeft < 0)
        { //right left case
            BST_leftRotate(&((*ppNode)->pLeft));
            BST_rightRotate(ppNode);
        }
    }
    if (bF < -1)
    { //right heavy
        int bFRight = BST_getBalance((*ppNode)->pRight);
        if (bFRight > 0)
        { //right left
            BST_rightRotate(&((*ppNode)->pRight));
            BST_leftRotate(ppNode);
        }
        else if (bFRight < 0)
        { //left left case
            BST_leftRotate(ppNode);
        }
    }
}

//------------------------------------------------------------------------
