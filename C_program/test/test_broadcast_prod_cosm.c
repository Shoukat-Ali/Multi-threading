/**
 * Testing a simple producer and consumer program using mutex and broadcasting on 
 * conditional variable on Ubuntu using pthread library.
 *  
 * gcc -Wall -Werror -g3 -O3 ../source/broadcast_prod_cosm.c test_broadcast_prod_cosm.c -o prog
 * 
*/

#include <stdio.h>
#include "../header/broadcast_prod_cosm.h"


#define NUM_THREADS 5 // For now, we have only producer and consumer


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
    
    if(pthread_cond_init(&food_cond, NULL)) {
        // Conditional variable initialization of food_cond failed
        perror("Error, failed to initialize the conditional variable (food_cond)");
        return ERR_COND_VAR_INIT;
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(i < (NUM_THREADS - 1)) {
            // Creating consumer thread
            if(pthread_create(thrd + i, NULL, &consumer, NULL)) {
                perror("Error, consumer thread creation failed");
                return ERR_COSM_THRD_CREATE;
            }
        }
        else{
            // Creating producer thread
            if(pthread_create(thrd + i, NULL, &producer, NULL)) {
                perror("Error, producer thread creation failed");
                return ERR_PROD_THRD_CREATE;
            }
        }
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(pthread_join(thrd[i], NULL)) {
            perror("Error, (joinable) thread termination failed");
            return ERR_THRD_JOIN;
        }
    }

    if(pthread_cond_destroy(&food_cond)) {
        // Destroying conditional variable (food_cond) caused an error
        perror("Error, failed to destroy conditional variable (food_cond)");
        return ERR_COND_VAR_DESTORY;
    }

    if(pthread_mutex_destroy(&food_mutex)) {
        // Destroying mutex (food_mutex) caused an error
        perror("Error, failed to destroy mutex (food_mutex)");
        return ERR_MUTEX_DESTORY;
    }
    return 0;
}