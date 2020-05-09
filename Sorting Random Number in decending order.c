#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	clock_t str, end;
	FILE *fp;
	int *arr,n;
	int tmp, i, j, index,k;
	

	printf("N:");
	scanf("%d", &n);


	if (n < 1)
	{
		printf("N�� �ٽ� �Է����ּ���.");
		exit(1);
	}

	
	arr = (int*) malloc (n * sizeof(int));
	if (arr == NULL)
	{
		printf("�޸� �Ҵ� ����.");
		exit(1);
	}

	fp = fopen("unsorted.txt", "w");
	if (fp == NULL)
	{
		printf("������ ������ �ʾҽ��ϴ�.");
		exit(1);
	}

	for (i = 0; i < n; i++) 
	{
		arr[i] = rand() % 1000 ;  
		fprintf(fp, "%d ", arr[i]);   
	}
	fclose(fp);
	
	str = clock();                
	for (i = 0; i < n; i++)
	{	
		tmp = arr[i];
		index = i;
		for (j = i; j < n; j++)
		{
			if (arr[j] > tmp)
			{
				tmp = arr[j];
				index = j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[index];
		arr[index] = tmp;
		
	}
	end = clock();  //���� ����

	fp = fopen("sorted.txt", "w");
	if (fp == NULL)
	{
		printf("������ ������ �ʾҽ��ϴ�.");
		exit(1);
	}
	
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%d ", arr[i]);
	}
	
	printf("Time:%f", (float)(end - str) / CLOCKS_PER_SEC);
	
	free(arr);
	fclose(fp);

	return 0;
}