/**
 * A simple thread example
*/

#include <stdio.h>
#include <unistd.h>

void* my_thread1()
{
    printf("Starting thread-1\n");
    sleep(2);
    printf("Ending thread-1\n");
    return NULL;
}

void* my_thread2()
{
    printf("Starting thread-2\n");
    sleep(4);
    printf("Ending thread-2\n");
    return NULL;
}