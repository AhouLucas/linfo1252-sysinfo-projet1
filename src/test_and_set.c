#include "../include/test_and_set.h"

int test_and_set(Mutex_t *mutex) {
    int new_value = 1;

    // %0 = new_value
    // %1 = *mutex
    asm volatile (
        "xchg %0, %1"
        : "=r" (new_value), "=m" (*mutex)
        : "0" (new_value), "m" (*mutex)
    );

    return new_value;
}

void lock_TAS(Mutex_t *mutex) {
    while (test_and_set(mutex) == 1);
}

void unlock_TAS(Mutex_t *mutex) {
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