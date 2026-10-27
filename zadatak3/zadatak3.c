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
int insertPoslPerson(char* ime, char* prezime, int godina, char* trazi, Position p) {  //	od ovog 
	Position f = findPrezime(p, trazi);
	return f ? insertBegin(ime, prezime, godina, f) : -1;
}
int insertPrijePerson(char* ime, char* prezime, int godina, char* trazi, Position p) { 
	while (p->next && strcmp(p->next->prezime, trazi)) p = p->next;
	return p->next ? insertBegin(ime, prezime, godina, p) : -1;

}
int sortirajList(Position head) {  
	Position i, j; Person t;
	for (i = head->next; i; i = i->next)
		for (j = i->next; j; j = j->next)
			if (strcmp(i->prezime, j->prezime) > 0) {
				strcpy(t.ime, i->ime);
				strcpy(t.prezime, i->prezime);
				t.godina = i->godina;
				strcpy(i->ime, j->ime);
				strcpy(i->prezime, j->prezime);
				i->godina = j->godina;
				strcpy(j->ime, t.ime);
				strcpy(j->prezime, t.prezime);
				j->godina = t.godina;
			}
	return 0;
}
int upis(Position p, char* file) {  
	FILE* f = fopen(file, "w");
	if (!f) return -1;
	for (; p; p = p->next) fprintf(f, "%s %s %d\n", p->ime, p->prezime, p->godina);
	fclose(f);
	return 0;
}
int cita(Position p, char* file) {		//	do ovog
	char ime[30], prezime[30];
	int godina;
	FILE* f = fopen(file, "r");
	if (!f)
		return -1;
	while (fscanf(f, "%29s %29s %d", ime, prezime, &godina) == 3)
		insertEnd(ime, prezime, godina, p);
	fclose(f);
	return 0;
}

int main(void) {
	Person Head = { "", "", 0, NULL };
	Position p = &Head, f;
	char ime[30], prezime[30], trazi[30];
	int godina, c;

	do {
		printf("\n1-Pocetak 2-Ispis 3-Kraj 4-Trazi 5-Brisi 6-Iza 7-Ispred 8-Sort 9-Upis 10-Citaj 0-Izlaz: ");
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
			scanf("%29s", prezime);
			if (c == 4) {
				f = findPrezime(p, prezime);
				f ? printf("%s %s, %d\n", f->ime, f->prezime, f->godina) : printf("Ne postoji\n");
			}
			else if (deletePerson(p, prezime)) printf("ne postoji.\n");
		}
		else if (c == 6 || c == 7) {
			printf("Ime Prezime Godina i prezime trazene osobe: ");
			scanf("%29s %29s %d %29s", ime, prezime, &godina, trazi);
			if (c == 6) insertPoslPerson(ime, prezime, godina, trazi, p);
			else insertPrijePerson(ime, prezime, godina, trazi, p);
		}
		else if (c == 8) sortirajList(p);
		else if (c == 9) upis(p->next, "osobe.txt");
		else if (c == 10) cita(p, "osobe.txt");
	
	} while (c != 0);
	while (Head.next) deletePerson(p, Head.next->prezime);
	return 0;
}