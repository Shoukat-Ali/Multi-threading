/**
 * 
*/

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdio.h>
#include <semaphore.h>  // For semaphore

/**
 * Based on the POSIX manual, The <semaphore.h> header shall define the sem_t type, 
 * used in performing semaphore operations. The semaphore may be implemented
 * using a file descriptor, in which case applications are able to open up 
 * at least a total of {OPEN_MAX} files and semaphores.
 * 
 * The <semaphore.h> header shall define the symbolic constant SEM_FAILED 
 * which shall have type sem_t *.
 * 
 */
extern sem_t semUser; // Declaration


// TODO: bound check on the number of threads
#define NUM_THREAD 17
#define SEMAPHORE_LIMIT 7

#define ERR_SEMAPHORE_INIT 1
#define ERR_THRD_CREATE 2
#define ERR_THRD_JOIN 3


int* my_queue[NUM_THREAD] = {NULL};  // Array of pointers


/**
 * 
*/
void* my_thrd();


/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up();

#endif