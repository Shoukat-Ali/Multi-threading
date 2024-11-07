/**
 * 
*/

#ifndef CHEF_STOVE_H
#define CHEF_STOVE_H

#include <pthread.h>

#define ERR_THRD_CREATE 1
#define ERR_THRD_JOIN 2
#define ERR_MUTEX_INIT 3
#define ERR_MUTEX_DESTORY 4

#define SHARED_RESOURCES 5


// Allusion for global shared resource/data
extern pthread_mutex_t stove_mutex[];
extern int stove_fuel[];

/**
 * 
*/
void* chef_stove_thread();

#endif