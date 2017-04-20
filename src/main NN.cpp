
#include "jpg.h"
#include "mnist.h"
#include<limits.h>

float dist(float* v1, float* v2) ;
float linear_classifier(float* w, float* x) {
	float d = 0;
	for (int i = 0; i<784; i++) d+=w[i]*x[i];
	if (d>=0) return 1; else return 0;
}


int main()
{
    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");
	float* test_labels = read_labels("t10k-labels.idx1-ubyte");
	float* w = new float[784];
	for (int i = 0; i<784; i++) w[i] = (float)rand()*2/INT_MAX-1;

	float erreur = 0;
    for(int i=0; i<10000; i++) {
		float mind = -1;
		int NN;
		for (int j = 0; j<60000; j++) {
			float d = dist(test_images[i], images[j]);
			if(d<mind || mind == -1) {
				mind = d;
				NN = j;
			}
		}
		int inference = labels[NN];
		//int inference = linear_classifier (w, test_images[i]);
        printf("%u\n", i);
		if (inference != test_labels[i]) erreur++ ;//(inference != test_labels[i]) ? erreur++ : ;
		//save_jpg(test_images[i], 28, 28, "%u/%u.jpg", inference,i );
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

















