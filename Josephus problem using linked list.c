#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s)\
		if(!(p = malloc(s))){\
			printf("Insufficient Memory!");\
			exit(EXIT_FAILURE);\
		}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node* NodePtr;
typedef struct Node {
	int number;
	NodePtr link;
};


void playGame(int, int);
void firstNode(int);
NodePtr insertNode(NodePtr, int);
void deleteNode(NodePtr);

NodePtr head;

int main() {
	FILE* fp1;

	int wordsNum;
	int friendsNum;


	if (!(fp1 = fopen("input.txt", "r"))) {
		printf("FILE OPEN ERROR!");
		return 1;
	}

	fscanf(fp1, "%d %d", &friendsNum, &wordsNum);
	playGame(friendsNum, wordsNum);

	fclose(fp1);
}

void playGame(int friendsNum, int wordsNum) {
	NodePtr temp, cur;
	int i = 1;

	firstNode(i);
	temp = head;
	for (i = 2; i <= friendsNum; i++) {
		temp = insertNode(temp, i);
	}
	cur = temp;
	temp->link = head;

	while (1) {

		for (i = 1; i <= wordsNum; i++) {
			cur = cur->link;
		}

		deleteNode(cur);

		if (cur == cur->link)    // 자기자신을 가리킬 때, 즉 노드가 1개남았을때 break;
			break;
	}

	printf("%d", cur->number);  //결과값
}

void firstNode(int number) {
	NodePtr temp;
	MALLOC(temp, sizeof(*temp));
	temp->number = number;
	temp->link = NULL;

	head = temp;
}

NodePtr insertNode(NodePtr ptr, int number) {
	NodePtr temp;
	MALLOC(temp, sizeof(*temp));
	temp->number = number;
	temp->link = NULL;

	ptr->link = temp;
	return temp;
}

void deleteNode(NodePtr ptr) {
	NodePtr temp = ptr;

	for (; temp->link != ptr; temp = temp->link);
	temp->link = ptr->link;
}