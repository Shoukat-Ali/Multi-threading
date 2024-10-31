/**
 * A simple thread example
*/

#include <stdio.h>
#include <unistd.h>

void* my_thread()
{
    printf("Starting thread\n");
    sleep(2);
    printf("Ending thread\n");
    return NULL;
}