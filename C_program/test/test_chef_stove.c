/**
 * Testing Chef and stove multi-threading (joinable threads) program that uses mutex on Ubuntu using pthread library.
 * 
 * gcc -Wall -Werror -g3 -O3 ../source/chef_stove.c test_chef_stove.c -o prog
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/chef_stove.h"

#define NUM_THREAD 13

// Definition of global shared resource/data
pthread_mutex_t stove_mutex[SHARED_RESOURCES];


int main()
{
    int i;
    pthread_t thrd[NUM_THREAD];
    /**
     * time_t time(time_t *_Nullable tloc);
     * 
     * time() returns the time as the number of seconds since the Epoch,
     * 1970-01-01 00:00:00 +0000 (UTC).
     * The tloc argument is obsolescent and should always be NULL in new code. 
     * When tloc is NULL, the call cannot fail.
     * 
     * void srand(unsigned seed);
     * 
     * The srand() function uses the argument as a seed for a new sequence 
     * of pseudo-random numbers to be returned by subsequent calls to rand(). 
     * If srand() is then called with the same seed value, the sequence of 
     * pseudo-random numbers shall be repeated.
     * 
     * 
     * Note that srand() is not a cyrptographic pseudo-random numbers generator
     */
    srand(time(NULL));

    // Initializing all the mutexes
    for(i = 0; i < SHARED_RESOURCES; ++i) {
        if(pthread_mutex_init(&stove_mutex[i], NULL)) {
            // Mutex initialization failed
            perror("Failed to initialize the stove mutex");
            return ERR_MUTEX_INIT;
        }
    }
    // Creating threads
    for(i = 0; i < NUM_THREAD; ++i) {
        if(pthread_create(thrd + i, NULL, chef_stove_thread, NULL)) {
            perror("Failed to create a thread");
            return ERR_THRD_CREATE;
        }
    }
    // Main process waiting for the termination of other threads
    for(i = 0; i < NUM_THREAD; ++i) {
        if(pthread_join(thrd[i], NULL)) {
            perror("Thread termination failed");
            return ERR_THRD_JOIN;
        }
    }

    // Destroying all the mutexex
    for(i = 0; i < SHARED_RESOURCES; ++i) {
        if(pthread_mutex_destroy(&stove_mutex[i])) {
            // Destroying mutex caused an error
            perror("Failed to destory the stove mutex");
            return ERR_MUTEX_DESTORY;
        }
    }
    return 0;
}