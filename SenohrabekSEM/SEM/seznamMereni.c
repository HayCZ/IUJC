#include "seznamMereni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



/*
 * typedef struct {
	int idSenzoru;
	tDateTime datumOd;
	tDateTime datumDo;
	tMereni *seznam;
	} tSeznamMereni;
 */

const char* FILE_NAME = "data.csv";
const int MAX_COUNT = 1024;
const int ROWS = 7;
const int COLUMNS = 24;
tSeznamMereni* seznamMereni;
float** array;

const char* getfield(char* line, int num); //Slou�� pro z�sk�n� sloupce.
const int* compareTo(tDateTime date1, tMereni* mereni); //Slou�� pro porovn�n� dat;

// vrac� pole id v�ech senzor� v souboru
int* dejPoleIdSenzoru()
{
	FILE* file = fopen(FILE_NAME, "r");
	int sizeOfArray = 10, iterations = 0, countOfId = 0, currID = 0;
	int* arrayOfId = (int)malloc(sizeOfArray * sizeof(int));
	char line[1024];
	while (fgets(line, MAX_COUNT, file))
	{
		iterations++;
		if (iterations == 1)
		{
			continue;
		}
		else if (countOfId == sizeOfArray)
		{
			sizeOfArray *= 2;
			int* tmpArray = realloc(arrayOfId, (sizeOfArray * sizeof(int)));
			arrayOfId = tmpArray;
		}
			char* tmp = _strdup(line);
			auto t = getfield(tmp, 2);
			int a = atoi(t);
			free(tmp);
			int match = 0;
			for (int j = 0; j < countOfId; ++j)
			{
				if (arrayOfId[j] == a)
				{
					match = 1;
					break;
				}
			}
			if (match == 0)
			{
				arrayOfId[countOfId] = a;
				countOfId++;
			}
	}
	if (countOfId < sizeOfArray){
		arrayOfId[countOfId] = -1;
	}
	return arrayOfId;
}

// na�te v�echna m��en� dan�ho senzoru, vyu��v� vytvorMereni, pokud ji� n�jak� seznam existuje, mus� b�t dealokov�n
tSeznamMereni* nactiMereni(int idSenzoru)
{
	dealokujSeznam();
	seznamMereni = malloc(sizeof(tSeznamMereni));
	FILE* stream = fopen(FILE_NAME,"r");
	char line[1024];
	int run = 0, init = 0;
	tMereni* posledniMereni = NULL;
	while (fgets(line, 1024, stream))
	{
		run++;
		if (run > 1) {
			char* tmp = _strdup(line);
			int idMereni = atoi(strtok(tmp, ";"));
			int idNactenehoSenzoru = atoi(strtok(NULL, ";"));
			char* dateChar = strtok(NULL, ";");
			float m3 = atof(strtok(NULL, "\n"));
			tDateTime date = dejDateTime(strtok(dateChar, ";"));
			if(idNactenehoSenzoru == idSenzoru){
				tMereni* mereni = vytvorMereni(idMereni, date, m3);
					if (init == 0) {
						init++;
						seznamMereni->idSenzoru = idSenzoru;
						seznamMereni->datumOd = mereni->timestamp;
						seznamMereni->seznam = mereni;
						posledniMereni = mereni;
					}
					else {
						posledniMereni->dalsi = mereni;
						mereni->dalsi = NULL;
						posledniMereni = mereni;
					}
					mereni = NULL;
					free(mereni);
			}
			dateChar = NULL;
			free(dateChar);
			free(tmp);
		}
	}
	if (posledniMereni != NULL) {
		seznamMereni->datumDo = posledniMereni->timestamp;
		printf("Uspesne nacteno: Seznam mereni pro senzor id:%d, Datum od: %d-%d-%d, datum do: %d-%d-%d\n", seznamMereni->idSenzoru,
			seznamMereni->datumOd.day, seznamMereni->datumOd.month, seznamMereni->datumOd.year,
			seznamMereni->datumDo.day, seznamMereni->datumDo.month, seznamMereni->datumDo.year);
		posledniMereni = NULL;
		free(posledniMereni);
		return seznamMereni;
	}
	else {
		printf("Zadne id nebylo nalezeno.\n");
		free(posledniMereni);
		return NULL;
	}
}

// odebere a vr�t� po�adovan� m��en� ze seznamu
tMereni* odeberMereni(tDateTime timestamp)
{
	tMereni* mereni = NULL;
	tMereni* lastMereni = NULL;
	int run = 0;
	while (1)
	{
		if (seznamMereni != NULL) {
			run++;
			if (run == 1) {
				lastMereni = seznamMereni->seznam;
				mereni = seznamMereni->seznam;
			}
			else if (mereni->dalsi != NULL) {
				lastMereni = mereni;
				mereni = mereni->dalsi;
			}
			else {
				break;
			}
			if (mereni->timestamp.day == timestamp.day && mereni->timestamp.month == timestamp.month &&
				mereni->timestamp.year == timestamp.year && mereni->timestamp.hour == timestamp.hour &&
				mereni->timestamp.min == timestamp.min && mereni->timestamp.sec == timestamp.sec) {
				if (run == 1) {
					seznamMereni->seznam = mereni->dalsi;
					seznamMereni->datumOd = mereni->dalsi->timestamp;
				}
				lastMereni->dalsi = mereni->dalsi;
				return mereni;
			}
		}
		else {
			break;
		}
	}
	mereni = NULL;
	lastMereni = NULL;
	free(mereni);
	free(lastMereni);
	return NULL;
}


