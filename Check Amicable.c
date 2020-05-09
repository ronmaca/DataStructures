#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int num1, num2;
	int sum1=0, sum2 = 0;
	int i;

	printf("Fisrt number:");
	scanf("%d", &num1);
	printf("Second number:");
	scanf("%d", &num2);

	for (i = 1; i < num1; i++) //ù ��° �� ����� ���ϱ�
	{
		if (num1 % i == 0)
		{
			sum1 += i;
		}
	}
	for (i = 1; i < num2; i++) //�� ��° �� ����� ���ϱ�
	{
		if (num2 % i == 0)
		{
			sum2 += i;
		}
	}
	
	if ((sum1 == num2) && (sum2 == num1))
		printf("Amicable");
	else
		printf("Not amicable");

	return 0;
}