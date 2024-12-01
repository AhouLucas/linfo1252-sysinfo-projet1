#pragma once

#include "stdlib.h"

typedef int Mutex_t;

int test_and_set(Mutex_t *mutex);
void lock_TAS(Mutex_t *mutex);
void unlock_TAS(Mutex_t *mutex);