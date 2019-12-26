typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int dayInWeek;
} tDateTime;

// pøevádí vstup (2018-05-01 01:00:00) na strukturu, využívá dejDenVTydnu
tDateTime dejDateTime(char* datetime);

//vrací den v týdnu (0-PO,…,6-NE) *výpoèet viz poznámka
int dejDenVTydnu(int r, int m, int d);
