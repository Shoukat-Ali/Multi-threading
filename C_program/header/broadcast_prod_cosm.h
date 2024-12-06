/**
 * 
*/

#ifndef BROADCAST_PRODUCER_CONSUMER_H
#define BROADCAST_PRODUCER_CONSUMER_H


#include <pthread.h>

#define ERR_MUTEX_INIT 1
#define ERR_COND_VAR_INIT 2
#define ERR_COSM_THRD_CREATE 3
#define ERR_PROD_THRD_CREATE 4
#define ERR_THRD_JOIN 5


#define PRODUCTION 50
#define FOOD_THRESHOLD 100
#define CONSUMPTION (FOOD_THRESHOLD - 20)  // Must be always less than FOOD_THRESHOLD
#define ROUND 10


extern int food;   // Global variable
extern pthread_mutex_t food_mutex;     // Lock for updating shared food variable
extern pthread_cond_t food_cond;   // mutex conditional variable


/**
 * Thread for producing food i.e., increating the value of food variable
*/
void* producer();


/**
 * Thread for consuming food if more than some threshold  
*/
void* consumer();

/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up();

#endif