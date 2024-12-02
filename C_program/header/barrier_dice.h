/**
 * 
 * 
 */

#ifndef BARRIER_DICE_H
#define BARRIER_DICE_H

#include <pthread.h>


extern int diceValue[];    // Storing the result of each dice roll by a thread
extern int winnerStatus[];  // 1 is winner, 0 is losser

extern pthread_barrier_t diceBarrier;   // barrier for rolling dice
extern pthread_barrier_t decisionBarrier;   // barrier for deciding winner(s)

/**
 * 
*/
void* roll_dice(void* indx);


#endif