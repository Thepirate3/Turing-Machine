// Structura utilizata pentru o citire mai eficienta a tranzitiilor
typedef struct tranzitie{
	
	char stare_cur[100]; // starea curenta a masinilor
	char cuv1; // cuvantul pentru masina 1
	char cuv2; // cuvantul pentru masina 2
	char stare_urm[100]; // starea in care trec masinile
	char cuv1_next; // cuvantul de scris pe prima banda
	char cuv2_next; // cuvantul de scris pe a doua banda
	char deplasare1; // sensul deplasarii benzii 1
	char deplasare2; // sensul deplasarii benzii 2

	}Tranzitie;
