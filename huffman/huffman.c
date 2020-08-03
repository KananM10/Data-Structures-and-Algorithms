#include "huffman.h"


//----------------------------------------------------------------------------------

int nCount_albhabets = 0;
char arr[256][20];
char temp[10];
char *pTemp = &(temp[0]);
char *pArr = &(arr[0][0]);

//----------------------------------------------------------------------------------
/*
 * function which adds all letters from file to the linked list
 */
void statistics(int* list, float fsum, SNode **ppHead){
	printf("\nStatistics:\n");
	float fEnt = 0;
    	
    for(int i = 0;i < 256; i++){
    	if (list[i] != 0){
    		nCount_albhabets++;
    		printf("%c: %d\n", (char)i, list[i]);
    		Node_add(ppHead, Node_new((char)i, list[i]));
    		fEnt += (list[i]/fsum * log2(fsum/list[i]));
    	}
    }
    printf("\nEntropy: %f\n", fEnt);
}

//----------------------------------------------------------------------------------
/*
 * function that makes a binary tree from linked list 
 */
void addToBinaryTree(SNode **ppHead){
	while((*ppHead)->pNext != NULL){
		SNode *pTemp = (*ppHead);

	    if (pTemp->pNext != NULL){
	    	SNode *pFirstNode = pTemp;
	    	SNode *pSecondNode = pTemp->pNext;

	    	SNode *newNode = Node_new(' ',pFirstNode->count + pSecondNode->count);
	    	newNode->pLChild = pFirstNode;
	    	newNode->pRChild = pSecondNode;
	    	

	    	if (pSecondNode->pNext == NULL){
	    		*ppHead = newNode;
	    	}

	    	else{
	    		*ppHead = pSecondNode->pNext;
	    		Node_add(&(*ppHead), newNode);
	    	}
	    }
	}
}

//----------------------------------------------------------------------------------
/*
 * function that traverses through the binary tree and puts 0s to the left and 1s to the right 
 */
void binary_traverse(SNode *pHead,char *pTemp){
	
	if (pHead->pLChild){
		*pTemp='0';
		binary_traverse(pHead->pLChild,pTemp+1);
	}

	if (pHead->pRChild){
		*pTemp='1';
		binary_traverse(pHead->pRChild,pTemp+1);

	} else {
		*pArr=pHead->value;
		*(pArr+1)=0;
		*pTemp=0;
		strcpy(pArr+2,temp);
		pArr+=20;
	}
}

//----------------------------------------------------------------------------------
/*
 * function to print the binary tree
 */
void printBinaryTree(SNode  *pHead){

	if (pHead->pLChild == NULL)  
        printf(" [- : -] ");
	else 
        printf(" [%c : %d] ",pHead->pLChild->value, pHead->pLChild->count);
	printf(" [%c : %d] ",pHead->value,pHead->count );
	if (pHead->pRChild == NULL)  
        printf(" [- : -] ");
	else 
        printf(" [%c : %d]  \n",pHead->pRChild->value, pHead->pRChild->count);

    if(pHead->pLChild != NULL){
		printBinaryTree(pHead->pLChild);
	}

	if (pHead->pRChild != NULL){
		printBinaryTree(pHead->pRChild);	
	}
	printf("\n");
}

//----------------------------------------------------------------------------------
/*
 * function that encodes the huffman code and returns the binary code
 */
char *encode(SNode *pHead,char *fileName){

	binary_traverse(pHead,pTemp);
	char *encodeArr = (char*)malloc(1000*sizeof(char));
	FILE *file = fopen(fileName,"r");
	int c;
	int lastPointIndex = 0;
	while ((c = fgetc(file)) != EOF){
    	for (int i = 0; i < nCount_albhabets; ++i){
    		char tempChar = arr[i][0];
    		if (c == tempChar){
    			char *ptr = &(arr[i][2]);
    			strcpy(&encodeArr[lastPointIndex],ptr);
    			lastPointIndex += strlen(ptr);
    		}
    	}
    }
    return encodeArr;
    fclose(file);
}

//----------------------------------------------------------------------------------
/*
 * function that decodes the huffman code and returns the phrase
 */
char *decode(SNode *pHead,char *encodeArr){
	char *decodeArr = (char*)malloc(1000*sizeof(char));
	int index = 0;
	SNode *pTemp = pHead;
	for (int i = 0; i < 1000; ++i){
		if (encodeArr[i] != 0) {
			char c = encodeArr[i];
			if(c == '1') 
                pTemp = pTemp->pRChild;
			else 
                pTemp = pTemp->pLChild;
			
			if (pTemp->pLChild == NULL && pTemp->pRChild == NULL){
				decodeArr[index++] = pTemp->value;
				pTemp = pHead;
			}
		}
	}
	return decodeArr;
}

//----------------------------------------------------------------------------------
