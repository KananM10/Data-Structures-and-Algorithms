#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//------------------------------------------------------------------------
/*
 * function to create a matrix
 */
int **TABLE_new(int rows, int cols){
	int **table = (int **) calloc(rows, sizeof(int *));

	for (int i = 0; i < rows; i++) 
		table[i] = (int *) calloc(cols, sizeof(int));

	return table;
}

//------------------------------------------------------------------------
/* 
 * function which returns the max value from 3 inputs
 */
int maximum(int left, int top, int diag, char c1, char c2){
	int max;

	if (c1 == c2) max = diag + 3;
	else max = diag - 3;
	if (left - 2 > max) max = left - 2;
	if (top - 2 > max) max = top - 2;
	if (max < 0) return 0;
	
	return max;
}

//------------------------------------------------------------------------
/*
 * function which fill table in 
 */
void TABLE_fill(int **table, char *s1, char *s2) {
	for (int y = 1; y < strlen(s2) + 1; y++) { // 1 because the first row and the first col is 0s
		for (int x = 1; x < strlen(s1) + 1; x++) {
			char c1 = s1[x - 1],
                c2 = s2[y - 1];
			int score = maximum(table[y][x - 1], table[y - 1][x], table[y - 1][x - 1], c1, c2);
			table[y][x] = score;
		}
	}
}

//------------------------------------------------------------------------
/*
 * function which finds the path in the matrix according smith-watermann theory
 */
int *TABLE_traceback(int **table, int rows, int cols, int *size, int *highestScore) {
	*highestScore = -1;
	int highestScoreRowIndex, highestScoreColIndex;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (table[i][j] > *highestScore) {
				*highestScore = table[i][j];
				highestScoreRowIndex = i;
				highestScoreColIndex = j;
			}
		}
	}
	//printf("Highest score: %d\n", *highestScore);

	int *rowCol = (int *) calloc(2 * rows * cols, sizeof(int)),
        rowColIndex = 0, rowIndex, colIndex, tempHighestScore = *highestScore;
	while (tempHighestScore) {
		rowCol[rowColIndex++] = highestScoreRowIndex;
		rowCol[rowColIndex++] = highestScoreColIndex;

 		tempHighestScore = table[highestScoreRowIndex - 1][highestScoreColIndex - 1];
 		rowIndex = highestScoreRowIndex - 1;
 		colIndex = highestScoreColIndex - 1;

 		if(table[highestScoreRowIndex][highestScoreColIndex - 1] > tempHighestScore) {
 			tempHighestScore = table[highestScoreRowIndex][highestScoreColIndex - 1];
	 		rowIndex = highestScoreRowIndex;
 			colIndex = highestScoreColIndex - 1;
 			if (tempHighestScore == 0) break;
 		}

        if(table[highestScoreRowIndex - 1][highestScoreColIndex] > tempHighestScore) {
 			tempHighestScore = table[highestScoreRowIndex - 1][highestScoreColIndex];
	 		rowIndex = highestScoreRowIndex - 1;
 			colIndex = highestScoreColIndex;
 			if (tempHighestScore == 0) break;
 		}

 		highestScoreRowIndex = rowIndex;
 		highestScoreColIndex = colIndex;
	}

	*size = rowColIndex;
	return rowCol;
}

//------------------------------------------------------------------------
/*
 * function that prints the path in the matrix
 */
void TABLE_printPath(int **table, int *path, int pathTableSize, char *s1, char *s2) {
    int rowIndex, colIndex, i;

	for (i = pathTableSize - 1; i >= 0; i -= 2) {
		rowIndex = path[i - 1];
		colIndex = path[i];
		printf("%d  ", table[rowIndex][colIndex]);
	}
	puts("");

	for (i = pathTableSize - 1; i >= 0; i -= 2) {
		rowIndex = path[i - 1];
		colIndex = path[i];

		if (s2[rowIndex - 1] == s1[colIndex - 1])
			printf("%c  ", s1[colIndex - 1]);
		else printf("-  ");
	}
	puts("");

	for (i = pathTableSize - 1; i >= 0; i -= 2) {
		rowIndex = path[i - 1];
		colIndex = path[i];
		printf("%c  ", s2[rowIndex - 1]);
	}
	puts("");
}

//------------------------------------------------------------------------
/*
 * main function
 */
int main() {
	char junk[1024];

	FILE *file = fopen("dna.csv", "r");

	if (file == NULL) {
		printf("ERROR while trying to open the file\n");
		return 0;
	}

	// skipping the first 3558 lines
	for (int i = 0; i < 3558; i++) fscanf(file,"%[^\n]\n", junk);

	char *sample = "tgttacggac\0", *cur;
	int curPathTableSize, rows = strlen(sample) + 1, cols;

	fscanf(file, "%s", junk); // read skip the number at the beginning
	int highestScore = -1, tempScore, *bestPath, **bestPathTable, bestPathTableSize;
	char *bestMatch;
	for (int i = 0; i < 3837; i++) {
		// 6 codes per line
		for (int j = 0; j < 6; j++) {
			//puts("");
			char *cur = (char *) malloc(11*sizeof(char));
			fscanf(file, "%s", cur);
			cols = strlen(cur) + 1;


			int **table = TABLE_new(rows, cols);
			TABLE_fill(table, cur, sample);

			int *path = TABLE_traceback(table, rows, cols, &curPathTableSize, &tempScore);

			if (tempScore > highestScore) {
				highestScore = tempScore;
				bestPath = path;
				bestPathTable = table;
				bestPathTableSize = curPathTableSize;
				bestMatch = cur;
			}
		}
	}

	printf("\n\nThe best matching is: \n\n\tMatch: %s\n\tSample: %s\n\n",bestMatch, sample);
	TABLE_printPath(bestPathTable, bestPath, bestPathTableSize, bestMatch, sample);
	printf("\nScore is: %d\n",highestScore);
		
	return 0;
}

//---------------------------------------------------------------------------------------