/**
 * 
 * 
 */

#ifndef BARRIER_DICE_H
#define BARRIER_DICE_H

#include <pthread.h>

extern int diceValue[];         // Storing the result of each dice roll by a thread
extern int winnerStatus[];      // 1 is winner, 0 is losser
extern pthread_mutex_t mLock;    // To lock shared resource(s) 


extern pthread_barrier_t diceBarrier;   // barrier for rolling dice
extern pthread_barrier_t decisionBarrier;   // barrier for deciding winner(s)


#define ERR_BARRIER_INIT 1
#define ERR_THRD_CREATE 2
#define ERR_THRD_JOIN 3
#define ERR_BARRIER_WAIT 4
#define ERR_MUTEX_INIT 5
#define ERR_MUTEX_LOCK 6
#define ERR_MUTEX_UNLOCK 7

#define DICE_LIMIT 6        // Limit the range of dice values to [0-6]
#define NUM_THREAD 11       // The number of threads and index range
#define NUM_ROUNDS 3       // For testing purpose

/**
 * 
 */
int initialize();


/**
 * 
*/
void* roll_dice(void* indx);


/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up();


#endif