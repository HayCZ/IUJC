#include "datetime.h"
#include <string.h>
#include <stdlib.h>
/* STRUCT
 * typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int dayInMonth;
}tDateTime;
 */

tDateTime dejDateTime(char* aDatetime) {
	tDateTime date;
	date.year = atoi(strtok(aDatetime, "-"));
	date.month = atoi(strtok(NULL, "-"));
	date.day = atoi(strtok(NULL, " "));
	date.hour = atoi(strtok(NULL, ":"));
	date.min = atoi(strtok(NULL, ":"));
	date.sec = atoi(strtok(NULL, ";"));
	date.dayInWeek = dejDenVTydnu(date.year, date.month, date.day);
	return date; 
}
// pøevádí vstup (2018-05-01 01:00:00) na strukturu, využívá dejDenVTydnu

int dejDenVTydnu(int aR, int aM, int aD) {

	//Zjištuje pøestupný rok.
	int prestupny = 0;
	if (aR / 4 > 0 && aR % 4 == 0) {
		if (aR / 100 > 0 && aR % 100 == 0) {
			if (aR / 400 > 0 && aR % 400 == 0) {
				prestupny = 1;
			}
		}
		else {
			prestupny = 1;
		}
	}

	int lastTwoDigitsOfYear = aR % 100;

	int fromTable = 0;
	switch (aM) {
	case 1: fromTable = 6; break; //Leden
	case 2: fromTable = 2; break; //Unor
	case 3: fromTable = 2; break; //Brezen
	case 4: fromTable = 5; break; //Duben
	case 5: fromTable = 0; break; //Kveten
	case 6: fromTable = 3; break; //Cerven
	case 7: fromTable = 5; break; //Cervenec
	case 8: fromTable = 1; break; //Srpen
	case 9: fromTable = 4; break; //Zari
	case 10: fromTable = 6; break; //Rijen
	case 11: fromTable = 2; break; //Listopad
	case 12: fromTable = 4; break; //Prosinec
	}
	if ((prestupny == 1 && aM == 1) || (prestupny == 1 && aM == 2))
		prestupny = -1;
	int num = ((lastTwoDigitsOfYear + (lastTwoDigitsOfYear / 4) + fromTable + prestupny + aD) % 7) - 1;
	if (num == -1) {
		return 6;
	}
	else {
		return num;
	}
}
//vrací den v týdnu (0-PO,…,6-NE) *výpoèet viz poznámka