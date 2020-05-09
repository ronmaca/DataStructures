#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) \
	if(!((p) = malloc(s))) {\
		printf("Insufficient Memory"); \
		exit(EXIT_FAILURE); \
	}

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};

listPointer createNode(listPointer, int);
listPointer concatenate(listPointer, listPointer);
listPointer invert(listPointer);
void printList(listPointer);

int main() {
	FILE* fp1;
	FILE* fp2;
	listPointer first = NULL, second = NULL;
	char ch;
	int data;

	if (!(fp1 = fopen("input1.txt", "r")) || !(fp2 = fopen("input2.txt", "r"))) {
		printf("FILE OPEN ERROR");
		return 1;
	}

	ch = fscanf(fp1, "%d", &data);  
	while (ch != EOF) {
		first = createNode(first, data);
		ch = fscanf(fp1, "%d", &data);
	}

	ch = fscanf(fp2, "%d", &data); 
	while (ch != EOF) {
		second = createNode(second, data);
		ch = fscanf(fp2, "%d", &data);
	}


	printf("First:\n");
	printList(first);

	printf("Second:\n");
	printList(second);

	concatenate(first, second);
	printf("Concatenate:\n");
	printList(first);

	first = invert(first);
	printf("Invert:\n");
	printList(first);

	fclose(fp1);
	fclose(fp2);

	return 0;
}

listPointer createNode(listPointer first, int data) {
	listPointer temp;
	listPointer current;

	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->link = NULL;

	if (!first) {   // ��带 ó�� ������ ��
		return temp;
	}
	else {
		for (current = first; current->link; current = current->link);
		current->link = temp;
	}
	return first;
}
listPointer concatenate(listPointer ptr1, listPointer ptr2) {
	listPointer temp;

	if (!ptr1) return ptr2;
	if (!ptr2) return ptr1;

	for (temp = ptr1; temp->link; temp = temp->link);
	temp->link = ptr2;
}
listPointer invert(listPointer lead) {
	listPointer middle, trail;

	middle = NULL;
	while (lead) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}
void printList(listPointer first) {
	int i = 1;
	for (; first; first = first->link) {
		printf("(%p, %d, %p) ", first, first->data, first->link);
		if (!(i++ % 3)) printf("\n");
	}

	printf("\n");
}