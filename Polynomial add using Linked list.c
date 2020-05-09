#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) \
	if(!((p) = malloc(s))) {\
		printf("Insufficient Memory"); \
		exit(EXIT_FAILURE); \
	}


#include <stdio.h>
#include <stdlib.h>



typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expo;
	polyPointer link;
}polyNode;


polyPointer createNode(polyPointer,int,int);
polyPointer padd(polyPointer, polyPointer);
void attach(int,int,polyPointer);
void printList(polyPointer);
int compare(int,int); 

int main() {
	FILE* fp1, * fp2;
	polyPointer sumList;
	polyPointer a = NULL, b = NULL;
	char ch;
	int coef, expo;
	int i, num;
	if (!(fp1 = fopen("a.txt", "r")) || !(fp2 = fopen("b.txt", "r"))){
		printf("FILE OPEN ERROR!");
		return 1;
	}

	fscanf(fp1, "%d", &num);   
	for (i = 0; i < num; i++) {
		fscanf(fp1, "%d %d", &coef, &expo);
		a = createNode(a, coef, expo);
	}

	fscanf(fp2, "%d", &num); 
	for (i = 0; i < num; i++) {
		fscanf(fp2, "%d %d", &coef, &expo);
		b = createNode(b, coef, expo);
	}

	sumList = padd(a, b);  
	printList(sumList);    

	fclose(fp1);
	fclose(fp2);

	return 0;
}

polyPointer createNode(polyPointer ptr,int coef,int expo) {
	polyPointer temp;
	polyPointer first;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coef;
	temp->expo = expo;
	temp->link = NULL;

	if (ptr == NULL) {
		return temp;
	}
	else {
		for (first = ptr; first->link; first = first->link);
		first->link = temp;
		return ptr;
	}
}

polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;

	MALLOC(rear, sizeof(*rear));
	c = rear;
	

	while (a && b) {
		switch (compare(a->expo,b->expo)) {
		case -1:  // a->expo < b->expo
			attach(b->coef, b->expo, &rear);
			b = b->link;
			break;
		case 0:  // a->expo == b->expo
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expo, &rear);
			a = a->link; b = b->link;
			break;
		case 1:   // a->expo  > b-> expo
			attach(a->coef,a->expo,&rear);
			a = a->link;
		}
	}

	for (; a; a = a->link) attach(a->coef, a->expo, &rear);
	for (; b; b = b->link) attach(b->coef, b->expo, &rear);
	rear->link = NULL;
	temp = c; c = c->link; free(temp);

	return c;
}

void attach(int coef, int expo,polyPointer *ptr) {
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coef;
	temp->expo = expo;
	(*ptr)->link = temp;
	*ptr = temp;
}


void printList(polyPointer first) {
	for (; first; first = first->link) {
		if (first->expo == 0) {
			printf("%+d ", first->coef);
			break;
		}
		printf("%+dx^%d ", first->coef, first->expo);
	}
	printf("\n");
}

int compare(int a, int b) {
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}
