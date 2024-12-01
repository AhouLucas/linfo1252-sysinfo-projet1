#pragma once

#include "stdlib.h"
#include "test_and_set.h"

void lock_TATAS(Mutex_t *mutex);
void unlock_TATAS(Mutex_t *mutex);