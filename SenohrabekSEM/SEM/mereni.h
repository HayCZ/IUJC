#include "datetime.h"

typedef struct mereni {
	int idMereni;
	tDateTime timestamp;
	float m3;
	struct mereni* dalsi;
} tMereni;

// vrac� adresu dynamick� alokace mereni, ukazatel dalsi se nastav� na NULL
tMereni* vytvorMereni(int idMereni, tDateTime ts,
	float m3);

//vyp�e mereni na obrazovku
void vypisMereni(tMereni* mereni);