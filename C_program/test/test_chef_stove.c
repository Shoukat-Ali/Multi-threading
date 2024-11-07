/**
 * Chef and stove multi-threading program that uses mutex
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
        if(pthread_create(thrd + i, NULL, &chef_stove_thread, NULL)) {
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