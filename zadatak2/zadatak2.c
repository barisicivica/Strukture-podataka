#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* Position;
typedef struct _person {
	char ime[30];
	char prezime[30];
	int godina;
	Position next;


} Person;

int insertAfter(Position newP, Position p) {
	newP->next = p->next;
	p->next = newP;
	return 0;


}

int insertBegin(char* ime, char* prezime, int godina, Position p) {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) return -1;
	strcpy(newPerson->ime, ime);
	strcpy(newPerson->prezime, prezime);
	newPerson->godina = godina;
	return insertAfter(newPerson, p);

}

int insertEnd(char* ime, char* prezime, int godina, Position p) {
	while (p->next) p = p->next;
	return insertBegin(ime, prezime, godina, p);


}
int ispis(Position p) {
	for (; p; p = p->next) printf("%s %s, %d\n", p->ime, p->prezime, p->godina);
	return 0;

}
Position findPrezime(Position p, char* prezime) {
	for (p = p->next; p; p = p->next) {
		if (strcmp(p->prezime, prezime) == 0) return p;
	} return NULL;
	
}
int deletePerson(Position head, char* prezime) {
	Position prev = head, curr = findPrezime(prev, prezime);
	if (!curr) return -1;
	while (prev->next != curr) prev = prev->next;
	prev->next = curr->next;
	free(curr);
	return 0;
}

int main(void) {
	Person Head = { "", "", 0, NULL };
	Position p = &Head, f;
	char ime[30], prezime[30];
	int godina, c;

	do {
		printf("\n1-Pocetak 2-Ispis 3-Kraj 4-Trazi 5-Brisi 0-Izlaz: ");
		scanf("%d", &c);
		if (c == 1 || c == 3) {
			printf("Ime Prezime Godina: ");
			scanf("%29s %29s %d", ime, prezime, &godina);
			if (c == 1) 
				insertBegin(ime, prezime, godina, p);
			else
				insertEnd(ime, prezime, godina, p);
		}
		else if (c == 2) ispis(p->next);
		else if (c == 4 || c == 5) {
			printf("Prezime: ");
			scanf("%49s", prezime);
			if (c == 4) {
				f = findPrezime(p, prezime);
				f ? printf("%s %s, %d\n", f->ime, f->prezime, f->godina) : printf("Ne postoji\n");
			}
			else if (deletePerson(p, prezime)) printf("ne postoji.\n");
		}

	} while (c != 0);
	while (Head.next) deletePerson(p, Head.next->prezime);
	return 0;
}