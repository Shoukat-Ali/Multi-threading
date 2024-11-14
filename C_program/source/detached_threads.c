/**
 * 
*/

#include <unistd.h>
#include "../header/detached_threads.h"

/**
 * 
 */
void* thrd_func() 
{
    printf("Nothing interesting to do, therefore, sleep\n");
    usleep(600000); // Sleep for 600 ms or 0.6-sec
    printf("Finished execution\n");
    return NULL;
}