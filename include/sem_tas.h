#pragma once

#include "test_and_set.h"

typedef struct {
    volatile int value;
    Mutex_t* mutex_tas;
} sem_tas_t;

void sem_tas_init(sem_tas_t* sem, int value);
void sem_tas_destroy(sem_tas_t* sem);
void sem_tas_wait(sem_tas_t* sem);
void sem_tas_post(sem_tas_t* sem);