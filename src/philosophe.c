#include "stdio.h" 
#include "stdlib.h"
#include "unistd.h"
#include "getopt.h"
#include "pthread.h"


#define NUM_CYCLES 1000000

typedef struct {
    int N;
    int id;
    pthread_mutex_t* baguette;
} params_t;

void* philosophe(void* arg) {
    // Cast arg into int pointer then dereference it
    params_t* params = (params_t*) arg;
    int N = params->N;
    int id = params->id;
    int left = id;
    int right = (left+1) % N;

    pthread_mutex_t* baguette = params->baguette;

    for (int i = 0; i < NUM_CYCLES; i++) {
        if(left<right) {
            pthread_mutex_lock(&baguette[left]);
            pthread_mutex_lock(&baguette[right]);

        }
        else {
            pthread_mutex_lock(&baguette[right]);
            pthread_mutex_lock(&baguette[left]);
        }
        pthread_mutex_unlock(&baguette[left]);
        pthread_mutex_unlock(&baguette[right]);
    }

    return NULL;
}

int main(int argc, char **argv) {
    
    // Parse command line option
    int opt;
    int N = 1;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
        case 'n':
            N = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s -n number\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    pthread_t threads[N];
    params_t args[N];
    int err;
    pthread_mutex_t* baguette = malloc(sizeof(pthread_mutex_t)*N);

    for (int i = 0; i < N; i++) {
        // Initialize mutex
        err = pthread_mutex_init(&baguette[i], NULL);
        if (err != 0) {
            printf("Error while initializing mutex [%d]\n", i);
            free(baguette);
            exit(EXIT_FAILURE);
        }
    }


    for (int i = 0; i < N; i++) {
        args[i].N = N;
        args[i].id = i;
        args[i].baguette = baguette;


        // Create threads
        err = pthread_create(&threads[i], NULL, philosophe, (void*) &(args[i]));
        if (err != 0) {
            printf("Error while creating thread [%d]\n", i);
            free(baguette);
            exit(EXIT_FAILURE);
        }
    }


    for(int i = 0; i < N; i++) {
        
        // Join threads
        err=pthread_join(threads[i], NULL);
        if(err!=0) {
            printf("Error while joining thread [%d]\n", i);
            free(baguette);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++) {
        err = pthread_mutex_destroy(baguette+i);
        if (err != 0) {
            printf("Error while destroying mutex [%d]\n", i);
            free(baguette);
            exit(EXIT_FAILURE);
        }
    }

    free(baguette);
    return EXIT_SUCCESS;
}
