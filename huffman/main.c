#include "huffman.h"
#include "node.h"


//----------------------------------------------------------------------------
/*
 * function that reades the file and increses the counters for ascii num of the letters in the file
 */
void readFile(char *fileName,int** list,float *fsum){

	FILE *file=fopen(fileName,"r");
	int c;
	printf("Text:\n");
	while ((c = fgetc(file)) != EOF){
    	printf("%c",(char)c );
    	(*list)[c]++;
    	(*fsum)++;
        
    }
    printf("\n");
    fclose(file);
}

//----------------------------------------------------------------------------
/*
 * main function which takes the phrases from file, encodes it into huffman code, and then decodes it into previous text
 */
void main(){

	SNode *pHead = NULL;

	char* fileName = "test.txt";
	int *list = (int *)calloc(256,sizeof(int));
	float fsum = 0;
	readFile(fileName,&list,&fsum);
	statistics(list,fsum,&pHead);
	
	printf("\nList:\n");
	Node_print(pHead);

	addToBinaryTree(&pHead);
	printf("\nBinary Tree:\n");
	printBinaryTree(pHead);

	char *encodeArr = encode(pHead,fileName);

	printf("\nEncode:\n");
	for (int i = 0; i < 1000; ++i){
		if (encodeArr[i] != 0) 
            printf("%c",encodeArr[i] );
	}
    
	printf("\n");

	char* decodeArr=decode(pHead,encodeArr);
    printf("\nDecode:\n");
	for (int i = 0; i < 1000; ++i){
		if (decodeArr[i]!=0) 
            printf("%c",decodeArr[i] );
	}

	printf("\n");

}

//----------------------------------------------------------------------------
