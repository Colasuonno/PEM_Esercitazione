#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int total_tosses = 0;
int total_in_circle = 0;

int launch_for_thread = 0;

pthread_mutex_t* glb_mutex;

void* launch_dart(void* rank_ptr){
    // unsafe
    long rank = (long)rank_ptr;
    
    // prendo dei numeri random da -1 e 1 (x,y)
	// se le coordinate x^2 + y^2 = 1 allora (x,y) sono nel cerchio

    int local_circles = 0;

    for (int launch = 0; launch < launch_for_thread; launch++){
        double rand_x = (rand() / (double)RAND_MAX) * 2.0 - 1;
        double rand_y = (rand() / (double)RAND_MAX) * 2.0 - 1;


        if (rand_x*rand_x + rand_y*rand_y <= 1.0){
            local_circles += 1;
        }
    }

    printf("Thread %d have %d circles\n", rank, local_circles);

    pthread_mutex_lock(glb_mutex);
    total_tosses += launch_for_thread;
    total_in_circle += local_circles;
    pthread_mutex_unlock(glb_mutex);


    return NULL;
}


int main(int argc, char** argv){

    srand(time(NULL));

    int thread_amount = 4;
    int total_launch = 10000000;

    launch_for_thread = total_launch / thread_amount;

    printf("AO\n");
    glb_mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(glb_mutex, NULL);
    
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t)*thread_amount);

    for (int i = 0; i < thread_amount; i++){
        pthread_create(
            &threads[i],
            NULL,
            launch_dart,
            (void*)(long)i
        );
    }

    printf("Threads created\n");

    for (int i = 0; i < thread_amount; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(glb_mutex);

    free(threads);
    free(glb_mutex);
    

    printf("End, so PI is %lf\n", (4.0*(double)total_in_circle)/(double)total_tosses);

    return 0;

}