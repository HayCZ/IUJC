#include "datetime.h"

typedef struct mereni {
	int idMereni;
	tDateTime timestamp;
	float m3;
	struct mereni* dalsi;
} tMereni;

// vrací adresu dynamické alokace mereni, ukazatel dalsi se nastaví na NULL
tMereni* vytvorMereni(int idMereni, tDateTime ts,
	float m3);

//vypíše mereni na obrazovku
void vypisMereni(tMereni* mereni);