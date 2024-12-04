/**
 * A simple thread example
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../header/simple_thread.h"


/**
 * 
 */
void* my_thread1()
{
    printf("Starting thread\n");
    sleep(4);
    printf("Ending thread\n");
    return NULL;
}

/**
 * 
 */
void* my_thread2(void* arg)
{
    char* msg = "";   // default is null string 

    // validating that void* is not null pointer 
    if (arg != NULL) {
        // Explicit casting of void* to char*
        msg = (char*) arg;
        // Validating the arg is pointing to a string of lenght <= MAX_LEN
        // Otherwise, point to null character
        if(strlen(msg) > MAX_LEN) {
            // Revert arg to null character
            // msg = '\0';
            // Revert arg to null string
            msg = "";
        }
    }
    printf("Starting thread with arg (%s)\n", msg);
    // Sleeping for nearly a minute
    if(usleep(999999)) {
        perror("Error, usleep() failed");
    }
    printf("Ending thread with arg (%s)\n", msg);
    return NULL;
}