// sma� (dealokuj) v�echny z�znamy a
void dealokujSeznam()
{
	int run = 0;
	tMereni* mereni = NULL;
	tMereni* mereni2 = NULL;
	if (seznamMereni != NULL) {
	while (1)
	{
			run++;
			if (run == 1) {
				if (seznamMereni->seznam->dalsi != NULL)
				{
					mereni = seznamMereni->seznam->dalsi;
					free(seznamMereni->seznam);
				}
				else {
					free(seznamMereni->seznam);
					free(mereni);
					free(mereni2);
					break;
				}
			} else if (mereni != NULL && mereni->dalsi != NULL ) {
					mereni2 = mereni;
					mereni = mereni->dalsi;
					free(mereni2);
				}
			else {
				free(mereni);
				seznamMereni = NULL;
				free(seznamMereni);
				break;
			}
		}
	}
	else {
			free(mereni);
			free(mereni2);
			free(seznamMereni);
	}
}

// V�po�et pr�m�ru pro v�echny kombinace den v t�dnu, kter� vr�t� dynamick� 2D pole 7x24 �den v t�dnu� x �hodina dne� (v litrech)
float** analyzuj(tDateTime datumOd, tDateTime datumDo)
{
	int i, y;
	array = (float**)calloc(ROWS,sizeof(float*));
	int** countArray =  (int**)calloc(ROWS,sizeof(int*));
	for (i = 0; i < ROWS; i++) {
		array[i] = (float*) malloc(COLUMNS * sizeof(float));
		countArray[i] = (int*) malloc(COLUMNS * sizeof(int));
		for (y = 0; y < COLUMNS; y++) {
			array[i][y] = 0;
			countArray[i][y] = 0;
		}
	}

	int run = 0;
		tMereni* mereni = NULL;
		while (1)
		{
			run++;
			if (run == 1) {
				mereni = seznamMereni->seznam;
				if (seznamMereni->seznam->dalsi == NULL)
					break;
				
			}
			if (mereni != NULL) {
				if (compareTo(datumOd, mereni) == 1 || compareTo(datumOd, mereni)==0) {
					if (compareTo(datumDo, mereni) == -1 || compareTo(datumDo, mereni) == 0) {
						array[mereni->timestamp.dayInWeek][mereni->timestamp.hour] += (mereni->m3 * 1000);
						countArray[mereni->timestamp.dayInWeek][mereni->timestamp.hour] = countArray[mereni->timestamp.dayInWeek][mereni->timestamp.hour]+1;
					}
				} if (mereni->dalsi != NULL) {
					mereni = mereni->dalsi;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}

		for (i = 0; i < ROWS; i++) {
			for (y = 0; y < COLUMNS; y++) {
				array[i][y] = array[i][y] / countArray[i][y];
			}
			free(countArray[i]);
		}
		mereni = NULL;
		free(countArray);
		free(mereni);
	return array;
}

// sma� (dealokuj) matici
void dealokujMatici()
{
	if (array != NULL) {
		for (int i = 0; i < ROWS; i++)
			free(array[i]);
		free(array);
	}
}

//vr�t� odchylku v litrech dan�ho z�znamu (m��en� v dle timestamp) oproti spr�vn�mu pr�m�ru z matice pr�m�r�
float dejOdchylku(tDateTime timestamp)
{
	int run = 0;
	tMereni* mereni = NULL;
	while (1)
	{
		run++;
		if (run == 1) {
			mereni = seznamMereni->seznam;
			if (seznamMereni->seznam->dalsi == NULL)
				break;
		}
		if (compareTo(timestamp, mereni) == 0) {
			return array[mereni->timestamp.dayInWeek][mereni->timestamp.hour] - (mereni->m3 * 1000);
		}
		if (mereni->dalsi != NULL) {
			mereni = mereni->dalsi;
		}
		else {
			break;
		}
	}
	mereni = NULL;
	free(mereni);
	return 0;
}

//Porovn�v�n� data
//return  1 -> Date1 je star�� ne� date2
//return  0 -> Data jsou schodn�
//return -1 -> Date2 je star�� ne� date1. 
const int* compareTo(tDateTime date1, tMereni* mereni) {
	if (date1.year > mereni->timestamp.year) {
		return -1;
	}else if (date1.year < mereni->timestamp.year) {
		return 1;
	}else if (date1.year == mereni->timestamp.year) {
		if (date1.month > mereni->timestamp.month) {
			return -1;
		}
		else if (date1.month < mereni->timestamp.month) {
			return 1;
		}
		else if (date1.month == mereni->timestamp.month) {
			if (date1.day > mereni->timestamp.day) {
				return -1;
			}
			else if (date1.day < mereni->timestamp.day) {
				return 1;
			}
			else if (date1.day == mereni->timestamp.day) {
				if (date1.hour > mereni->timestamp.hour) {
					return -1;
				}
				else if (date1.hour < mereni->timestamp.hour) {
					return 1;
				}
				else if (date1.hour == date1.hour) {
					if (date1.min > mereni->timestamp.min) {
						return -1;
					}
					else if (date1.min < mereni->timestamp.min) {
						return 1;
					}
					else if (date1.min == mereni->timestamp.min) {
						if (date1.sec > mereni->timestamp.sec) {
							return -1;
						}
						else if (date1.sec < mereni->timestamp.sec) {
							return 1;
						}
						else if (date1.sec == mereni->timestamp.sec) {
							return 0;
						}
					}
				}
			}

		}
	
	}

	return 911;
}

//Slou�� pro dej pole ID senzor�
const char* getfield(char* line, int num)
{
	const char* tok;
	for (tok = strtok(line, ";");
	     tok && *tok;
	     tok = strtok(NULL, ";\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}
