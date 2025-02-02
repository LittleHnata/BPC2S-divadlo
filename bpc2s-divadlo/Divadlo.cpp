﻿#include "stdafx.h"
#include "string"
#include "stdlib.h"
#include "iostream"
#include "fstream"
#include "windows.h"
#include "Divadlo.h"
int map[7][14]; // mapa
void pridej(uzivatel **zaznam,int ID, char* prijmeni, char* jmeno,int pocet_rezervaci,int rezervace[2][5]) //pridava do seznamu
{
	int p = 0;
	uzivatel *u = new uzivatel;
	u->ID = ID;
	strcpy_s(u->jmeno, VELIKOST, jmeno);
	strcpy_s(u->prijmeni, VELIKOST, prijmeni);
	u->pocet_rezervaci = pocet_rezervaci;
	for (int j = 0; j < pocet_rezervaci; j++) {
		for (int i = 0; i < 2; i++) {
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
	for (int j = 0; j < pocet_rezervaci; j++) {
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
		for (int j = 0; j < pocet_rezervaci; j++) {
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

	if (temp==NULL) {
		tiskoddelovace();
		printf("Prazdny seznam\n");
		tiskoddelovace();
	}
	if (temp->ID == ID)
	{
		*zaznam = temp->next;
		for (int i = 0; i < temp->pocet_rezervaci; i++) {
			map[temp->rezervace[0][i]][temp->rezervace[1][i]] = 0;
		}
		delete temp;
		return;
	}

	temp2 = temp->next;
	while (temp2 != NULL)
	{
		if (temp2->ID == ID) {
			temp->next = temp2->next;
			for (int i = 0; i < temp2->pocet_rezervaci; i++) {
				map[temp2->rezervace[0][i]][temp2->rezervace[1][i]] = 0;
			}
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
	if (fopen_s(&soubor, filePath2, "r+") != 0) {
		printf("Nepodarilo se otevrit soubor.\n");
		tiskoddelovace();
		return;
	}
	while (fgets(buffer, 256, soubor)!=NULL) {
		a = strtok_s(buffer, ";", &next);
		while (a != NULL) {
			map[i][j] = atoi(a);
			a = strtok_s(NULL, ";", &next);
			j++;
		}
		i++;
		j = 0;
	}
	fclose(soubor);
	printf("Soubor uspesne nacten\n");
	tiskoddelovace();
}
void ulozmapu() {
	FILE *soubor;
	if (fopen_s(&soubor, filePath2 ,"w+") != 0) {
		printf("Nepodarilo se otevrit soubor.\n");
		tiskoddelovace();
		return;
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			fprintf_s(soubor, "%d;", map[i][j]);
		}
		fprintf_s(soubor, "\n");
	}
	fclose(soubor);
	printf("Mapa uspesne ulozena\n");
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
	char buffer[256];
	char *a, *next;
	int ID,i=0,pocet=0,pocet_rezervaci;
	int rezervace[2][5];
	while (!feof(soubor))
	{
		fscanf_s(soubor, "%d;%[^\;];%[^\;];%d;%[^\n]",&ID, prijmeni, VELIKOST, jmeno, VELIKOST, &pocet_rezervaci, &buffer, 256);
			a = strtok_s(buffer, ";", &next);
			while (a != NULL) {
				if (i < 2) {
					rezervace[i][pocet] = atoi(a);
					a = strtok_s(NULL, ";", &next);
				}
				i++;
				if (i == 2)	{
					i = 0;
					pocet++;
				}
			}
		pridej(zaznam, ID, prijmeni, jmeno,pocet_rezervaci, rezervace);
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
	}
	while (zaznam != NULL)
	{
		fprintf_s(soubor, "%d;%s;%s;%d;", zaznam->ID, zaznam->prijmeni, zaznam->jmeno, zaznam->pocet_rezervaci);
		for (int j = 0; j < zaznam->pocet_rezervaci; j++) {
			for (int i = 0; i < 2; i++) {
				fprintf_s(soubor, "%d;", zaznam->rezervace[i][j]);
			}
		}
		fprintf_s(soubor, "\n");
		zaznam = zaznam->next;
	}\

	fclose(soubor);
	printf("Soubor uspesne ulozen\n");
	tiskoddelovace();
}
void tiskmapy() {
	printf("------------------------------------\n          jeviste\n");
	for (int i = 0; i < 7; i++) {
		printf("%d|", i+1);
		for (int j = 0; j < 14; j++) {
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
	while (zaznam != NULL) {
		tiskradku(zaznam);
		zaznam = zaznam->next;
	}
	tiskoddelovace();
}
void tiskradku(uzivatel *u){
	printf("ID: %d Prijmeni: %-25s Jmeno: %-25s Pocet rezervaci: %d ",u->ID,u->prijmeni,u->jmeno,u->pocet_rezervaci);
	for (int j = 0; j < u->pocet_rezervaci; j++) {
		printf("Rada: %d Misto: %d",u->rezervace[0][j],u->rezervace[1][j]);
	}
	printf("\n");
}
void najdizaznam(uzivatel *u, char *najdi) { //hleda zaznamy

	tiskoddelovace();
	while (u != NULL) {
		if (strstr(u->prijmeni, najdi) != NULL) {
			tiskradku(u);
		}
		u = u->next;
	}
	tiskoddelovace();

}
void editujzaznam(uzivatel **zaznam, uzivatel *stare, char* prijmeni, char* jmeno, int pocet_rezervaci, int rezervace[2][5]) {
	smaz(zaznam, stare->ID);
	pridej(zaznam, stare->ID, prijmeni, jmeno, pocet_rezervaci, rezervace);
}
uzivatel *vratzaznam(uzivatel *zaznam, int ID) {
	while (zaznam != NULL)
	{
		if (zaznam->ID==ID) {
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
	int i = 0;
	pom = new char[strlen(text)];
	for (i; text[i]; i++)
	{
		pom[i] = tolower(text[i]);
	}
	pom[++i] = '\0';
	return pom;
}

int porovnani(char *str1, char *str2) {
	return strcmp(namale(str1), namale(str2));

}