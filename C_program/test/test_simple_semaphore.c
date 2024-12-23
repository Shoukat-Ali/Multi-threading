/**
 * Testing simple semaphore program on Ubuntu using pthread (POSIX threads) and semaphore.
 * The program demonstrates the use of semaphores to control access to a shared resource 
 * in a multi-threaded environment. It simulates a login system where a limited number of users 
 * can log in simultaneously, represented by threads.
 * 
 * Some of the applications could be;
 *      Limiting concurrent user access to a server
 *      Systems with limited capacity (e.g., parking lots, database connections)
 *  
 * gcc -Wall -Werror -g3 -O3 ../source/simple_semaphore.c test_simple_semaphore.c -o prog
*/

#include <stdio.h>
#include <stdlib.h>
#include "../header/simple_semaphore.h"



sem_t semUser; // Definition

/**
 * 
 */
int main()
{
    int i;
    pthread_t thrd[NUM_THREAD];
    int my_queue[NUM_THREAD];
    
    /**
     * int sem_init(sem_t *sem, int pshared, unsigned int value);
     * 
     * sem_init() initializes the unnamed semaphore at the address pointed to by sem.
     * The value argument specifies the initial value for the semaphore.
     * The maximum value of the semaphore is set to SEM_VALUE_MAX.
     * The pshared argument indicates whether this semaphore is to be shared 
     * between the threads of a process, or between processes.
     * If pshared has the value 0, then the semaphore is shared between the threads of 
     * a process, and should be located at some address that is visible to all threads 
     * (e.g., a global variable, or a variable allocated dynamically on the heap).
     * 
     * If pshared is nonzero, then the semaphore is shared between processes, 
     * and should be located in a region of shared memory.
     * 
     * Initializing a semaphore that has already been initialized results in undefined behavior.
     * 
     * sem_init() returns 0 on success; on error, -1 is returned, 
     * and errno is set to indicate the error.
     * 
     *  */ 
    if(sem_init(&semUser, 0, SEMAPHORE_LIMIT)) {
        perror("Error, semaphore initialization failed");
        return ERR_SEMAPHORE_INIT;
    }
    
    for (i = 0; i < NUM_THREAD; i++) {
        my_queue[i] = i;
        if (pthread_create(thrd + i, NULL, my_thrd, &my_queue[i])) {
            perror("Error, thread creation failed");
            // Attempt to destroy initialized semaphore
            clean_up();
            return ERR_THRD_CREATE;
        }
    }

    for (i = 0; i < NUM_THREAD; i++) {
        if (pthread_join(thrd[i], NULL)) {
            perror("Error, thread joining failed");
            // Attempt to destroy initialized semaphore
            clean_up();
            return ERR_THRD_JOIN;
        }
    }

    // Attempt to destroy initialized semaphore 
    clean_up();
    return 0;
}