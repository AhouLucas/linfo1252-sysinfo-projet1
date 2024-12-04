#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "pthread.h"
#include "../include/test_and_set.h"
#include "../include/sem_tas.h"
#include "unistd.h"
#include "getopt.h"

#define BUFFER_SIZE 8
#define NUM_ITEMS 131072

int buffer[BUFFER_SIZE];
int in = 0;   // Index for producer
int out = 0;  // Index for consumer
int count_produced = 0;
int count_consumed = 0;

sem_tas_t empty;  // Tracks empty slots in the buffer
sem_tas_t full;   // Tracks filled slots in the buffer
Mutex_t mutex;  // Protects access to the buffer

void producer(void* arg) {
    int id = *((int*) arg);
    while(true) {
        sem_tas_wait(&empty); // attente d'une place libre
        lock_TAS(&mutex);

        // section critique
        if (count_produced >= NUM_ITEMS) {
            unlock_TAS(&mutex);
            sem_tas_post(&full);
            break;
        }
        buffer[in] = id;
        count_produced++;
        in = (in + 1) % BUFFER_SIZE;

        unlock_TAS(&mutex);
        for (int i=0; i<10000; i++); // Simulate a slow producer
        sem_tas_post(&full); // il y a une place remplie en plus
    }
}

void consumer(void) {
    while(true) {
        sem_tas_wait(&full); // attente d'une place remplie
        lock_TAS(&mutex);

        // section critique
        if (count_consumed >= NUM_ITEMS) {
            unlock_TAS(&mutex);
            sem_tas_post(&empty);
            break;
        }
        // printf("%d\n", buffer[out]);
        count_consumed++;
        out = (out + 1) % BUFFER_SIZE;
        
        unlock_TAS(&mutex);
        for (int i=0; i<10000; i++); // Simulate a slow producer
        sem_tas_post(&empty); // il y a une place libre en plus
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

    sem_tas_init(&empty, BUFFER_SIZE);  // buffer vide
    sem_tas_init(&full, 0);   // buffer vide
    mutex = 0;

    pthread_t prod[N_prod];
    pthread_t cons[N_cons];
    int id[N_prod];

    int err = 0;

    for (int i = 0; i < N_prod; i++) {
        id[i] = i;
        err = pthread_create(&prod[i], NULL, (void*) producer, (void*) &id[i]);

        if (err != 0) {
            printf("Error while creating producer thread [%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N_cons; i++) {
        err = pthread_create(&cons[i], NULL, (void*) consumer, NULL);

        if (err != 0) {
            printf("Error while creating consumer thread [%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N_prod; i++) {
        pthread_join(prod[i], NULL);
    }

    for (int i = 0; i < N_cons; i++) {
        pthread_join(cons[i], NULL);
    }

    sem_tas_destroy(&empty);
    sem_tas_destroy(&full);

    return 0;
}