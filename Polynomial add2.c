/*input a.txt (3x^20 + 2x^5 + 4) 		3 3 20 2 5 4 0 
		
		b.txt (x^4 + 10x^3 + 3x^2 + 1) 4 1 4 10 3 3 2 1 0 
  
  
  output   3x^20 + 2x^5 + 1x^4 + 10x^3 + 3x^2 + 5 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1001


typedef struct {
	int coef;
	int expo;
}polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

void attach(int, int);
void padd(int,int,int,int,int*,int*);
void printpoly();

int main()
{
	FILE* fp1, * fp2;
	int sa=0, fa, sb, fb;
	int * sd, * fd;
	int coef, expo;
	int n, i;

	fp1 = fopen("a.txt", "r");
	fp2 = fopen("b.txt", "r");
	if ((fp1 == NULL) || (fp2 == NULL))
	{
		printf("���� ���� ����\n");
		return 1;
	}

	fscanf(fp1, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp1, "%d %d", &coef,&expo);
		attach(coef, expo);
	}
	fa = avail - 1;
	sb = avail;

	fscanf(fp2, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp2, "%d %d", &coef, &expo);
		attach(coef, expo);
	}
	fb = avail - 1;

	padd(sa,fa,sb,fb,&sd,&fd);
	
	for (i = sd; i <= fd; i++) 
	{
		if (terms[i].expo == 0)
		{
			printf("%d", terms[i].coef);
			continue;
		}
		else
		{
			printf("%dx^%d + ", terms[i].coef, terms[i].expo);
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}

void attach(int coefficient, int exponent)
{
	if (avail >= MAX_TERMS)
	{
		printf("Too many items.");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expo = exponent;
}

void padd(int sa, int fa, int sb, int fb, int* sd, int* fd)
{

	int coef;
	*sd = avail;

	while ((sa <= fa) && (sb <= fb))
	{
		if (terms[sa].expo > terms[sb].expo)
		{
			attach(terms[sa].coef, terms[sa].expo);
			sa++;
		}
		else if (terms[sa].expo == terms[sb].expo)
		{
			coef = terms[sa].coef + terms[sb].coef;
			if (coef)
				attach(coef, terms[sa].expo);
			sa++; sb++;
		}
		else
		{
			attach(terms[sb].coef, terms[sb].expo);
			sb++;
		}
	}
	for (; sa <= fa; sa++) attach(terms[sa].coef, terms[sa].expo);
	for (; sb <= fb; sb++) attach(terms[sb].coef, terms[sb].expo);
	*fd = avail - 1;
}