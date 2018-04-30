#include "stdafx.h"
#include "string"
#include "stdlib.h"
#include "iostream"
#include "fstream"
#include "windows.h"
#include "Divadlo.h"
int map[14][7];
void pridej(uzivatel **zaznam,int ID, char* prijmeni, char* jmeno,int rezervace[2][5]) //pridava do seznamu
{
	int p = 0;
	uzivatel *u = new uzivatel;
	u->ID = ID;
	strcpy_s(u->jmeno, VELIKOST, jmeno);
	strcpy_s(u->prijmeni, VELIKOST, prijmeni);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			u->rezervace[i][j] = rezervace[i][j];
		}
	}
	u->next = NULL;

	uzivatel *temp, *temp2;
	temp = *zaznam;

	if (temp == NULL) {
		*zaznam = u;
		return;
	}
	for (int j = 0; j < 5; j++) {
		if (map[temp->rezervace[0][j]][temp->rezervace[1][j]] > 0)
		{
			p++;
		}
	}

	if (p <= 0) {
		*zaznam = u;
		u->next = temp;
		return;
	}

	p = 0;
	temp2 = temp->next;

	while (temp2 != NULL)
	{
		for (int j = 0; j < 5; j++) {
			if (map[temp->rezervace[0][j]][temp->rezervace[1][j]] > 0)
			{
				p++;
			}
		}

		if (p<=0) {
			temp->next = u;
			return;
		}
		p = 0;
		temp = temp2;
		temp2 = temp2->next;
	}

	temp->next = u;
}
void smaz(uzivatel **zaznam, int ID) { //maze urcite veci ze seznamu

	uzivatel *temp, *temp2;
	temp = *zaznam;

	if (temp) {
		tiskoddelovace();
		printf("Prazdny seznam\n");
		tiskoddelovace();
	}
	if (temp->ID == ID)
	{
		*zaznam = temp->next;
		delete temp;
		return;
	}

	temp2 = temp->next;
	while (temp2 != NULL)
	{
		if (temp2->ID== ID) {
			temp->next = temp2->next;
			delete temp2;
			return;
		}
		temp = temp2;
		temp2 = temp2->next;
	}
	printf("Zaznam nenalezen\n");
	tiskoddelovace();
}
void nactimapu() {
	FILE *soubor;
	int i = 0, j = 0;
	char *a, *next;
	char buffer[256];
	system("cls");
	tiskoddelovace();
	if (fopen_s(&soubor, filePath2, "r") != 0) {
		printf("Nepodarilo se otevrit soubor.\n");	
		tiskoddelovace();
		return;
	}
	//bool prvni = true;
	//while (fgets(buffer, 256, soubor)/*!feof(soubor)*/) {
	//	/*fscanf_s(soubor, "%s", buffer);*/
	//	a = strtok_s(buffer, ",", &next);
	//	while (a!=NULL) {
	//		a = strtok_s(NULL, ",", &next);
	//		if (prvni)
	//		i++;
	//	}
	//	prvni = false;
	//	j++;
	//}
	////int** map =new int[i][j];
	//map = new int*[i];
	//for (int index = 0; index < i; index++) {
	//	map[i] = new int[j];
	//}
	//rewind(soubor);
	//i = 0;
	//j = 0;
	while (fgets(buffer, 256, soubor)/*!feof(soubor)*/) {
		/*fscanf_s(soubor, "%s", buffer);*/
		a = strtok_s(buffer, ",", &next);
		while (a != NULL) {
			map[i][j] = atoi(a);
			a = strtok_s(NULL, ",", &next);
			i++;
		}
		j++;
	}
	fclose(soubor);
	printf("Soubor uspesne nacten\n");
	tiskoddelovace();
}
void nactiseznam(uzivatel **zaznam) { //nacita ze souboru
	FILE *soubor;

	system("cls");
	tiskoddelovace();
	if (fopen_s(&soubor, filePath, "r") != 0) {
		printf("Nepodarilo se otevrit soubor.\n");
		tiskoddelovace();
		return;
	}

	char prijmeni[VELIKOST], jmeno[VELIKOST];
	int ID;
	int rezervace[2][5];
	while (!feof(soubor))
	{
		fscanf_s(soubor, "%d;%[^\;];%[^\;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;\n",&ID, prijmeni, VELIKOST, jmeno, VELIKOST,  &rezervace[0][0], &rezervace[0][1], &rezervace[0][2], &rezervace[0][3], &rezervace[0][4], &rezervace[1][0], &rezervace[1][1], &rezervace[1][2], &rezervace[1][3], &rezervace[1][4]);
		pridej(zaznam, ID, prijmeni, jmeno, rezervace);
	}
	fclose(soubor);
	printf("Soubor uspesne nacten\n");
	tiskoddelovace();
}

void ulozseznam(uzivatel *zaznam) { //uklada zaznamy do souboru
	FILE *soubor;
	tiskoddelovace();
	if (fopen_s(&soubor, filePath, "w+") != 0) {
		printf("Nepodarilo se otevrit soubor");
		tiskoddelovace();
		return;
	};
	char* buffer = NULL;
	while (zaznam != NULL)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 5; j++) {
				buffer += zaznam->rezervace[i][j];
				buffer += ';';
			}
		}
		fprintf_s(soubor, "%d;%s;%s;%s\n",zaznam->ID, zaznam->prijmeni, zaznam->jmeno, buffer);
		zaznam = zaznam->next;
		buffer = NULL;
	}

	fclose(soubor);
	printf("Soubor uspesne ulozen\n");
	tiskoddelovace();
}
void tiskmapy() {
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 7; j++) {
			if(map[i][j]==0) {
				printf("V|");
			}else{
				printf("O|");
			}
						
		}
		printf("\n");
	}
}
void tisk(uzivatel *zaznam) {
	tiskmapy();
}
void najdizaznam(uzivatel *u, char *najdi) { //hleda zaznamy

	tiskoddelovace();
	while (u != NULL) {
		if (strstr(u->prijmeni, najdi) != NULL) {
			//tiskRadku(u);
		}
		u = u->next;
	}
	tiskoddelovace();

}
uzivatel *vratzaznam(uzivatel *zaznam, char *prijmeni) {
	while (zaznam != NULL)
	{
		if (porovnani(zaznam->prijmeni, prijmeni) == 0) {
			return zaznam;
		}
		zaznam = zaznam->next;
	}
	return NULL;
}

void tiskoddelovace() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns = 0;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	for (int i = 0; i < columns - 1; i++)
	{
		printf("=");
	}
	printf("\n");
}
//porovnani øetìzcù
char *namale(char *text) {
	char *pom;
	pom = new char[strlen(text)];
	for (int i = 0; text[i]; i++)
	{
		pom[i] = tolower(text[i]);
	}
	return pom;
}

int porovnani(char *str1, char *str2) {
	return strcmp(namale(str1), namale(str2));

}