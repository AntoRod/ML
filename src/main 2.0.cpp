
#include "jpg.h"
#include "mnist.h"
#include<limits.h>
#include<math.h>

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

	//STEP 1: INITIALIZATION
	for (int i = 0; i<784; i++) w[i] = (float)rand()*2/INT_MAX-1;
	/*float gamma = (float)rand()*2/INT_MAX-1;
	if (gamma < 0) gamma++;*/

	float gamma = 0.0194445;	/*	14 ERREURS*/


	//STEP 2: LEARNING (que les données de train)
	for (int i = 0; i<60000; i++) {
		//Calcul gradiant ( g = y*x si erreur, 0 sinon)
		int prediction = linear_classifier(w, images[i]);
			int verite = (labels[i] == 1) ? 1 : -1;
			//printf("ERREUR\n");
			if (verite != prediction) {
				//ajout au w actuel (w(t+1) = w(t) - gamma*y*x)
				for (int j = 0; j<784; j++) w[j]+= gamma*verite*images[i][j];
			}
	}


	//STEP 3: TEST (que les données de test)

	float erreur = 0;
    for(int i=0; i<10000; i++) {
		int inference = linear_classifier (w, test_images[i]);
		printf("%u\n", i);
		if ((inference == 1 && test_labels[i] != 1)|| (inference == 0 && test_labels[i] == 1)) 				erreur++ ;
		//save_jpg(test_images[i], 28, 28, "%u/%u.jpg", inference,i );
	printf("L'erreur est de %0.8f%%, %f\n", (erreur*100/i), erreur);

    }
    return 0;
}
















