/**
 * Creating threads using loop and passing arguments
 * 
 * gcc -Wall -Werror -g3 -O3 ../source/loop_arg.c test_loop_arg.c -o prog
*/

#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include "../header/loop_arg.h"


#define NUM_THREADS 11


int main()
{
    pthread_t thrd[NUM_THREADS];
    int primes[NUM_THREADS] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, INT_MAX};
    int i;

    for(i = 0; i < NUM_THREADS; ++i) {
        // Note that the argument passed to thread is not shared
        if(pthread_create(thrd + i, NULL, &display_prime, primes + i)) {
            perror("Thread creation failed");
            return 1;
        }
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(pthread_join(thrd[i], NULL)) {
            perror("Thread termination failed");
            return 2;
        }
    }

    return 0;
}