#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	FILE* fp;
	int Min, Max;
	int num;
	int res;

	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("파일이 열리지 않았습니다.\n");
		return 1;
	}

	fscanf(fp, "%d", &num);
	Min = num;
	Max = num;
	
		
	while (1)
	{
		res = fscanf(fp,"%d",&num);
		if (res == EOF)
			break;
		else
		{
			if (num < Min)
				Min = num;
			else if (num > Max)
				Max = num;
		}
	}

	printf("Min:%d\n",Min);
	printf("Max:%d",Max);

	fclose(fp);

	return 0;
}
