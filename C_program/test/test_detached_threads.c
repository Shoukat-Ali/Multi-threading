/**
 * 
*/

#include <stdio.h>
#include <pthread.h>
#include "../header/detached_threads.h"

#define NUM_THREAD 7

int main()
{
    int i;
    pthread_t thrd[NUM_THREAD];
    pthread_attr_t detachedThread;
    
    // Setting thread attributes
    pthread_attr_init(&detachedThread);
    pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);
    
    for(i = 0; i < NUM_THREAD; i++) {
        if(pthread_create(thrd + i, &detachedThread, &thrd_func, NULL) != 0) {
            perror("Thread creation failed");
            return 1;
        }
        // Note: Not a good idea to call pthread_detach() separately
        // pthread_detach(th[i]);
    }

    pthread_attr_destroy(&detachedThread);
    // Note by calling pthread_exit(), the main thread ensures all thread to finish its execution 
    pthread_exit(0);
}