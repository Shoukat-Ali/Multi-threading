/**
 * 
*/

#ifndef SIMPLE_PRODUCER_CONSUMER_H
#define SIMPLE_PRODUCER_CONSUMER_H

// #include <stdio.h>
#include <pthread.h>


extern int food;   // Global variable
extern pthread_mutex_t food_mutex;     // Lock for updating shared food variable

extern pthread_cond_t food_cond;   // mutex conditional variable

/**
 * Thread for producing food i.e., increasing the value of the shared food variable
 * 
*/
void* producer();


/**
 * Thread for consuming food if greater than some threshold
 * 
*/
void* consumer();


#endif