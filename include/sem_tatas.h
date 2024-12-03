#pragma once

#include "test_and_test_and_set.h"

typedef struct {
    int value;
    Mutex_t mutex_tatas;
} sem_tatas_t;


void sem_tatas_init(sem_tatas_t* sem, int value);
void sem_tatas_wait(sem_tatas_t* sem);
void sem_tatas_post(sem_tatas_t* sem);