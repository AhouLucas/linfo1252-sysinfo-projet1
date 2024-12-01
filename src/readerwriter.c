#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"
#include "getopt.h"

#define NUM_WRITE 640
#define NUM_READ 2540

sem_t db;   // Protects access to the database
pthread_mutex_t mutex;  // Protects access to the readercount
int readercount = 0;

int count_write = 0; // Number of writes done so far
int count_read = 0; // Number of reads done so far

void writer(void) {
    while(true) {
        sem_wait(&db);
        // section critique
        if (count_write >= NUM_WRITE) {
            sem_post(&db);
            break;
        }
        count_write++;

        for (int i=0; i<10000; i++); // Simulate a slow writer
        sem_post(&db);
    }
}

void reader(void) {
    while(true) {
        pthread_mutex_lock(&mutex);
        if (count_read >= NUM_READ) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        count_read++;

        readercount++;
        if (readercount == 1) {
            sem_wait(&db);
        }

        for (int i=0; i<10000; i++); // Simulate a slow reader
        pthread_mutex_unlock(&mutex);


        pthread_mutex_lock(&mutex);
        readercount--;
        if (readercount == 0) {
            sem_post(&db);
        }
        pthread_mutex_unlock(&mutex);
    }
}


int main(int argc, char **argv) {

    // Parse command line option
    int opt;
    int n_writer = 1;
    int n_reader = 1;
    while ((opt = getopt(argc, argv, "w:r:")) != -1) {
        switch (opt) {
        case 'w':
            n_writer = atoi(optarg);
            break;
        case 'r':
            n_reader = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s -w number -r number\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    pthread_t threads[n_writer+n_reader];
    int err;

    sem_init(&db, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < n_writer; i++) {
        err = pthread_create(&threads[i], NULL, (void*) writer, NULL);
        if (err != 0) {
            fprintf(stderr, "Error creating writer thread\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = n_writer; i < n_writer+n_reader; i++) {
        err = pthread_create(&threads[i], NULL, (void*) reader, NULL);
        if (err != 0) {
            fprintf(stderr, "Error creating reader thread\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n_writer+n_reader; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&db);
    pthread_mutex_destroy(&mutex);

    return 0;
}
