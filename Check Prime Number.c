#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main(void)
{
	int i,res = 0 ;
	int num;

	printf("Number:");
	scanf("%d", &num);
	
	if (num <= 1) 
		printf("Not Prime");
	else {
		for (i = 2; i < num; i++)
		{
			if (num % i == 0)
			{
				res++;
				break;
			}
		}

		if (res != 0)
			printf("Not Prime");
		else
			printf("Prime");
	}
	return 0;
}