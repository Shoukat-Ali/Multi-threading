/**
 * 
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../header/simple_prod_cosm.h"



int food = 0;   // Global variable
pthread_mutex_t food_mutex;     // Lock for updating shared food variable
/**
 * Condition variables allow threads to wait until some event or condition has occurred
 * A condition variable has attributes that specify the characteristics of the condition. 
 * Typically, a program uses the following objects:
 *      A boolean variable, indicating whether the condition is met
 *      A mutex to serialize the access to the boolean variable
 *      A condition variable to wait for the condition
 * 
 * When a thread is terminated, its storage may not be reclaimed, depending on an attribute of the thread.
 * 
 */
pthread_cond_t food_cond;   // mutex conditional variable


/**
 * Thread for producing food i.e., increasing the value of the shared food variable
 * 
*/
void* producer()
{
    int i;
    // printf("Starting:: Producer thread id: %lu\n", (unsigned long)pthread_self());
    for(i = 0; i < ROUND; ++i) {
        if(!pthread_mutex_lock(&food_mutex)) {
            // Obtained lock and owned, therefore, update shared resource
            food += PRODUCTION;
            printf("Total food production:: %d  (thread id: %lu)\n", food, (unsigned long)pthread_self());
            if(pthread_mutex_unlock(&food_mutex)) {
                // Reporting error
                perror("Error, producer thread failed to release food mutex");
            }
        }
        else {
            // Reporting error
            perror("Producer thread failed to obtain food mutex");
        }
        /**
         * 
         * int pthread_cond_signal(pthread_cond_t *cond);
         * 
         * These functions shall unblock threads blocked on a condition variable
         * The pthread_cond_signal() function shall unblock at least one of
         * the threads that are blocked on the specified condition variable cond 
         * (if any threads are blocked on cond).
         * 
         * If more than one thread is blocked on a condition variable, then the
         * scheduling policy shall determine the order in which threads are unblocked.
         * 
         * If successful, the pthread_cond_signal() functions shall return zero. 
         * Otherwise, an error number shall be returned to indicate the error.
         * 
         * */ 
        if(pthread_cond_signal(&food_cond)) {
            perror("Error, producer thread failed to signal food conditional variable");
        }
        // Let take rest before producing more food
        // Sleep for 500 ms or 0.5-sec
        if(usleep(600000)) {
            perror("Failed, usleep()");
        }
    }
    printf("Ending:: Producer thread id: %lu\n", (unsigned long)pthread_self());
    return NULL;
}


/**
 * 
 * Thread for consuming food if more than some threshold  
 * 
*/
void* consumer()
{
    // printf("Starting:: Consumer thread id: %lu\n", (unsigned long)pthread_self());
    if(!pthread_mutex_lock(&food_mutex)) { 
        // Obtained lock and owned
        while(food < FOOD_THRESHOLD) {
            printf("Not enough food to consume (thread id: %lu)\n", (unsigned long)pthread_self());
            /**
             * int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
             * 
             * The pthread_cond_wait() functions shall block on a condition variable cond. 
             * They shall be called with mutex locked by the calling thread or undefined behavior results.
             * These functions atomically release mutex and cause the calling thread to block on the 
             * condition variable cond. Atomically here means "atomically with respect to access by another 
             * thread to the mutex and then the condition variable". 
             * That is, if another thread is able to acquire the mutex after the about-to-block thread 
             * has released it, then a subsequent call to pthread_cond_signal() or pthread_cond_broadcast() 
             * in that thread behaves as if it were issued after the about-to-block thread has blocked.
             * 
             * 
             * On successful, a value of zero is returned. Otherwise, an error number is returned to indicate the error.  
             */
            if(pthread_cond_wait(&food_cond, &food_mutex)) {
                perror("Error, failed to block food conditional variable");
            }
        }
        // Shared variable/resource
        food -= CONSUMPTION;
        printf("After consumption we have: %d food\n", food);
        if(pthread_mutex_unlock(&food_mutex)) {
            perror("Error, consumer thread failed to release food mutex");
        }
    }
    else {
        perror("Error, consumer thread failed to obtain food mutex");
    }
    printf("Ending:: Consumer thread id: %lu\n", (unsigned long)pthread_self());
    return NULL;
}