#include "../include/test_and_test_and_set.h"

void lock_TATAS(Mutex_t *mutex) {
    do {
        while (*mutex == 1);
    } while (test_and_set(mutex) == 1);
}


void unlock_TATAS(Mutex_t *mutex) {
    int new_value = 0;

    // %0 = new_value
    // %1 = *mutex
    asm volatile (
        "xchg %0, %1"
        : "=r" (new_value), "=m" (*mutex)
        : "0" (new_value), "m" (*mutex)
        : "memory"
    );
}