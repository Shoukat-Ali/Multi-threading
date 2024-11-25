/**
 * 
*/

#ifndef BROADCAST_PRODUCER_CONSUMER_H
#define BROADCAST_PRODUCER_CONSUMER_H


#include <pthread.h>


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

#endif