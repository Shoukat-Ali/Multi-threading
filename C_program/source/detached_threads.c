/**
 * 
*/

#include <stdio.h>
#include <unistd.h>
#include "../header/detached_threads.h"

/**
 * 
 */
void* my_thrd() 
{
    puts("Nothing interesting to do, therefore, sleep");
    // Sleep for 600 ms or 0.6-sec
    if(usleep(600000)) {
        perror("Failed, usleep()");
    }
    puts("Finished execution");
    return NULL;
}