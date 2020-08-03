#include <stdio.h>
#include <string.h>

void blast(char* arr,int size){
	int nBestPos = 0, nBestHeight = 0, nCandHeight = 0, nCandPos = 0;
	for (int i = 0; i < size; i++){
		if (arr[i] == '0'){
			if(nCandHeight) 
                nCandHeight--;
			else 
                nCandPos = i + 1;	
		} else {
			nCandHeight++;
		}

		if (nCandHeight > nBestHeight){
			nBestHeight = nCandHeight;
			nBestPos = nCandPos;
		}
	}
	printf("Best Position: %d  Best Height: %d\n",nBestPos,nBestHeight );

}

void main(){
	char match[]="01111010010100001111101100000011";
	blast(match,strlen(match));
}