
#include "jpg.h"
#include "mnist.h"
#include<limits.h>


#define cst 0

float dist(float* v1, float* v2) ;
float linear_classifier(float* w, float* x) ;
int indice_element (int *tab, int nbelement) ;





int main()
{
    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");
	float* test_labels = read_labels("t10k-labels.idx1-ubyte");
	float* w = new float[784];
	for (int i = 0; i<784; i++) w[i] = (float)rand()*2/INT_MAX-1;

	float erreur = 0; int constante = 2*cst+1, indice_max = 0;
    for(int i=0; i<500; i++) {
		float mind = -1;
		int NN[constante];
		int distance[constante] ;
		int label_dist[constante] ;
		for (int j = 0; j<60000; j++) {
			// stockage des distances des X NN et des labels dans des tableau non trié
			float d = dist(test_images[i], images[j]);
			if (j < constante) {
				distance[j] = d;
				label_dist[j] = labels[j];
			}
			else {
				indice_max = indice_element(distance, constante);
				if (d < distance[indice_max]) {
					distance[indice_max] = d ;
					label_dist[indice_max] = labels[j];
				}
			}
			// fin de la fonction de stockage
			

			/*float d = dist(test_images[i], images[j]);
			if(d<mind || mind == -1) {
				mind = d;
				NN = j;
			}*/

		}
		//création d'un tableau de 10 chiffres en indice (0 a 9)
		int chiffres[10] = {0,0,0,0,0,0,0,0,0,0} ;
		for (int k = 0; k < constante; k++) chiffres[label_dist[k]]++ ;
		//for (int m = 0; m < constante; m++) printf(" %d ", label_dist[m]);
		//printf("\n");
		//for (int l = 0; l<10; l++) printf(" %d ", chiffres[l]);

		int inference = indice_element(chiffres, 10);
		//int inference = linear_classifier (w, test_images[i]);
		printf("%u, %u\n", i, inference);
		if (inference != test_labels[i]) erreur++ ;//(inference != test_labels[i]) ? erreur++ : ;
		save_jpg(test_images[i], 28, 28, "%u/%u.jpg", inference,i );
	printf("L'erreur est de %0.2f%%\n", (erreur*100/i));
    }

    return 0;
}

float dist(float* v1, float* v2) {
	int i = 0 ;
	float d = 0 ;
	for ( ; i <784 ; i++) {
		d += (v1[i]-v2[i])*(v1[i]-v2[i]) ;
	}
	return d;
}


float linear_classifier(float* w, float* x) {
	float d = 0;
	for (int i = 0; i<784; i++) d+=w[i]*x[i];
	if (d>=0) return 1; else return 0;
}

int indice_element (int *tab, int nbelement) {
	int var, max = tab[0], indice = 0;
	for (var = 1 ; var < nbelement; var++) {
		if (tab[var] > max) {
			max = tab[var] ;
			indice = var;
		}
	}
	return indice;
}










