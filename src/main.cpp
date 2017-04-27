
#include "jpg.h"
#include "mnist.h"
#include<limits.h>
#include<math.h>



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
	if (d>=0) return 1; else return -1;
}


int main()
{

    float** images = read_mnist("train-images.idx3-ubyte");
	float* labels = read_labels("train-labels.idx1-ubyte");
	float** test_images = read_mnist("t10k-images.idx3-ubyte");
	float* test_labels = read_labels("t10k-labels.idx1-ubyte");
	float* w = new float[784];

	//PARTIE KMEANS
	int K = 10;
	float A[K][784];
	float B[K][784];
	int* n = new int[K];



	//1) init
	for (int i=0; i<K; i++) {//1
		n[i] = 0;
		for (int j=0; j<784; j++) {//2
			A[i][j] = images[i][j];  // random: (float)rand()*2/INT_MAX-1;
			B[i][j] = 0;
		}//2
	}//1

	//2) main loop
	for (int t=0; t<1000; t++) {//10
		//STEP 1
		for (int i=0; i<K; i++){//20
			n[i]=0;
			for (int j=0; j<784; j++) B[i][j] = 0;
		}//20


		//STEP 2
		for (int i=0; i<60000; i++) {//21
			printf("t=%u, i=%u\n", t, i);
			// trouver le gagnant = argmin ||x- mu k||
			float mind = -1 ; int gagnant = 0;
			for (int k=0; k<K; k++) {//30
				float d = dist(A[k], images[i]);
				if(d<mind || mind == -1) {//40
					mind = d; gagnant = k;
				}//40
			}//30
			//accumulation des images dans les barycentres de leur cellules gagnantes
			for (int j = 0; j<784; j++) B[gagnant][j] += images[i][j];
				n[gagnant]++;
		}//21

			//Step 3 : calcul des barycentres a partir des accumulation (somme/nombre)
			for (int k=0; k<K; k++) {//31
				for (int j=0; j<784; j++) {//41
					A[k][j] = B[k][j]/n[k];
				}//41

			}//31

			//step 4 : sauvegarde
			for (int k=0; k<K; k++) {//32		
				save_jpg(A[k], 28, 28, "%u/%u.jpg", k, t);
			}//32
	}//10
return 0;
}	


/*
	//STEP 1: INITIALIZATION
	for (int i = 0; i<784; i++) w[i] = (float)rand()*2/INT_MAX-1;
//	float gamma = (float)rand()*2/INT_MAX-1;
//	if (gamma < 0) gamma++;

	float gamma = 0.02;	//	14 ERREURS


	//STEP 2: LEARNING (que les données de train)
	for (int i = 0; i<100; i++) {
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
		float mind = -1;
		int NN;
		int inference = linear_classifier (w, test_images[i]);
		printf("%u\n", i);
		if ((inference == 1 && test_labels[i] != 1)|| (inference == 0 && test_labels[i] == 1)) erreur++ ;
		//(inference != test_labels[i]) ? erreur++ : ;
		//save_jpg(test_images[i], 28, 28, "%u/%u.jpg", inference,i );
	printf("L'erreur est de %0.8f%%, %f\n", (erreur*100/i), erreur);

    }
    return 0;
}



*/












