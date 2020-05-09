#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#define MAX_STR 1001

void printfailure(char *);
void failure(char*);
void pmatch(char *,char *);

int f[MAX_STR];

int main()
{
	FILE* fp1;
	char str[MAX_STR];
	char pat[MAX_STR];

	fp1 = fopen("input.txt", "r");
	if (fp1 == NULL)
	{
		printf("파일 열기 오류");
		return 1;
	}

	fscanf(fp1,"%s %s",&str,&pat);
	failure(pat);

	printf("Failure function:\n"); printfailure(pat);
	printf("The pattern %s is found at ", pat) ;
	pmatch(str,pat);


	return 0;
}

void printfailure(char* pat)
{
	int i;
	printf("j  ");
	for (i = 0; i < strlen(pat); i++)
		printf("%3d ", i);
	printf("\n");

	printf("pat");
	for (i = 0; i <= strlen(pat); i++)
		printf("%3c ", pat[i]);
	printf("\n");

	printf("f  ");
	for (i = 0; i < strlen(pat); i++)
		printf("%3d ", f[i]);
	printf("\n");
}

void failure(char pat[]) {
	
	int j = 0, i = 1;
	f[0] = -1;

	while (i < strlen(pat)) {
		while ((pat[i] != pat[j]) && j > 0)
			j = f[j - 1];

		if (pat[i] == pat[j]) {
			f[i] = j;
			i++;
			j++;
		}
		else {
			f[i] = -1;
			i++;
		}
	}
}

void pmatch(char *str,char *pat)
{
	int i = 0, j = 0;

	while (i < strlen(str))
	{
		if (j == -1 || str[i] == pat[j])
		{
			i++;
			j++;
		}
		else j = f[j];
		if (j == strlen(pat))
		{
			printf("%d", i - strlen(pat));
			j = f[j];
		}
	}
}
