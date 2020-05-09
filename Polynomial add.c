/*input a.txt (3x^20 + 2x^5 + 4) 		3 3 20 2 5 4 0 
		
		b.txt (x^4 + 10x^3 + 3x^2 + 1) 4 1 4 10 3 3 2 1 0 
  
  
  output   3x^20 + 2x^5 + 1x^4 + 10x^3 + 3x^2 + 5 
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX_DEGREE 1001
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
}polynomial;

void printpoly(polynomial);
polynomial add(polynomial, polynomial);

int main()
{
	FILE * fp1, * fp2;
	polynomial a = { 0 ,{0} }, b = { 0,{0} },d;
	int coef, expo;
	int n,i;

	fp1 = fopen("a.txt", "r");
	fp2 = fopen("b.txt", "r");
	if ((fp1 == NULL)||(fp2==NULL))
	{
		printf("���� ���� ����\n");
		return 1;
	}

	fscanf(fp1,"%d",&n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp1, "%d%d", &coef,&expo);
		if (i == 0)
			a.degree = expo;
		a.coef[expo] = coef;
	}

	fscanf(fp2, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp2, "%d%d", &coef, &expo);
		if (i == 0)
			b.degree = expo;
		b.coef[expo] = coef;
	}
	

	d = add(a, b);
	printpoly(d);


	fclose(fp1);
	fclose(fp2);

	return 0;
}

void printpoly(polynomial n)
{

	int i;
	int expo = n.degree;

	for (i = expo; i >= 0; i--)
	{
		if (n.coef[i] != 0)
		{
			if (i == 0)
				printf("%d", n.coef[i]);
			else
				printf("%dx^%d + ", n.coef[i], i);
		}
	}
	printf("\n");
}

polynomial add(polynomial a, polynomial b)
{
	polynomial d;
	int i;
	int adegree = a.degree, bdegree = b.degree;
	d.degree = MAX(a.degree, b.degree);
	
	while (adegree>=0 && bdegree >=0) {
		if (adegree > bdegree) {
			d.coef[adegree] = a.coef[adegree];
			adegree--; 
		}
		else if (adegree == bdegree) {
			d.coef[adegree] = a.coef[adegree] + b.coef[bdegree];
			adegree--;	bdegree--;
		}
		else {
			d.coef[bdegree] = b.coef[bdegree];
			bdegree--;
		}
	}
	return d;
}