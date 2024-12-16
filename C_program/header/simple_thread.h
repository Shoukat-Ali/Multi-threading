/**
 * A simple (joinable) multi-threading program using pthread on Ubuntu.
 * In POSIX, a thread is in a joinable state by default. The parent thread can 
 * wait for the joinable thread to finish its execution using pthread_join().
*/

#ifndef SIMPLE_THREAD_H
#define SIMPLE_THREAD_H

#define ERR_THRD_CREATE 1
#define ERR_THRD_JOIN 2

#define MAX_LEN 55  // For testing by restrict maximum string length

/**
 * 
*/
void* my_thread1();

/**
 * 
*/
void* my_thread2(void* arg);

#endif