/**
 * A simple thread program
*/

#ifndef SIMPLE_THREAD_H
#define SIMPLE_THREAD_H

#define ERRTHRDCRT 1
#define ERRTHRDJON 2

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