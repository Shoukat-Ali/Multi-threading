/**
 * 
*/
#include <stdio.h>
#include <unistd.h>
#include "../header/simple_semaphore.h"



/**
 * 
*/
void* my_thrd(void* indx)
{
    int index;
    // Checking if void* is null
    if (!indx) {
        printf("Error, Null pointer passed to thread id '%ld'\n", (unsigned long)pthread_self());
        return NULL;
    }

    // Casting indx to integer pointer and de-referencing to display the content
    index = *(int*) indx;
    // Validating the index value
    if (index < 0 || index >= NUM_THREAD) {
        printf("Error, invalid array index to thread id '%ld'\n", (unsigned long)pthread_self());
        return NULL;
    }
     
    printf("User: (%d) is waiting in the login queue\n", index);
    /**
     * int sem_wait(sem_t *sem);
     * 
     * sem_wait() decrements (locks) the semaphore pointed to by sem.
     * If the semaphore's value is greater than zero, then the decrement proceeds, 
     * and the function returns, immediately. If the semaphore currently has the 
     * value zero, then the call blocks until either it becomes possible to perform 
     * the decrement (i.e., the semaphore value rises above zero), 
     * or a signal handler interrupts the call.
     * 
     * The function returns 0 on success; on error, the value of the semaphore 
     * is left unchanged, -1 is returned, and errno is set to indicate the error.
     * 
     */
    if(sem_wait(&semUser)) {
        perror("Error, sem_wait() failed");
    }
    printf("User: (%d) is logged in\n", index);
    // Sleeping for nearly a minute
    if(usleep(999999)) {
        perror("Error, usleep() failed");
    }
    printf("User: (%d) is logged out\n", index);
    /**
     * int sem_post(sem_t *sem);
     * 
     * sem_post() increments (unlocks) the semaphore pointed to by sem.
     * If the semaphore's value consequently becomes greater than zero, 
     * then another process or thread blocked in a sem_wait() call will
     * be woken up and proceed to lock the semaphore.
     * 
     * On success, returns 0; on error, the value of the semaphore is left 
     * unchanged, -1 is returned, and errno is set to indicate the error.
     * 
     */
    if (sem_post(&semUser)) {
        perror("Error, sem_post() failed");
    }
    return NULL;
}



/**
 * The functions attempts to clean up the utilized resources.
 * If the clean up was not successful, then the error is reported
 * 
 */
void clean_up()
{
    for(int i = 0; i < NUM_THREAD; i++) {
        free(my_queue[i]);
        my_queue[i] = NULL;
    }

    /**
     * int sem_destroy(sem_t *sem);
     * 
     * sem_destroy() destroys the unnamed semaphore at the address pointed to by sem. 
     * 
     * Only a semaphore that has been initialized by sem_init(3) should be destroyed 
     * using sem_destroy(). Destroying a semaphore that other processes or threads are
     * currently blocked on (in sem_wait(3)) produces undefined behavior.
     * 
     * On success, returns 0; on error, -1 is returned, and errno is set to indicate the error.
     * 
     */
    if(sem_destroy(&semUser)) {
        perror("Error, destroying semaphore failed");
    }

}