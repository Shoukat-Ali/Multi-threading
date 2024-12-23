/**
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/adv_prod_cosm.h"


const int Bound = 100;

/**
 * The function attempts to initialize the required resources for usage
 * 
 * On success, returns 0; otherwise an error number (non-zero integers) is returned.
 * 
 */
int initialize() 
{
    // initializing mutex
    if(pthread_mutex_init(&mBuffer, NULL)) {
        // Mutex initialization failed
        perror("Error, failed to initialize the mutex mBuffer");
        return ERR_MUTEX_INIT;
    }

    if(sem_init(&semEmpty, 0, SEMAPHORE_LIMIT)) {
        perror("Error, semaphore semEmpty initialization failed");
        // Attempt to destroy mutex
        pthread_mutex_destroy(&mBuffer);
        return ERR_SEMAPHORE_INIT;
    }

    if(sem_init(&semFull, 0, 0)) {
        perror("Error, semaphore semFull initialization failed");
        // Attempt to destroy semaphore semEmpty
        sem_destroy(&semEmpty);
        // Attempt to destroy mutex
        pthread_mutex_destroy(&mBuffer);
        return ERR_SEMAPHORE_INIT;
    }
    return 0;
}


/**
 * 
*/
void* producer()
{
    int x = 0;

    while (1) {
        // Produce
        x = rand() % Bound;

        // Causing producer thread to sleep for nearly a sec
        if(usleep(999999)) {
            perror("Error, producer usleep() failed");
        }
        // Add to the buffer
        if(sem_wait(&semEmpty)) {
            perror("Error, producer sem_wait(&semEmpty) failed");
        }
        // Obtain lock
        if(pthread_mutex_lock(&mBuffer)) {
            perror("Error, producer failed to lock mutex mBuffer");
            return NULL;
        }
        // Shared resources
        // TODO: verify count value never goes out of array index range
        if(count >= 0 && count < ArrayBound) {
            buffer[count] = x;
            count++;
        }

        // Release lock
        if(pthread_mutex_unlock(&mBuffer)) {
            perror("Error, producer failed to unlock mutex mBuffer");
            return NULL;
        }
        
        if (sem_post(&semFull)) {
            perror("Error, producer sem_post(&semFull) failed");
        }

        printf("Food Produced:: %d  (thread id: %lu)\n", x, (unsigned long)pthread_self());
        // printf("Food Produced: %d\n", x);
    }
}


/**
 * 
*/
void* consumer()
{
    int y = 0;

    while (1) {
        // Remove from the buffer
        if(sem_wait(&semFull)) {
            perror("Error, consumer sem_wait(&semFull) failed");
        }
        // Obtaind lock
        if(pthread_mutex_lock(&mBuffer)) {
            perror("Error, consumer failed to lock mutex mBuffer");
            return NULL;
        }
        // Shared resources
        // TODO: verify count value never goes out of array index range
        if(count > 0 && count < ArrayBound) {
            y = buffer[count - 1];
            count--;
        }
        
        // Release lock
        if(pthread_mutex_unlock(&mBuffer)) {
            perror("Error, consumer failed to unlock mutex mBuffer");
            return NULL;
        }

        if (sem_post(&semEmpty)) {
            perror("Error, consumer sem_post(&semEmpty) failed");
        }

        printf("Food Consumed:: %d  (thread id: %lu)\n", y, (unsigned long)pthread_self());
        // printf("Food Consumed: %d\n", y);
        // Causing consumer thread to sleep for 0.5 sec
        if(usleep(500000)) {
            perror("Error, consumer usleep() failed");
        }
    }
}


/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up()
{
    if(sem_destroy(&semEmpty)) {
        perror("Error, destroying semEmpty failed");
    }

    if(sem_destroy(&semFull)) {
        perror("Error, destroying semFull failed");
    }

    if(pthread_mutex_destroy(&mBuffer)) {
        perror("Error, failed to destroy mutex mBuffer");
    }

}