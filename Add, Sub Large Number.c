#define _CRT_SECURE_NO_WARNINGS
#define MAX 100  //큰 수가 최대 몇자리인지 몰라서 수정가능하게 해놓았습니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE * fp1, * fp2;
	char a[MAX];
	char b[MAX];
	char buf1[MAX];
	char buf2[MAX];
	char addres[MAX + 1] = "";
	char subres[MAX + 1] = "";
	int i;
	int sum ,carry = 0;
	


	fp1 = fopen("a.txt", "r");
	fp2 = fopen("b.txt", "r");
	if ((fp1 == NULL)||(fp2==NULL))
	{
		printf("파일 열기 오류\n");
		return 1;
	}

	fscanf(fp1, "%s",buf1);
	sprintf_s(a, sizeof(a), "%099s",buf1 );     
	fscanf(fp2, "%s", buf2);
	sprintf_s(b, sizeof(b), "%099s", buf2);
	

	for (i = sizeof(a)-2; i >= 0; i--) //더하기
	{
		sum = (a[i] - '0') + (b[i] - '0') + carry;
		carry = sum / 10;
		sum = sum % 10;
		addres[i + 1] = sum + '0';
	}
	addres[0] = carry + '0';
	

	for (i = 0; addres[i] == '0'; i++);
	printf("Addition:%s\n", addres + i);	
	
	if (strcmp(a, b) == 0)
		printf("Subtraction:0") ;
	else
	{
		for (i = sizeof(a) - 2; i >= 0; i--) //빼기
		{
			sum = (a[i] - '0') - (b[i] - '0') - carry;
				if (sum >= 0)
					carry = 0;
				else
				{
					sum += 10;
					carry = 1;
				}
			subres[i + 1] = sum + '0';
		}
		subres[0] = carry + '0';
		for (i = 0; subres[i] == '0'; i++);
		printf("Subtraction:%s", subres + i);
	}
	
	fclose(fp1);
	fclose(fp2);

	return 0;
}
