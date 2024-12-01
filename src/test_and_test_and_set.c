#include "../include/test_and_test_and_set.h"

void lock_TATAS(Mutex_t *mutex) {
    do {
        while (*mutex == 1);
    } while (test_and_set(mutex) == 1);
}

void unlock_TATAS(Mutex_t *mutex) {
    *mutex = 0;
}