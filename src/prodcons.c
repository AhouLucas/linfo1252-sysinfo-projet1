#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"
#include "getopt.h"

#define BUFFER_SIZE 8
#define NUM_ITEMS 131072

int buffer[BUFFER_SIZE];
int in = 0;   // Index for producer
int out = 0;  // Index for consumer
int count_produced = 0;
int count_consumed = 0;

sem_t empty;  // Tracks empty slots in the buffer
sem_t full;   // Tracks filled slots in the buffer
pthread_mutex_t mutex;  // Protects access to the buffer

void producer(void* arg) {
    int id = *((int*) arg);
    while(true) {
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);

        // section critique
        if (count_produced >= NUM_ITEMS) {
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
            break;
        }
        buffer[in] = id;
        count_produced++;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        for (int i=0; i<10000; i++); // Simulate a slow producer
        sem_post(&full); // il y a une place remplie en plus
    }
}

void consumer(void) {
    while(true) {
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);

        // section critique
        if (count_consumed >= NUM_ITEMS) {
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
            break;
        }
        // printf("%d\n", buffer[out]);
        count_consumed++;
        out = (out + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex);
        for (int i=0; i<10000; i++); // Simulate a slow producer
        sem_post(&empty); // il y a une place libre en plus
    }
}

int main(int argc, char** argv) {
    // Parse command line option
    int opt;
    int N_prod = 1;
    int N_cons = 1;
    while ((opt = getopt(argc, argv, "p:c:")) != -1) {
        switch (opt) {
            case 'p':
                N_prod = atoi(optarg);
                break;
            case 'c':
                N_cons = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -p number -c number\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    sem_init(&empty, 0 , BUFFER_SIZE);  // buffer vide
    sem_init(&full, 0 , 0);   // buffer vide
    pthread_mutex_init(&mutex, NULL);

    pthread_t prod[N_prod];
    pthread_t cons[N_cons];
    int id[N_prod];

    int err = 0;

    for (int i = 0; i < N_prod; i++) {
        id[i] = i;
        err = pthread_create(&prod[i], NULL, (void*) producer, (void*) &id[i]);

        if (err != 0) {
            printf("Error while creating producer thread [%d]\n", i);
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N_cons; i++) {
        err = pthread_create(&cons[i], NULL, (void*) consumer, NULL);

        if (err != 0) {
            printf("Error while creating consumer thread [%d]\n", i);
            sem_destroy(&empty);
            sem_destroy(&full);
            pthread_mutex_destroy(&mutex);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N_prod; i++) {
        pthread_join(prod[i], NULL);
    }

    for (int i = 0; i < N_cons; i++) {
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}