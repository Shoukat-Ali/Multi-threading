/**
 * 
*/

#include "../header/chef_stove.h"

#define FUEL_CONSUMPTION_LIMIT 50

// Definition of global shared resource/data for the stove fuel
int stove_fuel[SHARED_RESOURCES] = {70, 50, 90, 80, 120};

void* chef_stove_thread()
{
    int i, fuel_consumption;
    fuel_consumption = (rand() % FUEL_CONSUMPTION_LIMIT) + 1;
    printf("Thread id '%ld' requires %d-fuel\n", (unsigned long)pthread_self(), fuel_consumption);

    for(i = 0; i < SHARED_RESOURCES; ++i) {
        if(!pthread_mutex_trylock(stove_mutex + i)) {
            // Locked the stove_mutex
            // Checking whehter there is enough fuel in the stove
            if(stove_fuel[i] - fuel_consumption < 0) {
                printf("Not enough fuel on stove '%d'\n", i);
                // Release the mutex and try for the next stove
                if(pthread_mutex_unlock(stove_mutex + i)) {
                    perror("Failed to unlock the mutex");
                    break;
                }
                // try for the next available stove
                continue;
            }
            else {
                stove_fuel[i] -= fuel_consumption;
                sleep(0.1); // sleep for 100 milli-sec
                printf("---> Updated stove '%d' fuel '%d'\n", i, stove_fuel[i]);
                // Release the mutex
                if(pthread_mutex_unlock(stove_mutex + i)) {
                    perror("Failed to unlock the mutex");
                    break;
                }
                // Don't attempt to use stove again
                break;
            }
        }
        else if(i == (SHARED_RESOURCES - 1)) {
            // Wait for some time before attempting to obtain the lock on mutex
            printf("No available mutex, therefore, waiting ...\n");
            sleep(0.5); // sleep for 500 milli-sec
            i = 0;
        }
    }
    return NULL;
}