/**
 * Testing multi-threading dice rolling program using barrier on Ubuntu using pthread library.
 *  
 * gcc -Wall -Werror -g3 -O3 ../source/barrier_dice.c test_barrier_dice.c -o prog
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../header/barrier_dice.h"



static int *indx[NUM_THREAD] = {NULL};  // Array of pointers
int diceValue[NUM_THREAD];              // Definition: Storing the result of each dice roll by a thread
int winnerStatus[NUM_THREAD] = {0};     // Definition: 1 is winner, 0 is losser

pthread_barrier_t diceBarrier;          // Definition: barrier for rolling dice
pthread_barrier_t decisionBarrier;      // Definition: barrier for deciding winner(s)


/**
 * The function attempts to deallocate the memory
 */
void deallocate_mem(int bound) 
{
    for(int i = 0; i < bound; i++) {
        free(indx[i]);
        indx[i] = NULL;
    }
}


int main()
{
    pthread_t thrd[NUM_THREAD];
    int i;
    int max, ret;
    srand(time(NULL));
    
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

    // Creating threads
    for(i = 0; i < NUM_THREAD; ++i) {
        // Memory allocation on heap
        indx[i] = malloc(sizeof(*(indx[i])));
        *(indx[i]) = i;
        if (pthread_create(thrd + i, NULL, &roll_dice, (void*) indx[i])) {
            perror("Error, thread creation failed");
            deallocate_mem(i + 1);
            // Attempt to clean up resources by destroying barriers
            clean_up();
            return ERR_THRD_CREATE;
        }
    }

    while (1) {
        //printf("Main thread waiting for dice barrier\n");
        /**
         * block until the required number of threads have called pthread_barrier_wait()
         * Note, invoke pthread_barrier_wait() once on a barrier and safe return value
         * 
         */
        ret = pthread_barrier_wait(&diceBarrier);
        if(ret != 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
                perror("Error, dice barrier wait failed");
                deallocate_mem(NUM_THREAD);
                // Attempt to clean up resources by destroying barriers
                clean_up();
                return ERR_BARRIER_WAIT;
            } 
        
        // Deciding the winner(s) by max value
        max = 0;
        for (i = 0; i < NUM_THREAD; ++i) {
            if (diceValue[i] > max) {
                max = diceValue[i];
            }
        }

        // Setting the winner(s) using winnerStatus
        for (i = 0; i < NUM_THREAD; i++) {
            winnerStatus[i] = (diceValue[i] == max) ? 1 : 0;
        }

        //puts("Main thread sleeps after dice barrier\n");
        if(usleep(999999)) {
            perror("Error, usleep() failed");
        }
        puts("****** Starting new round ******\n");
        //puts("Main thread waiting for decision barrier\n");
        ret = pthread_barrier_wait(&decisionBarrier);
        if(ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
                perror("Error, decision barrier wait failed");
                deallocate_mem(NUM_THREAD);
                // Attempt to clean up resources by destroying barriers
                clean_up();
                return ERR_BARRIER_WAIT;
        }
    }
    
    // Waiting for other threads to terminate
    for (i = 0; i < NUM_THREAD; ++i) {
        if (pthread_join(thrd[i], NULL)) {
            perror("Error, thread termination failed");
            deallocate_mem(NUM_THREAD);
            // Attempt to clean up resources by destroying barriers
            clean_up();
            return ERR_THRD_JOIN;
        }
    }

    deallocate_mem(NUM_THREAD);
    // Attempt to clean up resources by destroying barriers
    clean_up();
    
    return 0;
}