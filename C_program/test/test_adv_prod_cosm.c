/**
 * 
 *  
 * gcc -Wall -Werror -g3 -O3 ../source/adv_prod_cosm.c test_adv_prod_cosm.c -o prog
*/

#include <stdio.h>
#include <time.h>
#include "../header/adv_prod_cosm.h"


#define NUM_THREADS 5
 

int buffer[ArrayBound];
int count = 0;


sem_t semEmpty;
sem_t semFull;
pthread_mutex_t mBuffer;


/**
 * 
 */
int main()
{
    int i, ret = 0;
    pthread_t thrd[NUM_THREADS];
    
    // Initializing required resources
    if((ret = initialize())) {
        printf("Error, initialization failed with error number: %i\n", ret);
        return ret;
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        if (i & 1) {
            // Odd 
            if(pthread_create(&thrd[i], NULL, producer, NULL)) {
                perror("Error, producer thread creation failed");
                // Attempt to clean up the resources
                clean_up();
                return ERR_PROD_THRD_CREATE;
            }
        } else {
            // Even
            if(pthread_create(thrd + i, NULL, consumer, NULL)) {
                perror("Error, consumer thread creation failed");
                // Attempt to clean up the resources
                clean_up();
                return ERR_COSM_THRD_CREATE;
            }
        }
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(pthread_join(thrd[i], NULL)) {
            perror("Error, (joinable) thread termination failed");
            // Attempt to clean up the resources
            clean_up();
            return ERR_THRD_JOIN;
        }
    }

    clean_up();
    return 0;
}