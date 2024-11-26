/**
 * 
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../header/broadcast_prod_cosm.h"



int food = 0;   // Global variable
pthread_mutex_t food_mutex;     // Lock for updating shared food variable
pthread_cond_t food_cond;   // mutex conditional variable


/**
 * Thread for producing food i.e., increating the value of food variable
*/
void* producer()
{
    int i;
    for(i = 0; i < ROUND; ++i) {
        if(pthread_mutex_lock(&food_mutex)) {
            perror("Error, producer thread failed to obtain food mutex");
            continue;
        }
        food += PRODUCTION;
        printf("Total food production:: %d  (thread id: %lu)\n", food, (unsigned long)pthread_self());
        if(pthread_mutex_unlock(&food_mutex)) {
            perror("Error, producer thread failed to release food mutex");
            // return NULL;
        }
        /**
         * int pthread_cond_broadcast(pthread_cond_t *cond);
         * 
         * The pthread_cond_broadcast() function shall unblock all threads currently 
         * blocked on the specified condition variable cond.
         * If more than one thread is blocked on a condition variable, the scheduling 
         * policy shall determine the order in which threads are unblocked.
         * The pthread_cond_broadcast() function may be called by a thread whether or not 
         * it currently owns the mutex that threads calling pthread_cond_wait() or 
         * pthread_cond_timedwait() have associated with the condition variable during their waits; 
         * however, if predictable scheduling behavior is required, then that mutex shall be locked 
         * by the thread calling pthread_cond_broadcast().
         * The pthread_cond_broadcast() shall have no effect if there are no threads currently blocked on cond.
         * 
         * If successful, the function returns zero; otherwise, an error number is returned to indicate the error. 
         *  
         *  */ 
        if(pthread_cond_broadcast(&food_cond)) {
            perror("Error, producer thread failed to broadcast signal food conditional variable");
            // return NULL;
        }
        // Let take a break before producing more food
        // Sleep for 700 ms or 0.7-sec
        if(usleep(700000)) {
            perror("Failed, usleep()");
        }
    }
    printf("Ending:: Producer thread id: %lu\n", (unsigned long)pthread_self());
    return NULL;
}


/**
 * Thread for consuming food if more than some threshold  
*/
void* consumer()
{
    if(pthread_mutex_lock(&food_mutex)) {
        perror("Consumer thread failed to obtain food mutex");
        return NULL;
    }
    while(food < FOOD_THRESHOLD) {
        printf("Not enough food to consume (thread id: %lu)\n", (unsigned long)pthread_self());
        pthread_cond_wait(&food_cond, &food_mutex);
    }
    food -= CONSUMPTION;
    printf("After consumption we have: %d food\n", food);
    if(pthread_mutex_unlock(&food_mutex)) {
        perror("Consumer thread failed to release food mutex");
        return NULL;
    }
    printf("Ending:: Consumer thread id: %lu\n", (unsigned long)pthread_self());
    return NULL;
}


/**
 * The functions attempts to clean-up the utilized resources.
 * If the clean-up was not successful, then the error is reported
 * 
 */
void clean_up()
{
    if(pthread_cond_destroy(&food_cond)) {
        // Destroying conditional variable (food_cond) caused an error
        perror("Error, failed to destroy conditional variable (food_cond)");
    }

    if(pthread_mutex_destroy(&food_mutex)) {
        // Destroying mutex (food_mutex) caused an error
        perror("Error, failed to destroy mutex (food_mutex)");
    }

}