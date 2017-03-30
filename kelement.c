#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define cst 500
#define cst2 5
int indice_elmt (int *tab) ;


int main() {

	int tableau[cst], i, indice_max = 0;
	int elements[cst2], lalala = 0;

	srand(time(NULL));
	for (i=0 ; i<cst;i++) tableau[i] = (rand()%10)+1;
	for (i=0 ; i<cst2; i++) elements[i] = tableau[i];
/*	for (i = 0; i<cst; i++) {
		lalala++;
		printf("%d ", tableau[i]);
		if (lalala==25) {
			lalala=0;
			printf("\n");
		}
	}*/


	for (i = 0; i<cst; i++) {
		indice_max = indice_elmt(elements);
		//printf("indice max element: %d\n", indice_max);
		if (tableau[i] < elements[indice_max]) elements[indice_max] = tableau[i];
	}
	//for (i = 0; i<cst2; i++) printf("\n valeur: %d, valeur 2: %d\n", elements[i], tableau[i]);



return 0;
}





int indice_elmt (int *tab) {

	int var, max = tab[0] ;
	int indice = 0;
	for (var = 1 ; var < 5; var++){
		if (tab[var] > max) {
			max = tab[var];
			indice = var;
		}
	}
	//for (var = 0; var<cst2; var++) printf("valeur:%d valeur indice:%d\n", tab[var], indice);
	return indice;
}
