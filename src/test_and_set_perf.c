#include "../include/test_and_set.h"
#include "stdbool.h"
#include "getopt.h"
#include "stdio.h"
#include "pthread.h"

#define NUM_ITERATIONS 32768

Mutex_t mutex = 0;

void thread_func(void* arg) {
    int N = *((int*) arg);
    for (int i = 0; i < NUM_ITERATIONS/N; i++) {
        lock_TAS(&mutex);
        // Critical section
        for (int i = 0; i < 10000; i++); // Simulate a slow operation
        unlock_TAS(&mutex);
    }
}


int main(int argc, char** argv) {
    // Parse command line option
    int opt;
    int N = 1;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                N = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -p number -c number\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    pthread_t threads[N];

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, (void*) thread_func, (void*) &N);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;

}