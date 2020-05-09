#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1001
#define MAX_COL 1001


typedef struct {
	int col;
	int row;
	int value;
}term;
term a[MAX_TERMS], b[MAX_TERMS];

void printmat();
void fastTranspose();
void matadd(int**, int**, int, int);
int** createmat(int, int, FILE*);

int main()
{
	FILE* fp1, * fp2;
	int** mat1, ** mat2;
	int row, col, value;
	int i, j;

	fp1 = fopen("mat1.txt", "r");
	fp2 = fopen("mat2.txt", "r");
	if (fp1 == NULL || fp2 == NULL)
	{
		printf("파일이 열리지 않았습니다.");
		return 1;
	}

	fscanf(fp1, "%d %d", &row, &col);
	mat1 = createmat(row, col, fp1);

	fscanf(fp2, "%d %d", &row, &col);
	mat2 = createmat(row, col, fp2);

	matadd(mat1, mat2, row, col);
	fastTranspose();
	printmat();



	free(mat1[0]); free(mat1);
	free(mat2[0]); free(mat2);
	fclose(fp1);  fclose(fp2);
	return 0;
}

void printmat()
{
	int i;

	printf("Maxtrix Addition:\n");
	for (i = 0; i <= a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	}
	printf("Transpose Maxtrix:\n");
	for (i = 0; i <= b[0].value; i++)
	{
		printf("%d %d %d\n", b[i].row, b[i].col, b[i].value);
	}
}
void matadd(int** mat1, int** mat2, int rowsize, int colsize)
{
	int i, j;
	int pos = 1;
	int value = 0;

	for (i = 0; i < rowsize; i++)
	{
		for (j = 0; j < colsize; j++)
		{
			if (mat1[i][j] + mat2[i][j] != 0)
			{
				a[pos].row = i;
				a[pos].col = j;
				a[pos].value = mat1[i][j] + mat2[i][j];
				pos++; value++;
			}
		}
	}
	a[0].row = rowsize; a[0].col = colsize; a[0].value = value;

}
void fastTranspose()
{
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols; b[0].col = a[0].row; b[0].value = numTerms;
	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}

}
int** createmat(int row, int col, FILE* fp)
{
	int** mat;
	int j, i, value;

	mat = (int**)malloc(sizeof(int*) * row); //free 해주기
	for (int i = 0; i < col; i++) {
		mat[i] = (int*)malloc(sizeof(int) * col);
		if (mat[i] == NULL)
		{
			printf("메모리 할당 오류");
			exit(1);
		}
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			value = fscanf(fp, "%d", &mat[i][j]);
			if (value == EOF) break;
		}
	}
	return mat;
}