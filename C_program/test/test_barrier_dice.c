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
int diceValue[NUM_THREAD] = {0};        // Definition: Storing the result of each dice roll by a thread
int winnerStatus[NUM_THREAD] = {0};     // Definition: 1 is winner, 0 is losser
pthread_mutex_t mLock;                   // Definition: To lock shared resource(s)


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
    int max, ret = 0;
    srand(time(NULL));
    int count = 0;
    
    // Initializing required resources
    if((ret = initialize())) {
        printf("Error, initialization failed with error number: %i\n", ret);
        return ret;
    }

    // Creating threads
    for(i = 0; i < NUM_THREAD; ++i) {
        // Memory allocation on heap
        indx[i] = malloc(sizeof(*(indx[i])));
        *(indx[i]) = i;
        if (pthread_create(thrd + i, NULL, roll_dice, indx[i])) {
            perror("Error, thread creation failed");
            deallocate_mem(i + 1);
            // Attempt to clean up resources by destroying barriers
            clean_up();
            return ERR_THRD_CREATE;
        }
    }

    while (count < NUM_ROUNDS) {
        count++;
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
        // Attempt to obtain lock
        if(pthread_mutex_lock(&mLock)) {
            perror("Error, failed to lock mutex mLock");
            deallocate_mem(NUM_THREAD);
            // Attempt to clean up resources by destroying barriers
            clean_up();
            return ERR_MUTEX_LOCK;
        }
        for (i = 0; i < NUM_THREAD; ++i) {
            if (diceValue[i] > max) {
                max = diceValue[i];
            }
        }

        // Setting the winner(s) using winnerStatus
        for (i = 0; i < NUM_THREAD; i++) {
            winnerStatus[i] = (diceValue[i] == max) ? 1 : 0;
        }
        //Attempt to release the lock
        if(pthread_mutex_unlock(&mLock)) {
            perror("Error, failed to unlock mutex mLock");
            deallocate_mem(NUM_THREAD);
            // Attempt to clean up resources by destroying barriers
            clean_up();
            return ERR_MUTEX_UNLOCK;
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