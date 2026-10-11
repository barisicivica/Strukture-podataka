#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 0;
	char buffer[50] = { 0 };
	int brojac = 0;
	FILE* fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("greska");
		return -1;
	}
	while (fgets(buffer, 50, fp) != NULL) {
		brojac++;


	}
	fclose(fp);
	fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("greska");
		return 1;



	}
	typedef struct _student {
		char ime[50];
		char prezime[50];
		int bodovi;
	}
	stud;
	stud* studenti = NULL;
	studenti = (stud*)malloc(brojac * sizeof(stud));
	if (!studenti) {
		printf("greska");
		free(studenti);
		return -1;

	}
	

	for (i = 0;i < brojac;i++) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}
	fclose(fp);
	int max_br_bodova = 0;
	for (i = 0; i < brojac; i++) {
		if (studenti[i].bodovi > max_br_bodova)
			max_br_bodova = studenti[i].bodovi;
	}

	for (i = 0; i < brojac; i++) {
		float relativni = (float)studenti[i].bodovi / max_br_bodova * 100;
		printf("%s %s %d %.2f%%\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni);



	}
	free(studenti);
	return 0;
}



