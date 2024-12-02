/**
 * Testing a simple producer and consumer program using mutex and conditional variable 
 * on Ubuntu using pthread library.
 *  
 * gcc -Wall -Werror -g3 -O3 ../source/simple_prod_cosm.c test_simple_prod_cosm.c -o prog
*/

#include <stdio.h>
#include "../header/simple_prod_cosm.h"


#define NUM_THREADS 4  


int main()
{
    int i;
    pthread_t thrd[NUM_THREADS];

    printf("To consume food, the threshold is set to :: %u\n", FOOD_THRESHOLD);
    
    if(pthread_mutex_init(&food_mutex, NULL)) {
        // Mutex initialization of food_mutex failed
        perror("Error, failed to initialize the (food_mutex) mutex");
        return ERR_MUTEX_INIT;
    }
    /**
     * int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
     * 
     * The pthread_cond_init() initializes the condition variable cond, using 
     * the condition attributes specified in cond_attr, or default attributes 
     * if cond_attr is NULL.  The LinuxThreads implementation supports no attributes 
     * for conditions, hence the cond_attr parameter is actually ignored.
     * Variables of type pthread_cond_t can also be initialized statically, 
     * using the constant PTHREAD_COND_INITIALIZER.
     * 
     * A condition variable must always be associated with a mutex, to avoid 
     * the race condition where a thread prepares to wait on a condition variable and 
     * another thread signals the condition just before the first thread actually waits on it.
     * 
     * On successful, a value of zero is returned. Otherwise, an error number is returned 
     * to indicate the error.
     */
    if(pthread_cond_init(&food_cond, NULL)) {
        // Conditional variable initialization of food_cond failed
        perror("Error, failed to initialize the conditional variable (food_cond)");
        // Attempt to destroy initialized mutex, therefore, ignoring return value
        pthread_mutex_destroy(&food_mutex);
        return ERR_COND_VAR_INIT;
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(i < (NUM_THREADS - 1)) {
            // Creating consumer thread
            if(pthread_create(thrd + i, NULL, &consumer, NULL)) {
                perror("Error, consumer thread creation failed");
                // Attempt to clean up the resources
                clean_up();
                return ERR_COSM_THRD_CREATE;
            }
        }
        else{
            // Creating producer thread
            if(pthread_create(thrd + i, NULL, &producer, NULL)) {
                perror("Error, producer thread creation failed");
                // Attempt to clean up the resources
                clean_up();
                return ERR_PROD_THRD_CREATE;
            }
        }
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(pthread_join(thrd[i], NULL)) {
            perror("Error, thread termination failed");
            // Attempt to clean up the resources
            clean_up();
            return ERR_THRD_JOIN;
        }
    }

    // Attempt to clean up the resources
    clean_up();
    return 0;
}