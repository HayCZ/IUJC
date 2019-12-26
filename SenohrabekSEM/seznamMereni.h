#include "mereni.h"
#include <stdio.h>


typedef struct {
	int idSenzoru;
	tDateTime datumOd;
	tDateTime datumDo;
	tMereni* seznam;
} tSeznamMereni;


int* dejPoleIdSenzoru(); // vrací pole id všech senzorù v souboru
tSeznamMereni* nactiMereni(
	int idSenzoru); // naète všechna mìøení daného senzoru, využívá vytvorMereni, pokud již nìjaký seznam existuje, musí být dealokován
void vypisMereni(); // vypíše všechna mìøení, využívá vypisMereni
tMereni* odeberMereni(tDateTime timestamp);// odebere a vrátí požadované mìøení ze seznamu
void dealokujSeznam();// smaž (dealokuj) všechny záznamy a
float** analyzuj(tDateTime datumOd,
	tDateTime datumDo);// Výpoèet prùmìru pro všechny kombinace den v týdnu, který vrátí dynamické 2D pole 7x24 „den v týdnu“ x „hodina dne“ (v litrech)
void dealokujMatici();// smaž (dealokuj) matici
float dejOdchylku(
	tDateTime timestamp);//vrátí odchylku v litrech daného záznamu (mìøení v dle timestamp) oproti správnému prùmìru z matice prùmìrù