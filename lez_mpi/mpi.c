#include <stdio.h>
#include <mpi.h>


int main(int arg, char** argv){

	int rank, world_size;
	int global_sum; 

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int local_sum = 5;

	printf("The local sum is %d with RANK %d\n", local_sum, rank);

	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0){
		printf("The global sum is %d\n", global_sum);
	}

	MPI_Finalize();

	return 0;
}