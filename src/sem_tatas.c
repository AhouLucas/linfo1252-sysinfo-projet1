#include "../include/sem_tatas.h"

void sem_tatas_init(sem_tatas_t* sem, int value) {
    sem->value = value;
    sem->mutex_tatas = malloc(sizeof(Mutex_t));
    *(sem->mutex_tatas) = 0;
}

void sem_tatas_destroy(sem_tatas_t* sem) {
    free(sem->mutex_tatas);
}

void sem_tatas_wait(sem_tatas_t* sem) {
    lock_TATAS(sem->mutex_tatas);
    int tmp = sem->value;
    unlock_TATAS(sem->mutex_tatas);

    while (tmp == 0) {
        lock_TATAS(sem->mutex_tatas);
        tmp = sem->value;
        unlock_TATAS(sem->mutex_tatas);
    }

    lock_TATAS(sem->mutex_tatas);
    sem->value--;
    unlock_TATAS(sem->mutex_tatas);
}

void sem_tatas_post(sem_tatas_t* sem) {
    lock_TATAS(sem->mutex_tatas);
    sem->value++;
    unlock_TATAS(sem->mutex_tatas);
}