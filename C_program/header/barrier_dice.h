/**
 * 
 * 
 */

#ifndef BARRIER_DICE_H
#define BARRIER_DICE_H

#include <pthread.h>

extern int diceValue[];         // Storing the result of each dice roll by a thread
extern int winnerStatus[];      // 1 is winner, 0 is losser

extern pthread_barrier_t diceBarrier;   // barrier for rolling dice
extern pthread_barrier_t decisionBarrier;   // barrier for deciding winner(s)

#define ERR_BARRIER_INIT 1
#define ERR_THRD_CREATE 2
#define ERR_THRD_JOIN 3
#define ERR_BARRIER_WAIT 4


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