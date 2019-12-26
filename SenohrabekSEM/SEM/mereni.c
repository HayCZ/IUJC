#include "mereni.h"
#include <stdio.h>
#include <stdlib.h>

/*typedef struct mereni {
	int idMereni;
	tDateTime timestamp;
	float m3;
	struct mereni *dalsi;
} tMereni;*/

// vrací adresu dynamické alokace senzoru, ukazatel dalsi se nastaví na NULL
tMereni* vytvorMereni(int idMereni, tDateTime ts, float m3) {
	tMereni* m = malloc(sizeof(tMereni));
	m->idMereni = idMereni;
	m->timestamp = ts;
	m->m3 = m3;
	m->dalsi = NULL;
	return m;
}

//vypíše senzor na obrazovku
void vypisMereni(tMereni* senzor) {
	printf("Mereni id: %d, TimeStamp: %d-%d-%d %d:%d:%d, m3: %.6f, diw %d \n", senzor->idMereni, senzor->timestamp.year,
		senzor->timestamp.month, senzor->timestamp.day, senzor->timestamp.hour, senzor->timestamp.min,
		senzor->timestamp.sec, senzor->m3, senzor->timestamp.dayInWeek);
}