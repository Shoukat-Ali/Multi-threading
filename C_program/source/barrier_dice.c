/**
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/barrier_dice.h"


/**
 * 
 * On success, returns 0; otherwise an error number (non-zero integers) is returned.
 * 
 */
int initialize() 
{
    // Initializing barriers
    // For threads count, main plus other threads
    /**
     * int pthread_barrier_init(pthread_barrier_t *restrict barrier,
                                const pthread_barrierattr_t *restrict attr, 
                                unsigned count); 
     * 
     * The pthread_barrier_init() function shall allocate any resources required 
     * to use the barrier referenced by barrier and shall initialize the barrier 
     * with attributes referenced by attr. If attr is NULL, the default barrier 
     * attributes shall be used; the effect is the same as passing the address 
     * of a default barrier attributes object. The results are undefined 
     * if pthread_barrier_init() is called when any thread is blocked on the barrier 
     * (that is, has not returned from the pthread_barrier_wait() call). 
     * The results are undefined if a barrier is used without first being initialized. 
     * The results are undefined if pthread_barrier_init() is called specifying an 
     * already initialized barrier. The count argument specifies the number of threads 
     * that must call pthread_barrier_wait() before any of them successfully return from the call. 
     * The value specified by count must be greater than zero. 
     * 
     * If the pthread_barrier_init() function fails, the barrier shall not be initialized 
     * and the contents of barrier are undefined.
     * 
     * On successful completion, the function returns zero; 
     * otherwise, an error number is returned to indicate the error.  
     * 
     */
    if(pthread_barrier_init(&diceBarrier, NULL, NUM_THREAD + 1)) {
        perror("Error, failed to initialize diceBarrier");
        return ERR_BARRIER_INIT;
    }
    // Initializing decision barrier
    if(pthread_barrier_init(&decisionBarrier, NULL, NUM_THREAD + 1)) {
        perror("Error, failed to initialize decisionBarrier");
        // Attempt to destroy the diceBarrier while ignoring the return value
        pthread_barrier_destroy(&diceBarrier); 
        return ERR_BARRIER_INIT;
    }

    // Initializing the mutex to lock shared resources
    if(pthread_mutex_init(&mLock, NULL)) {
        // Mutex initialization failed
        perror("Error, failed to initialize the mutex mLock");
        // Attempt to destroy the diceBarrier while ignoring the return value
        pthread_barrier_destroy(&diceBarrier);
        // Attempt to destroy the decisionBarrier while ignoring the return value
        pthread_barrier_destroy(&decisionBarrier);
        return ERR_MUTEX_INIT;
    }
    return 0;
}


/**
 * 
 */
void* roll_dice(void* indx)
{
    int ret, index = 0;
    // int count = 0;

    // Checking if void* is null
    if (!indx) {
        printf("Error, Null pointer passed to thread id '%ld'\n", (unsigned long)pthread_self());
        return NULL;
    }

    // Casting indx to integer pointer and de-referencing to display the content
    index = *(int*) indx;
    // Validating the array index
    if (index < 0 || index >= NUM_THREAD) {
        printf("Error, invalid array index to thread id '%ld'\n", (unsigned long)pthread_self());
        return NULL;
    }
    
    // while (count < NUM_ROUNDS) {
    //     count++;
    while (1) {
        // diceValue[] is shared globally, therefore, locking
        if(pthread_mutex_lock(&mLock)) {
            perror("Error, failed to lock mutex mLock");
            return NULL;
        }
        diceValue[index] = (rand() % DICE_LIMIT) + 1;
        printf("Thread id '%ld' rolled %d\n", (unsigned long)pthread_self(), diceValue[index]);
        if (pthread_mutex_unlock(&mLock)) {
            perror("Error, failed to unlock mutex mLock");
            return NULL;
        }

        /**
         * int pthread_barrier_wait(pthread_barrier_t *barrier);
         * 
         * The pthread_barrier_wait() function shall synchronize participating threads 
         * at the barrier referenced by barrier. The calling thread shall block until 
         * the required number of threads have called pthread_barrier_wait() specifying 
         * the barrier. When the required number of threads have called
         * pthread_barrier_wait() specifying the barrier, the constant
         * PTHREAD_BARRIER_SERIAL_THREAD shall be returned to one unspecified thread 
         * and zero shall be returned to each of the remaining threads. At this point, 
         * the barrier shall be reset to the state it had as a result of the most recent
         * pthread_barrier_init() function that referenced it.
         * 
         * The constant PTHREAD_BARRIER_SERIAL_THREAD is defined in <pthread.h> and 
         * its value shall be distinct from any other value returned by pthread_barrier_wait().
         * 
         * The results are undefined if this function is called with an uninitialized barrier.
         * 
         * Upon successful completion, the pthread_barrier_wait() function shall return 
         * PTHREAD_BARRIER_SERIAL_THREAD for a single (arbitrary) thread synchronized 
         * at the barrier and zero for each of the other threads. Otherwise, an error number 
         * shall be returned to indicate the error.
         */
        ret = pthread_barrier_wait(&diceBarrier);
        if(ret != 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
                printf("Error, diceBarrier wait in thread id '%ld'\n", (unsigned long)pthread_self());
                return NULL;
        }
        
        ret = pthread_barrier_wait(&decisionBarrier);
        if(ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
                printf("Error, decisionBarrier wait in thread id '%ld'\n", (unsigned long)pthread_self());
                return NULL;
        }
        
        // winnerStatus[] is shared globally, therefore, locking
        if(pthread_mutex_lock(&mLock)) {
            perror("Error, failed to lock mutex mLock");
            return NULL;
        }
        if (winnerStatus[index] == 1) 
            printf("Winner, Thread id '%ld' rolled %d\n", (unsigned long)pthread_self(), diceValue[index]);
        else
            printf("Loser, Thread id '%ld' rolled %d\n", (unsigned long)pthread_self(), diceValue[index]);
        if (pthread_mutex_unlock(&mLock)) {
            perror("Error, failed to unlock mutex mLock");
            return NULL;
        }
        // Part of testing to cause a thread to sleep
        // if(usleep(999999)) {
        //     perror("Error, usleep() failed");
        // }
    }
    return NULL;
}




/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up()
{
    /**
     * int pthread_barrier_destroy(pthread_barrier_t *barrier);
     * 
     * The pthread_barrier_destroy() function shall destroy the barrier 
     * referenced by barrier and release any resources used by the barrier. 
     * The effect of subsequent use of the barrier is undefined until 
     * the barrier is reinitialized by another call to pthread_barrier_init(). 
     * An implementation may use this function to set barrier to an invalid value. 
     * The results are undefined if pthread_barrier_destroy() is called 
     * when any thread is blocked on the barrier, or if this function is called 
     * with an uninitialized barrier.
     * 
     * On successful completion, the function returns zero; 
     * otherwise, an error number is returned to indicate the error.
     */
    if(pthread_barrier_destroy(&diceBarrier)) {
        perror("Error, failed to destroy diceBarrier");
    }

    if(pthread_barrier_destroy(&decisionBarrier)) {
        perror("Error, failed to destory decisionBarrier");
    }

    if(pthread_mutex_destroy(&mLock)) {
        // Destroying mutex caused an error
        perror("Error, failed to destroy mutex");
    }
}