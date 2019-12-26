#include <stdio.h>
#include "seznamMereni.h"

void vypisIdVsechSenzoru();
void vypisNactenaMereni();
void odeberMereniZeSeznamu(char* date);
void vypisMenu();
void vypisAnalyzu(char* datumOd, char* datumDo);
void ulozAnalyzu(char* datumOd, char* datumDo);

tSeznamMereni* seznam = NULL;

void main() {
	//MENU
	vypisMenu();
	int run = 1;
	while (run) {
		int idSenzoru = NULL, volba = NULL;
		char datum[20] = { 0 }, cas[10] = { 0 }, datum2[20] = { 0 }, cas2[10] = { 0 };
		printf("-----------------------------------------------------------------------------\n");
		printf("Zvolte prosim polozku z menu (zobrazit moznosti menu - 10): ");
		scanf("%d", &volba);
		printf("-----------------------------------------------------------------------------\n");
		switch (volba)
		{
		case 0:
			memset(datum, 0, sizeof datum);
			memset(cas, 0, sizeof cas);
			memset(datum2, 0, sizeof datum2);
			memset(cas2, 0, sizeof cas2);
			fflush(stdin);
			run=0;
			free(seznam);
			break;
		case 1:
			vypisIdVsechSenzoru();
			break;
		case 2:
			printf("Zadejte ID pozadoveneho senzoru:");
			scanf("%d", &idSenzoru);
			seznam = nactiMereni(idSenzoru);
			break;
		case 3:
			vypisNactenaMereni();
			break;
		case 4:
			printf("Zadejte prosim datum (YYYY-MM-DD): ");
			scanf("%s", &datum);
			printf("Zadejte prosim cas (HH:MM:SS): ");
			scanf("%s", &cas);
			strcat(datum, " ");
			strcat(datum, cas);
			odeberMereniZeSeznamu(datum);
			break;
		case 5:
			printf("Zvoleno:  Vypis analyzu nacteneho senzoru\n");
			printf("Zadejte prosim datum od (YYYY-MM-DD): ");
			scanf("%s", &datum);
			printf("Zadejte prosim cas od (HH:MM:SS): ");
			scanf("%s", &cas);
			strcat(datum, " ");
			strcat(datum, cas);
			printf("Zadejte prosim datum do (YYYY-MM-DD): ");
			scanf("%s", &datum2);
			printf("Zadejte prosim cas do (HH:MM:SS): ");
			scanf("%s", &cas2);
			strcat(datum2, " ");
			strcat(datum2, cas2);
			vypisAnalyzu(datum, datum2);
			break;
		case 6:
			printf("Zvoleno: Uloz analyzu do CSV\n");
			printf("Zadejte prosim datum od (YYYY-MM-DD): ");
			scanf("%s", &datum);
			printf("Zadejte prosim cas od (HH:MM:SS): ");
			scanf("%s", &cas);
			strcat(datum, " ");
			strcat(datum, cas);
			printf("Zadejte prosim datum do (YYYY-MM-DD): ");
			scanf("%s", &datum2);
			printf("Zadejte prosim cas do (HH:MM:SS): ");
			scanf("%s", &cas2);
			strcat(datum2, " ");
			strcat(datum2, cas2);
			ulozAnalyzu(datum, datum2);
			break;
		case 7:
			printf("Zvoleno: Vypis odchylku senzoru\n");
			printf("Zadejte prosim datum (YYYY-MM-DD): ");
			scanf("%s", &datum);
			printf("Zadejte prosim cas (HH:MM:SS): ");
			scanf("%s", &cas);
			strcat(datum, " ");
			strcat(datum, cas);
			printf("Odchylka pro zadany datum je: %.6f \n", dejOdchylku(dejDateTime(datum)));
			break;
		case 8:
			dealokujMatici();
			printf("Matice byla dealokovana\n");
			break;
		case 9:
			dealokujSeznam();
			printf("Seznam byl dealokovan\n");
			break;
		case 10:
			vypisMenu();
			break;
		default:
			fflush(stdin);
			break;
		}
	}
	_CrtDumpMemoryLeaks();
}

