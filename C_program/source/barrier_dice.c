/**
 * 
*/
#include <stdio.h>
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
                printf("Error, diceBarrier, in thread id '%ld'\n", (unsigned long)pthread_self());
                return NULL;
        }
        //printf("Thread id '%ld' dice barrier over\n", syscall(SYS_gettid));
        ret = pthread_barrier_wait(&decisionBarrier);
        if(ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
                printf("Error, decisionBarrier, in thread id '%ld'\n", (unsigned long)pthread_self());
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