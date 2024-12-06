/**
 * 
*/

#ifndef ADVANCE_PRODUCER_CONSUMER_H
#define ADVANCE_PRODUCER_CONSUMER_H


#include <pthread.h>
#include <semaphore.h>


#define ERR_MUTEX_INIT 1
#define ERR_SEMAPHORE_INIT 2
#define ERR_COSM_THRD_CREATE 3
#define ERR_PROD_THRD_CREATE 4
#define ERR_THRD_JOIN 5
#define ERR_MUTEX_INIT 6
#define ERR_MUTEX_LOCK 7
#define ERR_MUTEX_UNLOCK 8


const int Bound = 100;
#define SEMAPHORE_LIMIT 10

extern int buffer[];
extern int count;

extern sem_t semEmpty;
extern sem_t semFull;

extern pthread_mutex_t mBuffer;

/**
 * 
 * On success, returns 0; otherwise an error number (non-zero integers) is returned.
 * 
 */
int initialize();

/**
 * 
*/
void* producer();

/**
 * 
*/
void* consumer();


/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up();

#endif