/**
 * Testing simple thread program on Ubuntu using pthread
 * 
 * gcc -Wall -Werror -g3 -O3 ../source/simple_thread.c test_simple_thread.c -o prog
 * 
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>    //For threading
#include "../header/simple_thread.h"


int main()
{
    pthread_t t1, t2;   // pthread_t is a type used to identify a thread
    // Creating thread(s)
    /**
     * int pthread_create(pthread_t *restrict thread,
     *                    const pthread_attr_t *restrict attr,
     *                    void *(*start_routine)(void *),
     *                    void *restrict arg);
     * 
     * The pthread_create() function starts a new thread in the calling process. 
     * The new thread starts execution by invoking start_routine(); 
     * arg is passed as the sole argument of start_routine()
     * 
     * On success, pthread_create() returns 0; on error, it returns an error number, 
     * and the contents of *thread are undefined.
     */
    if(pthread_create(&t1, NULL, &my_thread1, NULL) != 0) {
        perror("Failed to create thread t1");
        return ERRTHRDCRT;
    }
    if(pthread_create(&t2, NULL, &my_thread2, NULL) != 0) {
        perror("Failed to create thread t2");
        return ERRTHRDCRT;
    }
    // Waiting for the thread(s) to terminate
    /**
     * int pthread_join(pthread_t thread, void **retval);
     * 
     * The pthread_join() function waits for the thread specified by thread to terminate. 
     * If that thread has already terminated, then pthread_join() returns immediately. 
     * The thread specified by thread must be joinable.
     * 
     * If retval is not NULL, then pthread_join() copies the exit status of the 
     * target thread (i.e., the value that the target thread supplied to pthread_exit(3)) 
     * into the location pointed to by retval. If the target thread was canceled, 
     * then PTHREAD_CANCELED is placed in the location pointed to by retval.
     * 
     * On success, pthread_join() returns 0; on error, it returns an error number.
     * 
     */
    if(pthread_join(t1, NULL) != 0) {
        perror("Termination of thread t1 failed");
        return ERRTHRDJON;
    }
    if(pthread_join(t2, NULL) != 0) {
        printf("Termination of thread t2 failed");
        return ERRTHRDJON;
    }

    return 0;
}