
#include "jpg.h"
#include "mnist.h"

float dist(float* v1, float* v2) ;

int main()
{
    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");

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
        printf("%u\n", i);
		save_jpg(test_images[i], 28, 28, "%u/%04u.jpg", inference,i );
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

















