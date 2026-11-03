#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;
typedef struct Poly {
	int coeff;
	int pow;
	Position next;
} polynom;

int insertSorted(Position q, int coeff, int pow) {
	Position n;
	while (q->next && q->next->pow > pow) q = q->next;
	if (q->next && q->next->pow == pow) {
		q->next->coeff += coeff;
		if (q->next->coeff == 0) { n = q->next; q->next = n->next; free(n); }
		return 0;
	}
	if (coeff == 0) return 0;
	n = (Position)malloc(sizeof(polynom));
	if (!n) return -1;
	n->coeff = coeff; n->pow = pow;
	n->next = q->next; q->next = n;
	return 0;
}

int readPoly(FILE* f, Position head) {
	char line[256], * s = line;
	int c, e, n;
	if (!fgets(line, sizeof(line), f)) return -1;
	while (sscanf(s, " %d %d%n", &c, &e, &n) == 2) {
		if (insertSorted(head, c, e)) return -1;
		s += n;
	}
	return 0;
}

int zbroji(Position a, Position b, Position r) {
	for (a = a->next; a; a = a->next) insertSorted(r, a->coeff, a->pow);
	for (b = b->next; b; b = b->next) insertSorted(r, b->coeff, b->pow);
	return 0;
}

int pomnozi(Position a, Position b, Position r) {
	Position j;
	for (a = a->next; a; a = a->next)
		for (j = b->next; j; j = j->next)
			if (insertSorted(r, a->coeff * j->coeff, a->pow + j->pow)) return -1;
	return 0;
}

int ispis(Position p) {
	if (!p->next) printf("0");
	for (p = p->next; p; p = p->next) printf("%+dx^%d ", p->coeff, p->pow);
	printf("\n");
	return 0;
}

int brisiSve(Position head) {
	Position t;
	while (head->next) { t = head->next; head->next = t->next; free(t); }
	return 0;
}

int main(void) {
	polynom headF = { 0, 0, NULL }, headS = { 0, 0, NULL }, sum = { 0, 0, NULL }, prod = { 0, 0, NULL };
	FILE* f = fopen("polinomi.txt", "r");

	if (!f) { printf("Ne moze se otvoriti datoteka!\n"); return 1; }
	if (readPoly(f, &headF) || readPoly(f, &headS)) {
		printf("Greska pri citanju polinoma!\n");
		fclose(f);
		return 1;
	}
	fclose(f);

	printf("P1: "); ispis(&headF);
	printf("P2: "); ispis(&headS);
	if (zbroji(&headF, &headS, &sum)) printf("Greska pri zbrajanju!\n");
	else { printf("Zbroj:   "); ispis(&sum); }
	if (pomnozi(&headF, &headS, &prod)) printf("Greska pri mnozenju!\n");
	else { printf("Umnozak: "); ispis(&prod); }

	brisiSve(&headF); brisiSve(&headS); brisiSve(&sum); brisiSve(&prod);
	return 0;
}