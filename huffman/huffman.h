#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "node.h"
#include <string.h>
#include <math.h>


//----------------------------------------------------------------------------------
/*
 * function which adds all letters from file to the linked list
 */
void statistics(int* list, float fsum, SNode **ppHead);

//----------------------------------------------------------------------------------
/*
 * function that makes a binary tree from linked list 
 */
void addToBinaryTree(SNode **ppHead);

//----------------------------------------------------------------------------------
/*
 * function that traverses through the binary tree and puts 0s to the left and 1s to the right 
 */
void binary_traverse(SNode *pHead,char *pTemp);

//----------------------------------------------------------------------------------
/*
 * function to print the binary tree
 */
void printBinaryTree(SNode  *pHead);

//----------------------------------------------------------------------------------
/*
 * function that encodes the huffman code and returns the binary code
 */
char *encode(SNode *pHead,char *fileName);

//----------------------------------------------------------------------------------
/*
 * function that decodes the huffman code and returns the phrase
 */
char *decode(SNode *pHead,char *encodeArr);

//----------------------------------------------------------------------------------

#endif