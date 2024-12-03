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
     
    printf("(%d) Waiting in the login queue\n", index);
    sem_wait(&semUser);
    printf("(%d) Logged in\n", index);
    sleep(2);
    printf("(%d) Logged out\n", index);
    sem_post(&semUser);
    return NULL;
}