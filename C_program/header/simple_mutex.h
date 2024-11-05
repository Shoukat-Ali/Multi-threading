/**
 * 
*/

#ifndef SIMPLE_MUTEX_H
#define SIMPLE_MUTEX_H

#include <pthread.h>

#define ERR_THRD_CREATE 1
#define ERR_THRD_JOIN 2

extern int shared;
extern pthread_mutex_t lock;

/**
 * 
*/
void* simple_thread();

#endif