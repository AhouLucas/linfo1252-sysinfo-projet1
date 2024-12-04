#include "../include/sem_tas.h"
#include "stdio.h"

void sem_tas_init(sem_tas_t* sem, int value) {
    sem->value = value;
    sem->mutex_tas = malloc(sizeof(Mutex_t));
    *(sem->mutex_tas) = 0;
}

void sem_tas_destroy(sem_tas_t* sem) {
    free(sem->mutex_tas);
}

void sem_tas_wait(sem_tas_t* sem) {
    lock_TAS(sem->mutex_tas);
    int tmp = sem->value;
    unlock_TAS(sem->mutex_tas);

    while (tmp == 0) {
        lock_TAS(sem->mutex_tas);
        tmp = sem->value;
        unlock_TAS(sem->mutex_tas);
    }

    lock_TAS(sem->mutex_tas);
    sem->value--;
    unlock_TAS(sem->mutex_tas);
}

void sem_tas_post(sem_tas_t* sem) {
    lock_TAS(sem->mutex_tas);
    sem->value++;
    unlock_TAS(sem->mutex_tas);
}