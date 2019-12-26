#include "mereni.h"
#include <stdio.h>


typedef struct {
	int idSenzoru;
	tDateTime datumOd;
	tDateTime datumDo;
	tMereni* seznam;
} tSeznamMereni;


int* dejPoleIdSenzoru(); // vrac� pole id v�ech senzor� v souboru
tSeznamMereni* nactiMereni(
	int idSenzoru); // na�te v�echna m��en� dan�ho senzoru, vyu��v� vytvorMereni, pokud ji� n�jak� seznam existuje, mus� b�t dealokov�n
void vypisMereni(); // vyp�e v�echna m��en�, vyu��v� vypisMereni
tMereni* odeberMereni(tDateTime timestamp);// odebere a vr�t� po�adovan� m��en� ze seznamu
void dealokujSeznam();// sma� (dealokuj) v�echny z�znamy a
float** analyzuj(tDateTime datumOd,
	tDateTime datumDo);// V�po�et pr�m�ru pro v�echny kombinace den v t�dnu, kter� vr�t� dynamick� 2D pole 7x24 �den v t�dnu� x �hodina dne� (v litrech)
void dealokujMatici();// sma� (dealokuj) matici
float dejOdchylku(
	tDateTime timestamp);//vr�t� odchylku v litrech dan�ho z�znamu (m��en� v dle timestamp) oproti spr�vn�mu pr�m�ru z matice pr�m�r