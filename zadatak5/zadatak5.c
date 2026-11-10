#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct Stack* Position;
typedef struct Stack {
	int broj;
	Position next;
} stack;

int Push(int broj, Position p) {
	Position q = (Position)malloc(sizeof(stack));
	if (!q) return -1;
	q->broj = broj;
	q->next = p->next;
	p->next = q;
	return 0;
}

int Pop(Position p, int* broj) {
	Position q = p->next;
	if (!q) return -1;
	*broj = q->broj;
	p->next = q->next;
	free(q);
	return 0;
}

int racunaj(Position p, char op) {
	int a, b, r;
	if (Pop(p, &b) || Pop(p, &a)) return -1;
	switch (op) {
		case '+': r = a + b; break;
		case '-': r = a - b; break;
		case '*': r = a * b; break;
		case '/': if (b == 0) return -1; r = a / b; break;
		default: return -1;
	}
	return Push(r, p);
}

int main(void) {
	stack head = { .broj = 0, .next = NULL };
	FILE* f = fopen("postfiks.txt", "r");
	char tok[32];
	int n, k, rez, err = 0;

	if (!f) { printf("Nema datoteke\n"); return 1; }
	while (!err && fscanf(f, "%31s", tok) == 1) {
		if (sscanf(tok, "%d%n", &n, &k) == 1 && tok[k] == '\0')

			err = Push(n, &head);
		else if (tok[1] == '\0')
			err = racunaj(&head, tok[0]);
		else
			err = 1;
	}
	fclose(f);

	if (!err && Pop(&head, &rez) == 0 && head.next == NULL)
		printf("rezultat: %d\n", rez);
	else
		printf("neispravan postfiks\n");
	while (head.next) Pop(&head, &n);
	return 0;
}