#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void print_arr(int* arr, int size){
	printf("\n");
	for (int i = 0; i < size; i++){
		printf("%i ", arr[i]);
	}
	printf("\n");
}

int* generate_random_arr(int n){
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++){
		arr[i] = rand() % 100;
	}
	return arr;
}

int main(int argc, char* argv){
	int rank,size;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int ARR_SIZE = 10;
	int* recv_arr;
	int AMNT_NUMS = ARR_SIZE / size;
	int* arr;
	int* mul_arr = (int*) malloc(sizeof(int)*size);

	if (rank == 0){

		arr = generate_random_arr(ARR_SIZE);

		printf("Generated Array\n:");
		print_arr(arr, ARR_SIZE);
	}

	// 0 is root -> sending data to others
	MPI_Scatter(arr, 1, MPI_INT, recv_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0){
		free(arr);
	}

	printf("Rank %i recv data %i\n", rank, *recv_arr);

	*recv_arr *= 2;

	MPI_Allgather(recv_arr, 1, MPI_INT, mul_arr, 1, MPI_INT, MPI_COMM_WORLD);

	if (rank == 0){
		printf("MUL ARR Is");
		print_arr(mul_arr, size);
		free(mul_arr);
	}
	
	

	MPI_Finalize();
}