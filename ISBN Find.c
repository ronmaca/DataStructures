/*An ISBN (International Standard Book Number) is a ten digit code which uniquely identifies a book.
  The first nine digits represent the book and the last digit is used to make sure the ISBN is correct.
  To verify an ISBN you calculate 10 times the first digit, plus 9 times the second digit, plus 8 times the third ... all the way until you add 1 times the last digit.
  If the final number leaves no remainder when divided by 11 the code is a valid ISBN. 
 
  For example, 0201103311 is a valid ISBN, since 10*0 + 9*2 + 8*0 + 7*1 + 6*1 + 5*0 + 4*3 + 3*3 + 2*1 + 1*1 = 55. 
  Each of the first nine digits can take a value between 0 and 9. Sometimes it is necessary to make the last digit equal to ten; this is done by writing the last digit as X. For example, 156881111X.  
  Write a program that reads in a valid ISBN with a single missing digit, marked with a ?, and outputs the correct value for the missing digit [6pts]. 
 
  Sample run ISBN: 15688?111X 
  Missing Digit: 1 
*/













#define _CRT_SECURE_NO_WARNINGS
#define NUM 10
#include <stdio.h>


int main()
{
	char isbn1[11];
	int isbn2[NUM];
	int digit=0,index;
	int remainder,i, sum = 0;
	
	
	printf("ISBN:");
	scanf("%s",isbn1);


	for (i = 0; i < NUM; i++)    // ISBN�� ���ڿ��� �Է¹޾� ������ �迭�� ����
	{
		if(isbn1[i]== 'X')
			isbn2[i] = (int)(isbn1[i]) - 78;
		else if (isbn1[i] == '?')
		{
			isbn2[i] = 0;
			index = i;
		}
		else 
			isbn2[i] = (int)(isbn1[i]) - 48;
	}

	for (i = 0 ; i < NUM; i++)     //�� ���ϱ�
	{
		if (i == index) 
			continue;
		else
			sum +=  (NUM-i)* isbn2[i];
	}

	for (i = 0;i<NUM; i++)
	{
		if ((sum + ((10 - index) * i)) % 11 == 0)
		{
			digit = i;
			break;
		}
	}
	
	printf("Missing Digit:%d",digit);
	
	return 0;
}
	