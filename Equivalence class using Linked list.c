#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) \
	if(!((p) = malloc(s))) {\
		printf("Insufficient Memory"); \
		exit(EXIT_FAILURE); \
	}
#define FALSE 0
#define TRUE 1


#include <stdio.h>
#include <stdlib.h>

typedef struct Node* NodePointer;
typedef struct Node {
	int data;
	NodePointer link;
};

int main() {
	FILE* fp;
	NodePointer* seq;
	NodePointer x, y, top;
	int* out;
	int N, M, i, j;
	int leftdata, rightdata;

	if (!(fp = fopen("input.txt", "r"))) {
		printf("FILE OPEN ERROR!");
		return 1;
	}

	fscanf(fp, "%d %d", &N, &M);
	MALLOC(out, sizeof(*out) * N);  
	MALLOC(seq, sizeof(*seq) * N);

	for (i = 0; i < N; i++) { 
		out[i] = TRUE;
		seq[i] = NULL;
	}


	for (i = 0; i < M; i++) {
		fscanf(fp, "%d %d", &leftdata, &rightdata);
		MALLOC(x, sizeof(*x));
		x->data = rightdata; x->link = seq[leftdata]; seq[leftdata] = x;
		MALLOC(x, sizeof(*x));
		x->data = leftdata; x->link = seq[rightdata]; seq[rightdata] = x;
	}

	for (i = 0; i < N; i++) {
		if (out[i] == TRUE) {
			printf("New Class: %d ", i);
			out[i] = FALSE;
			x = seq[i]; top = NULL;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j] == TRUE) {
						printf("%d ", j);
						out[j] = FALSE;
						y = x->link; x->link = top; top = x; x = y;
					}
					else x = x->link;
				}
				if (!top) break;
				x = seq[top->data]; top = top->link;
			}
			printf("\n");
		}
	}

	fclose(fp);

	return 0;
}