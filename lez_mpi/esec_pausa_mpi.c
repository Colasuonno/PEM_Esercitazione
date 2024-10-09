#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv){

	// abbiamo un quadrato di lato 2
	// inscriviamo il cerchio (con raggio 1)
	// area cerchio = pi*r^2 = pi
	// area quadrato = 4

	// PUNTI nel cerchio : pi = punti quadrato : 4
	// pi = 4 * punti cerchio / (punti quadrato)



	// prendo dei numeri random da -1 e 1 (x,y)
	// se le coordinate x^2 + y^2 = 1 allora (x,y) sono nel cerchio

	int rank, world_size;

	int global_circles;
	int global_tries;
	int local_tries = 10000000;
	int local_circles = 0;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	srand(rank);
    // Go try
    for (int times = 0; times < local_tries; times++){
    	float x = (rand() / (float)RAND_MAX) * 2 - 1;
    	float y = (rand() / (float)RAND_MAX) * 2 - 1;
    	float distance = x*x + y*y;
    	if (distance <= 1){
    		local_circles++;
    	}
    }

    // go reduce
    MPI_Reduce(&local_circles, &global_circles, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_tries, &global_tries, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    if (rank == 0){
    	printf("We are at rank 0, with #tries %d and #circles %d\n", global_tries, global_circles);
    	double pi = ((double)global_circles*4) / ((double)global_tries);
    	printf("PI Approx is %f\n", pi);
    }

    

	MPI_Finalize();
}




