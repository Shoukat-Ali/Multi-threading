/**
 * Testing a simple (joinable) threads creation, execution, and termination of threads using loop and 
 * passing arguments to program on Ubuntu using pthread library (POSIX threads).
 * 
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
    int primes[NUM_THREADS] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, INT_MAX};    // INT_MAX is for testing only
    int i;

    for(i = 0; i < NUM_THREADS; ++i) {
        // Note that the argument passed to thread is not shared
        if(pthread_create(thrd + i, NULL, display_prime, &primes[i])) {
            perror("Thread creation failed");
            /**
             * What happens to created threads when main() returns?
             * 
             * Returning from the initial thread (main()) implicitly calls 
             * the exit subroutine, thus terminating all the threads in the process
             * Link: https://www.ibm.com/docs/en/aix/7.2?topic=programming-terminating-threads
             * 
             * 
             * Returning from main() is the same as calling exit(). 
             * This means handlers established by atexit(), and any system 
             * cleanup handlers are run. Finally the kernel is asked to terminate 
             * the entire process(i.e. all threads).
             * Link: https://stackoverflow.com/questions/23807867/what-happens-to-a-running-thread-on-return-from-main-in-c
             */
            return ERR_THRD_CREATE;
        }
    }

    for(i = 0; i < NUM_THREADS; ++i) {
        if(pthread_join(thrd[i], NULL)) {
            perror("Thread termination failed");
            return ERR_THRD_JOIN;
        }
    }

    return 0;
}