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
    // Ignore the return value of usleep()
    usleep(600000); // Sleep for 600 ms or 0.6-sec
    puts("Finished execution");
    return NULL;
}