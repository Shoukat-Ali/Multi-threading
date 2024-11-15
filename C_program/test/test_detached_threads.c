/**
 * A simple detached thread program
 * 
 * gcc -Wall -Werror -g3 -O3 ../source/detached_threads.c test_detached_threads.c -o prog
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
    
    // Setting thread attributes explicitly
    /**
     * int pthread_attr_init(pthread_attr_t *attr);
     * 
     * The pthread_attr_init() function initializes the thread 
     * attributes object pointed to by attr with default attribute values. 
     * After this call, individual attributes of the object can be set 
     * using various related functions, and then the object can be used 
     * in one or more pthread_create() calls that create threads
     * 
     * If successful, returns 0. Otherwise, returns -1 and sets the errno
     * 
     */
    if(pthread_attr_init(&detachedThread)) {
        perror("Failed to initialize the thread attribute object");
        return ERR_THRD_ATTR_INIT;
    }
    /**
     * int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
     * 
     * The pthread_attr_setdetachstate() function sets the detach state 
     * attribute of the thread attributes object referred to by attr to the 
     * value specified in detachstate.  The detach state attribute determines 
     * whether a thread created using the thread attributes object attr will be 
     * created in a joinable or a detached state.
     * 
     * PTHREAD_CREATE_DETACHED and PTHREAD_CREATE_JOINABLE values may be specified in detachstate
     * and the default value is PTHREAD_CREATE_JOINABLE.
     * 
     * On success, the function returns 0. Otherwise, nonzero error number is returned.
     */
    if(pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED)) {
        perror("Failed to set thread attribute object to detach state ");
        // Attempt to destroy the thread attribute object
        // Here, we ignore the return value from pthread_attr_destroy()
        pthread_attr_destroy(&detachedThread);
        return ERR_THRD_ATTR_DATCH_STATE;
    }
    
    for(i = 0; i < NUM_THREAD; i++) {
        if(pthread_create(thrd + i, &detachedThread, &my_thrd, NULL) != 0) {
            perror("Thread creation failed");
            // Attempt to destroy the thread attribute object
            // Here, we ignore the return value from pthread_attr_destroy()
            pthread_attr_destroy(&detachedThread);
            return ERR_THRD_CREATE;
        }
        // Note: Not a good idea to call pthread_detach() separately
        // pthread_detach(th[i]);
    }

    /**
     * int pthread_attr_destroy(pthread_attr_t *attr);
     * 
     * When a thread attributes object is no longer required, it should
     * be destroyed using the pthread_attr_destroy() function.
     * Destroying a thread attributes object has no effect on threads 
     * that were created using that object.
     * 
     * If successful, returns 0. Otherwise, returns -1 and sets the errno
     */
    if(pthread_attr_destroy(&detachedThread)) {
        perror("Failed to destroy the thread attribute object");
        return ERR_THRD_ATTR_DESTROY;
    }
    /**
     * void pthread_exit(void *retval);
     * 
     * The pthread_exit() function terminates the calling thread and
     * returns a value via retval that (if the thread is joinable) is 
     * available to another thread in the same process that calls pthread_join().
     * 
     * After the last thread in a process terminates, the process terminates as 
     * by calling exit() with an exit status of zero. Thus, process-shared resources 
     * are released and functions registered using atexit() are called.
     * 
     * To allow other threads to continue execution, the main thread should 
     * terminate by calling pthread_exit() rather than exit(3).
     * 
     * Note by calling pthread_exit(), the main thread ensures all thread to finish its execution
     */ 
    // puts("Main thread ended");   // For demonstration/testing
    pthread_exit(NULL);
    // puts("Main thread ended");   // For demonstration/testing
}