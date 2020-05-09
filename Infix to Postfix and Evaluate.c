#define _CRT_SECURE_NO_WARNINGS
#define MAX_STR 101

#include <stdio.h>
#include <stdlib.h>

typedef enum { lparen,rparen,plus,minus,times,divide,mod,eos,operand} precedence;
int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };


char expr[MAX_STR];  //���Ͽ��� �Է¹��� �� �����ϴ� �迭
precedence stack[MAX_STR];     //����
char post[MAX_STR];  //����ǥ����� �����ϴ� �迭

int posttop = -1;

precedence push(precedence,int*,int);
precedence pop(int *);
void postfix();
int eval();
void printToken(precedence);
void postpush(char);

int main()
{
	FILE *fp;


	if (!(fp = fopen("input.txt","r"))) {
		printf("FILE OPEN ERROR!");
		return 1;
	}
	fscanf(fp,"%s", &expr);
	printf("Postfix: ");
	postfix();
	printf("Result: %d",eval());

	fclose(fp);
	return 0;
}

precedence push(precedence token,int *top) {
	stack[++(*top)] = token;
}

precedence pop(int *top) {
	return stack[(*top)--];
}
int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	int top = -1;

	token = getToken(&symbol, &n,1);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0',&top);
		else {
			op2 = pop(&top);
			op1 = pop(&top);
			switch (token) {
			case plus: push(op1 + op2, &top);
				break;
			case minus: push(op1 - op2, &top);
				break;
			case times: push(op1 * op2, &top);
				break;
			case divide: push(op1 / op2, &top);
				break;
			case mod: push(op1 % op2, &top);
			}
		}
		token = getToken(&symbol, &n,1);
	}
	return pop(&top);
}

precedence getToken(char* symbol, int* n,int menu) { 
	if (menu == 0) {
		*symbol = expr[(*n)++];
		switch (*symbol) {
		case '(': return lparen;
		case ')': return rparen;
		case '+': return plus;
		case '-': return minus;
		case '/': return divide;
		case '*': return times;
		case '%': return mod;
		case '\0': return eos;
		default: return operand;
		}
	}
	else {
		*symbol = post[(*n)++];
		switch (*symbol) {
		case '(': return lparen;
		case ')': return rparen;
		case '+': return plus;
		case '-': return minus;
		case '/': return divide;
		case '*': return times;
		case '%': return mod;
		case '\0': return eos;
		default: return operand;
		}
	}

}

void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	int top = 0;
	stack[0] = eos;

	for (token = getToken(&symbol, &n,0); token != eos ; token = getToken(&symbol, &n,0)) {
		if (token == operand) {  //��ū�� �ǿ����� �� �� 
			printf("%c", symbol);
			postpush(symbol);
		}
		else if (token == rparen) { // ������ ��ȣ��
			while (stack[top] != lparen) { //���� ��ȣ�� ���ö����� ���
				printToken(pop(&top));
			}
			pop(&top); //���� ��ȣ ����
		}
		else {  
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop(&top));
			}
			push(token, &top);
		}
	}
	while ((token = pop(&top)) != eos) {
		printToken(token);
	}
	printf("\n");
}

void printToken(precedence token) {
	switch (token) {
	case  plus:  
		printf("+");
		postpush('+');
		break;
	case  minus: 
		printf("-");
		postpush('-');
		break;
	case  times:
		printf("*");
		postpush('*');
		break;
	case  divide: 
		printf("/");
		postpush('/');
		break;
	case  mod:    
		printf("%");
		postpush('%');
	}
}

void postpush(char symbol) {
	post[++posttop] = symbol;
}