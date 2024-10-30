#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double pi = 1;
pthread_mutex_t* mutex;

void* contribute(void* rank_ptr){

	int rank = *((int*)rank_ptr);
	free(rank_ptr);

	pthread_mutex_lock(mutex);
	pi += pow(-1, rank) * ((1.0) / (2.0*rank+1));
	pthread_mutex_unlock(mutex);
	return NULL;
}


int main(int argc, char** argv){

	if (argc < 2){
		printf("Select thread size\n");
		exit(EXIT_FAILURE);
	}

	mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t*));
	int thread_count = atoi(argv[1]);

	pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);

	pthread_mutex_init(mutex, NULL);

	for (int i = 0; i < thread_count; i++){
		int* rank = (int*)malloc(sizeof(int)); // Alloca memoria per il rank
        *rank = i+1; 
		int a = pthread_create(
				&threads[i],
				NULL,
				contribute,
				rank
			);
	}

	for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("PI %lf\n", 4*(pi));
}