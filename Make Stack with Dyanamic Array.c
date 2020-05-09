
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!(p = malloc(s))) {\
						printf("Insufficient memory."); \
						exit(EXIT_FAILURE); \
					}

typedef struct {
	int key;
}element;
element* stack;


int capacity = 1;
int top = -1;

void stackFull();
void push(element);
element pop();
void printStack();

int main()
{
	MALLOC(stack, sizeof(*stack));

	element item;
	FILE* fp;
	char menu;
	int res;

	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("File Open Error!");
		return 1;
	}

	while (1)
	{
		res = fscanf(fp, "%c", &menu);
		if (res == EOF)
			break;
		else {
			if (menu == 'I') 
			{
				res = fscanf(fp, "%d", &item.key);
				push(item);
			}
			else if (menu == 'D') 
				pop();
		}
	}
	printStack();

	fclose(fp);
	return 0;
}

void stackFull()
{
	stack = (element*)realloc(stack, 2 * capacity * sizeof(*stack));
	if (!stack) 
	{
		printf("Insufficient Memory.");
		exit(EXIT_FAILURE);
	}
	capacity *= 2;
}

void push(element item)
{
	if (top >= capacity - 1)
		stackFull();
	if (top < 0)
	{
		stack->key = item.key;
		top++;
	}
	else
		stack[++top].key = item.key;
}


element pop()
{
	return stack[top--];
}

void printStack()
{
	int i;

	printf("Capacity: %d\n", capacity);
	printf("Stack: ");
	for (i = 0; i <= top; i++)	printf("%d ", stack[i].key);
}