/**
 * Testing a simple multi-threading (joinable threads) program that uses mutex on Ubuntu 
 * using pthread library (POSIX threads). The example demonstrates a multithreaded increment operation 
 * on a shared variable with synchronization using a mutex lock to avoid race conditions.
 * 
 * A mutex is a mutual exclusion lock. Only one thread can hold the lock.
 * Mutexes are used to protect data or other resources from concurrent access. 
 * A mutex has attributes, which specify the characteristics of the mutex. 
 * 
 * gcc -Wall -Werror -g3 -O3 ../source/simple_mutex.c test_simple_mutex.c -o prog 
*/

#include <stdio.h>
#include <pthread.h>
#include "../header/simple_mutex.h"

#define NUM_THREADS 7

int shared = 0;
pthread_mutex_t lock;


int main()
{
    pthread_t thrd[NUM_THREADS];
    int i;
    /**
     * int pthread_mutex_init(pthread_mutex_t *restrict mutex, 
     *                        const pthread_mutexattr_t *restrict attr);
     * 
     * The pthread_mutex_init() function shall initialize the mutex referenced 
     * by mutex with attributes specified by attr.  If attr is NULL, the default 
     * mutex attributes are used; the effect shall be the same as passing the 
     * address of a default mutex attributes object. Upon successful initialization, 
     * the state of the mutex becomes initialized and unlocked.
     * 
     * Attempting to initialize an already initialized mutex results in undefined behavior.
     * 
     * If successful, the pthread_mutex_init() functions shall return zero; 
     * otherwise, an error number shall be returned to indicate the error.
     * 
     */
    if(pthread_mutex_init(&lock, NULL)) {
        // Mutex initialization failed
        perror("Failed to initialize the mutex");
        return ERR_MUTEX_INIT;
    }

    // Successful mutex initialization
    for(i = 0; i < NUM_THREADS; ++i) {
        // starting a new thread within the process
        if(pthread_create(thrd + i, NULL, simple_thread, NULL)) {
            printf("Thread no. %d creation failed\n", i + 1);
            return ERR_THRD_CREATE;
        }
        //printf("Thread no. %d has started\n", i + 1);
    }
    
    for(i = 0; i < NUM_THREADS; ++i) {
        // Wait for the thread to end execution
        if(pthread_join(thrd[i] , NULL)){
            printf("Thread no. %d failed to terminate\n", i + 1);
            return ERR_THRD_JOIN;
        }
        //printf("Thread no. %d has ended\n", i + 1);
    }
    /**
     * int pthread_mutex_destroy(pthread_mutex_t *mutex);
     * 
     * The pthread_mutex_destroy() function shall destroy the mutex object 
     * referenced by mutex; the mutex object becomes, in effect, uninitialized. 
     * An implementation may cause pthread_mutex_destroy() to set the object 
     * referenced by mutex to an invalid value.
     * 
     * If successful, the pthread_mutex_destroy() functions shall return zero; 
     * otherwise, an error number shall be returned to indicate the error.
     */
    if(pthread_mutex_destroy(&lock)) {
        // Destroying mutex caused an error
        perror("Failed to destroy mutex");
        return ERR_MUTEX_DESTORY;
    }
    printf("Incrementing the same int variable by all threads: %d\n", shared);

    return 0;
}