
#include "jpg.h"
#include "mnist.h"
#include<limits.h>
#include<math.h>
#include<time.h>


float dist(float* v1, float* v2) {
	int i = 0 ;
	float d = 0 ;
	for ( ; i <784 ; i++) {
		d += (v1[i]-v2[i])*(v1[i]-v2[i]) ;
	}
	return d;
}


int main() {
	srand(time(NULL));
	int images_bary[nbelement][60000];
	int K = 100, percent = 60000/K, nbelement = 60000/percent;
	float** images = read_mnist("train-images.idx3-ubyte");
	float bary[nbelement][784] ;
	float bary_temp[nbelement][784];
	
	for (int a=0; a<nbelement; a++) {
		for (int b=0; b<784; b++) {
			bary[a][b] = (float)rand()*2/INT_MAX-1;
		}
	}

	
	int mind = -1, int NN, indice = 0;

	for (int c=0: c<60000; c++) {
		for (d=0; d<nbelement; d++) {
			int distance = dist(images[c],bary[d]);
			if(d<mind || mind == -1) {
				mind = distance;
				NN = d;
				indice = nbelement;
			}


		}
		images_bary[d][c] = indice;





return 0;
}














	/*float** images = read_mnist("train-images.idx3-ubyte");
	int tableau[K], percent = 60000/K;
	int element = 0;
	for (int a = 0; a<60000; a+=percent) {
		tableau[element] = a+abs(rand()%percent);
		element++;
	}
	for (int c = 0; c<K; c++) printf("%d ", tableau[c]);

	for (d=0; d<60000; d++)

*/




































/*
float linear_classifier(float* w, float* x) {
	float d = 0;
	for (int i = 0; i<784; i++) d+=w[i]*x[i];
	if (d>=0) return 1; else return -1;
}


int main()
{

    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");
	float* test_labels = read_labels("t10k-labels.idx1-ubyte");
	float* w = new float[784];


	for (int i = 0; i<784; i++) w[i] = (float)rand()*2/INT_MAX-1;

	float gamma = 0.0194445;	//	14 ERREURS



	for (int i = 0; i<60000; i++) {

		int prediction = linear_classifier(w, images[i]);
			int verite = (labels[i] == 1) ? 1 : -1;

			if (verite != prediction) {

				for (int j = 0; j<784; j++) w[j]+= gamma*verite*images[i][j];
			}
	}




	float erreur = 0;
    for(int i=0; i<10000; i++) {
		int inference = linear_classifier (w, test_images[i]);
		printf("%u\n", i);
		if ((inference == 1 && test_labels[i] != 1)|| (inference == 0 && test_labels[i] == 1)) 				erreur++ ;

	printf("L'erreur est de %0.8f%%, %f\n", (erreur*100/i), erreur);

    }
    return 0;
}
*/















