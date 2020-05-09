#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s)\
		if(!(p = malloc(s))){\
			printf("Insufficient Memory!");\
			exit(EXIT_FAILURE);\
		}
#define MAX_SIZE 100  
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer leftChild;
	treePointer rightChild;
	treePointer parent;
};

void addq(treePointer);
treePointer deleteq();

void convert(int);
void levelorder(int);
void preorder(treePointer);
void inorder(treePointer);
void postorder(treePointer);

void initTree(int);
treePointer makeNode(int);
void makeTree(treePointer);

treePointer root;
treePointer queue[MAX_SIZE];
int arrtree[MAX_SIZE];
int front = 0;
int rear = 0;

int main() {

	FILE* fp1;
	treePointer leftPtr = NULL, rightPtr = NULL, parent = NULL;
	int data, arrsize = 0, i = 1;
	char ch;

	if (!(fp1 = fopen("input.txt", "r"))) {
		printf("FILE OPEN ERROR!");
		return 1;
	}

	ch = fscanf(fp1, "%d", &data);
	while (ch != EOF) {
		arrtree[i++] = data;
		arrsize++;
		ch = fscanf(fp1, "%d", &data);
	}


	printf("Level Order: "); levelorder(arrsize); printf("\n");
	convert(arrsize);
	printf("Preorder: "); preorder(root); printf("\n");
	printf("Inorder: "); inorder(root); printf("\n");
	printf("Postorder: "); postorder(root); printf("\n");

	fclose(fp1);

	return 0;
}

void addq(treePointer ptr) {
	if (rear == MAX_SIZE - 1) {
		printf("Queue is Full!");
		exit(EXIT_FAILURE);
	}
	queue[++rear] = ptr;
}

treePointer deleteq() {
	if (rear == front) {
		printf("Queue is Empty!");
		exit(EXIT_FAILURE);
	}
	return queue[++front];
}

void levelorder(int arrsize) {
	int i;

	for (i = 1; i <= arrsize; i++) {
		if (arrtree[i] == -1)
			continue;
		printf("%d ", arrtree[i]);
	}
}
void convert(int arrsize) {
	treePointer temp;

	int i = 1;

	initTree(arrtree[i]);
	addq(root);

	for (i = 2; i <= arrsize; i++) {
		temp = makeNode(arrtree[i]);
		temp->parent = queue[i / 2];
		addq(temp);
	}

	for (i = 1; i <= arrsize; i++) {
		temp = deleteq();
		makeTree(temp);
	}

}

void preorder(treePointer ptr) {
	if (ptr) {
		if (ptr->data == -1) return;
		printf("%d ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void inorder(treePointer ptr) {
	if (ptr) {

		inorder(ptr->leftChild);
		if (ptr->data == -1) return;
		printf("%d ", ptr->data);;
		inorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {

		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		if (ptr->data == -1) return;
		printf("%d ", ptr->data);
	}

}

void initTree(int data) {
	treePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->parent = NULL;
	root = temp;
}
treePointer makeNode(int data) {
	treePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->parent = NULL;

	return temp;
}

void makeTree(treePointer node) {
	if (node->parent == NULL) {
		return;
	}
	treePointer parent, temp;
	parent = node->parent;

	if (parent->leftChild == NULL) {
		parent->leftChild = node;
	}
	else if (parent->rightChild == NULL) {
		parent->rightChild = node;
	}

}