#define _CRT_SECURE_NO_WARNINGS
#define MAX_STR 101

#include <stdio.h>
#include <stdlib.h>

char stack[MAX_STR];
int top = -1;
char LeftDelimeter[] = { '(','{','[','<' };
char RightDelimeter[] = { ')','}',']','>' };

void push(char);
char pop();
int isEmpty();
void isLeftDelimeter(char);   
void cmpDelimeter(char, char);  

int main()
{
	FILE* fp;
	char delimeter;
	char temp;
	int res;


	if (!(fp = fopen("input.txt", "r"))) {
		printf("FILE OPEN ERROR!");
		return 1;
	}

	res = fscanf(fp, "%c", &delimeter);
	while (res != EOF) {
		isLeftDelimeter(delimeter);
		res = fscanf(fp, "%c", &delimeter);
	}

	if (top != -1) printf("not balanced");   
	else printf("balanced "); 
	
	return 0;
}

void push(char delimeter) {
	stack[++top] = delimeter;
}

char pop() {
	if (isEmpty()) {
		printf("not balanced ");
		exit(1);
	}
	return stack[top--];
}

int isEmpty() {
	if (top == -1) return 1;
	return 0;
}

void isLeftDelimeter(char delimeter) {
	char temp;

	switch (delimeter) {
	case '(':
		push(delimeter);
		break;
	case '{':
		push(delimeter);
		break;
	case '[':
		push(delimeter);
		break;
	case '<':
		push(delimeter);
		break;
	case ')':
		temp = pop();
		cmpDelimeter(top, delimeter);
		break;
	case '}':
		temp = pop();
		cmpDelimeter(top, delimeter);
		break;
	case ']':
		temp = pop();
		cmpDelimeter(top, delimeter);
		break;
	case '>':
		temp = pop();
		cmpDelimeter(top, delimeter);
		break;
	}
}

void cmpDelimeter(char delimeter, char top) {
	int i, j;
	int topindex, delimeterindex;

	for (i = 0; i < 4; i++) {
		if (top == LeftDelimeter[i])
			topindex = i;
	}
	for (j = 0; j < 4; j++) {
		if (delimeter == RightDelimeter[j])
			delimeterindex = j;
	}

	if (i == j) return;
	else {
		printf("not balanced ");
		exit(1);
	}
}