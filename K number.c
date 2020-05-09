/*You probably already know that "N factorial" is written as "N!" and means N * (N-1) * (N2) * ... * 1.
  The factorial of 0 is defined to be 1. "Five factorial" is written and calculated like this: 5! = 5 * 4 * 3 * 2 * 1 = 120.
  Here's how to calculate factorial digit sums. Start with any number, say 25. 
  Find the sum of the factorials of each of the digits of 25: 2! + 5! = 2 + 120 = 122.
  Now, repeat the procedure with 122 to get 1! + 2! + 2! = 5.
  Continue summing the factorials of the individual digits to get the next number until we get total K numbers.
  For example, the list for N=25, K=3 is: 25→122→5 
  Write a program that computes and prints this factorial sum list, one number per line, for any number N (1<=N<=1000000) until we get K (1<=K<100) numbers [7pt]. 
 
  Sample run: N, K: 25 3 
                25 122 5
*/














#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int factorial(int);
int factorialsum(int);

int main()
{
    int n, k;
    int i;
    int sum = 0;

    printf("N, K:");
    scanf("%d %d", &n, &k);


    for (i = 0; i < k; i++)
    {
        printf("%d ", n);
        sum = factorialsum(n);
        n = sum;
    }
    return 0;
}

int factorial(int n)
{
    if (n <= 1) // 0! == 1
        return 1;
    else
        return n * factorial(n - 1);
}

int factorialsum(int n)
{
    int remainder, sum = 0;

    while (n != 0)
    {
        remainder = n % 10;
        sum = sum + factorial(remainder);
        n = n / 10;
    }
    return sum;
}