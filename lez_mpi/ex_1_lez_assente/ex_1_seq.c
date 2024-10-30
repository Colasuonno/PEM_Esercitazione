#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix {
	int** matrix;
	size_t size;
} matrix;

matrix gen_rand_matrix(int size);

matrix multiply_matrix(matrix m1, matrix m2);

void print_matrix(matrix m){

	for (int y = 0; y < m.size; y++){
		printf("Column (#%d) -> ", y);
		for (int x = 0; x < m.size; x++){
			printf(" %d ", m.matrix[y][x]);
		}
		printf("\n");
	}

}


int main(int argc, char** argv){

	if (argc < 3){
		printf("Select size of matrix & amount of matrix\n");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	int matrix_size = atoi(argv[1]);
	int matrix_amount = atoi(argv[2]);

	matrix* gens = (matrix*)malloc(sizeof(matrix*)*matrix_amount);

	for (int i = 0; i < matrix_amount; i++){
		gens[i] = gen_rand_matrix(matrix_size);
		print_matrix(gens[i]);
		printf("\n\n");
	}

	return 0;
}

matrix multiply_matrix(matrix m1, matrix m2){

	// m1 and m2 have the same length

}

matrix gen_rand_matrix(int size){
	int** m = (int**) malloc(sizeof(int*)*size);

	for (int i = 0; i < size; i++){
		 m[i] = (int*)malloc(sizeof(int)*size);
		 for (int j = 0; j < size; j++){
		 	m[i][j] = rand() % 100;
		 }
	}

	matrix matrix_struct;
	matrix_struct.matrix = m;
	matrix_struct.size = size;

	return matrix_struct;

}	