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
    printf("Starting thread-1\n");
    sleep(4);
    printf("Ending thread-1\n");
    return NULL;
}

/**
 * 
 */
void* my_thread2(void* arg)
{
    char* msg = '\0';   // default is null character 

    // validating that void* is not null pointer 
    if (arg != NULL) {
        // Explicit casting of void* to char*
        msg = (char*) arg;
        // Validating the arg is pointing to a string of lenght <= MAX_LEN
        // Otherwise, point to null character
        if(strlen(msg) > MAX_LEN) {
            // Revert arg to null character
            msg = '\0';
        }
    }
    printf("Starting thread-2 with arg (%s)\n", msg);
    sleep(2);
    printf("Ending thread-2\n");
    return NULL;
}