void vypisMenu() {
	printf("-----------------------------------------------------------------------------\n");
	printf("==============Semestralni prace IUJC 2019 - David Senohrabek=================\n");
	printf("-----------------------------------------------------------------------------\n");
	printf("MENU:\n");
	printf(" 0) Ukoncit program (Neprovede dealokaci seznamu a matice!)\n");
	printf(" 1) Vypis vsechny ID senzoru\n");
	printf(" 2) Nacti mereni podle ID senzoru\n");
	printf(" 3) Vypis nactena mereni podle ID senzoru\n");
	printf(" 4) Odeber mereni\n");
	printf(" 5) Vypis analyzu nacteneho senzoru\n");
	printf(" 6) Uloz analyzu do CSV\n");
	printf(" 7) Vypis odchylku senzoru\n");
	printf(" 8) Dealkouj matici (Analyza)\n");
	printf(" 9) Smaz vsechna mereni\n");
	printf("10) Zobrazit menu znovu\n");
}

void vypisIdVsechSenzoru() {
	printf("Vypisuji vsechna id senzoru: \n");
	int* i = dejPoleIdSenzoru();
	for (size_t j = 0; i[j] != -1; j++)
	{
		printf("%d \n", i[j]);
	}
	free(i);
}

void vypisNactenaMereni() {
	int run = 0;
	tMereni* mereni = NULL;
	while (1)
	{
		if (seznam != NULL) {
			run++;
			if (run == 1) {
				vypisMereni(seznam->seznam);
				if (seznam->seznam->dalsi == NULL)
					break;
				mereni = seznam->seznam->dalsi;
			}
			vypisMereni(mereni);
			if (mereni->dalsi != NULL) {
				mereni = mereni->dalsi;
			}
			else {
				break;
			}
		}
		else {
			printf("V seznamu nejsou zadna data!\n");
			break;
		}
	}
	mereni = NULL;
	free(mereni);
}

void odeberMereniZeSeznamu(char* date) {
	char* tmp = _strdup(date);
	tMereni* odebraneM = odeberMereni(dejDateTime(tmp));
	free(tmp);
	if (odebraneM != NULL) {
		printf("Odebrano:");
		vypisMereni(odebraneM);
	}
	else {
		printf("Seznam mereni je prazdny nebo hledany prvek neexistuje! \n");
	}
	tmp = NULL;
	free(tmp);
	free(odebraneM);
}

void ulozAnalyzu(char* datumOd, char* datumDo) {
	char* tmp = _strdup(datumOd);
	char* tmp2 = _strdup(datumDo);
	float** arr = analyzuj(dejDateTime(tmp), dejDateTime(tmp2));
	FILE* stream = fopen("analyza.csv", "w+");
	fprintf(stream, "den/hod;0;1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21;22;23\n");
	for (int i = 0; i < 7; i++) {
		fprintf(stream, "%d;", i);
		for (int j = 0; j < 24; j++) {
			fprintf(stream, "%6f;", arr[i][j]);
		}
		fprintf(stream, "\n");
	}
	fclose(stream);
	free(tmp);
	free(tmp2);
	printf("Analyza byla uspesne ulozena. Soubor byl pojmenovan analyza.csv\n");
}

void vypisAnalyzu(char* datumOd, char* datumDo) {
	char* tmp = _strdup(datumOd);
	char* tmp2 = _strdup(datumDo);
	float** arr = analyzuj(dejDateTime(tmp), dejDateTime(tmp2));
	printf("----------------------------------------------------(Pro spravne zobrazeni maximalizujte okno aplikace)-------------------------------------------------------\n");
	printf("%-10s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s %-7s",
			"den/hod", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23");
	for (int i = 0; i < 7; i++) {
		printf("\n");
		printf("%-10d", i);
		for (int j = 0; j < 24; j++) {
			printf(" %-7.4f", arr[i][j]);
		}
	}
	free(tmp);
	free(tmp2);
	printf("\n----------------------------------------------------(Pro spravne zobrazeni maximalizujte okno aplikace)-------------------------------------------------------\n");
}

