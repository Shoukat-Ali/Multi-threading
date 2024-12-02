/**
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include "../header/barrier_dice.h"

#define DICE_LIMIT 6

/**
 * 
 */
void* roll_dice(void* indx)
{
    int index = *(int*) indx;
    int ret;
    
    while (1) {
        // diceValue[] is shared globally
        diceValue[index] = (rand() % DICE_LIMIT) + 1;
        printf("Thread id '%ld' rolled %d\n", (unsigned long)pthread_self(), diceValue[index]);

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
        //printf("Thread id '%ld' dice barrier over\n", syscall(SYS_gettid));
        ret = pthread_barrier_wait(&decisionBarrier);
        if(ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
                printf("Error, decisionBarrier wait in thread id '%ld'\n", (unsigned long)pthread_self());
                return NULL;
        }
        //printf("Thread id '%ld' decision barrier over\n", syscall(SYS_gettid));
        // winnerStatus[] is shared globally
        if (winnerStatus[index] == 1) 
            printf("Winner, Thread id '%ld' rolled %d\n", (unsigned long)pthread_self(), diceValue[index]);
        else
            printf("Loser, Thread id '%ld' rolled %d\n", (unsigned long)pthread_self(), diceValue[index]);
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
}