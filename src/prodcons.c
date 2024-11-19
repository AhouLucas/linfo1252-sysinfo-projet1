#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"
#include "getopt.h"

#define BUFFER_SIZE 8
#define NUM_ITEMS 131072

int buffer[BUFFER_SIZE];
int in = 0;   // Index for producer
int out = 0;  // Index for consumer

sem_t empty;  // Tracks empty slots in the buffer
sem_t full;   // Tracks filled slots in the buffer
pthread_mutex_t mutex;  // Protects access to the buffer

void* producer(void* arg) {
    int id = *((int*) arg);
    for (int i = 0; i < NUM_ITEMS; i++) {

        sem_wait(&empty);           // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Add the item to the buffer
        buffer[in] = id;
        in = (in + 1) % BUFFER_SIZE; // Move to the next index

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full);              // Signal that a new item is available

        for (int i = 0; i < 10000; i++); // Simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);            // Wait for a filled slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Simulate removing the item from the buffer
        // buffer[out] = -1 ==> unnecessary
        out = (out + 1) % BUFFER_SIZE; // Move to the next index

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty);             // Signal that a slot is now empty

        for (int i = 0; i < 10000; i++); // Simulate consumption time
    }
    return NULL;
}

int main(int argc, char **argv) {

    // Parse command line option
    int opt;
    int n_prod = 1;
    int n_cons = 1;
    while ((opt = getopt(argc, argv, "p:c:")) != -1) {
        switch (opt) {
        case 'p':
            n_prod = atoi(optarg);
            break;
        case 'c':
            n_cons = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s -n number\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    pthread_t prod_thread[n_prod], cons_thread[n_cons];
    int ids[n_prod];

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer starts with all slots empty
    sem_init(&full, 0, 0);           // No items in the buffer initially

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    for (int i = 0; i < n_prod; i++) {
        ids[i] = i;
        pthread_create(&(prod_thread[i]), NULL, producer, (void*) (&(ids[i])));
    }
    
    for (int i = 0; i < n_cons; i++) {
        pthread_create(&(cons_thread[i]), NULL, consumer, NULL);
    }

    // Wait for threads to complete
    for (int i = 0; i < n_prod; i++) {
        ids[i] = i;
        pthread_join(prod_thread[i]     , NULL);
    }
    
    for (int i = 0; i < n_cons; i++) {
        pthread_join(cons_thread[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
