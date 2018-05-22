#pragma once
#ifndef __LINSEZNAM_H__
#define __LINSEZNAM_H__
#define VELIKOST 50
struct uzivatel {
	int ID;
	char jmeno[VELIKOST];
	char prijmeni[VELIKOST];
	int pocet_rezervaci;
	int rezervace[2][5];
	uzivatel *next;
};

enum menu
{
	pridat = 1,
	vypis,
	najdi,
	smazat,
	uloz,
	nacti,
	edituj,
	konec
};
static const char filePath[] = "./data.txt";
static const char filePath2[] = "./map.txt";

extern int map[7][14];  // mapa 

void nactimapu();
void ulozmapu();
void nactiseznam(uzivatel **zaznam);
void ulozseznam(uzivatel *zaznam);
void pridej(uzivatel **zaznam,int ID, char* prijmeni, char* jmeno, int pocet_rezervaci,int rezervace[2][5]);
void smaz(uzivatel **zaznam, int ID);
void najdizaznam(uzivatel *u, char* prijmeni);
void editujzaznam(uzivatel **zaznam,uzivatel *stare,  char* prijmeni, char* jmeno, int pocet_rezervaci, int rezervace[2][5]);
void tiskradku(uzivatel *u);
void tisk(uzivatel *zaznam);
void tiskmapy();
void tiskoddelovace();
uzivatel* vratzaznam(uzivatel *zaznam, char* najdi);
char *namale(char *text);
int porovnani(char *str1, char *str2);

#endif


