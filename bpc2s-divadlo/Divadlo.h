#pragma once
#ifndef __LINSEZNAM_H__
#define __LINSEZNAM_H__
#define VELIKOST 50
struct uzivatel {
	int ID;
	char jmeno[VELIKOST];
	char prijmeni[VELIKOST];
	int rezervace[2][5];
	uzivatel *next;
};
enum rezervacenum {
	v = 0, //volno
	o		//obsazeno
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
	vypocti,
	konec
};
static const char filePath[] = "./data.txt";
static const char filePath2[] = "./map.txt";
extern int map[14][7];
void nactimapu();
void nactiseznam(uzivatel **zaznam);
void ulozseznam(uzivatel *zaznam);
void pridej(uzivatel **zaznam,int ID, char* prijmeni, char* jmeno, int rezervace[2][5]);
void smaz(uzivatel **zaznam, int ID);
void najdizaznam(uzivatel *u, char* prijmeni);
void tisk(uzivatel *zaznam);
void tiskmapy();
void tiskoddelovace();
uzivatel* vratzaznam(uzivatel *zaznam, char* najdi);
char *namale(char *text);
int porovnani(char *str1, char *str2);



#endif


