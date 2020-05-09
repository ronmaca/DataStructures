#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s)\
		if(!(p = malloc(s))){\
			printf("Insufficient Memory!");\
			exit(EXIT_FAILURE);\
		}

#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftChild;
	treePointer rightChild;
};

void preorder(treePointer ptr);
void inorder(treePointer ptr);
void postorder(treePointer ptr);
void initTree(char data);
treePointer makeTree(treePointer parent, char data);

treePointer root;
char data[] = { '+','*','E','*','D','/','C','A','B' };  

int main() {

	treePointer leftPtr = NULL, rightPtr = NULL, parent = NULL;
	int i;

	initTree(data[0]);
	parent = root;
	for (i = 1; i < 9;) {
		leftPtr = makeTree(parent, data[i++]);
		rightPtr = makeTree(parent, data[i++]);
		parent = leftPtr;
	}  // �����͸� �̿��ؼ� Ʈ�� ����

	printf("Preorder: "); preorder(root); printf("\n");
	printf("Inorder: "); inorder(root); printf("\n");
	printf("Postorder: "); postorder(root); printf("\n");

	return 0;
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);;
		inorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}

}

void initTree(char data) {
	treePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	root = temp;
}
treePointer makeTree(treePointer parent, char data) {

	treePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->leftChild = NULL;
	temp->rightChild = NULL;

	if (parent->leftChild == NULL) {
		parent->leftChild = temp;
	}
	else if (parent->rightChild == NULL)
	{
		parent->rightChild = temp;
	}

	return temp;
}