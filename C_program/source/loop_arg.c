/**
 * 
*/

#include <stdio.h>
#include <unistd.h>     // Required for syscall()
#include <sys/syscall.h>  // Required for SYS_* constant
#include "../header/loop_arg.h"


/**
 * 
*/
void* display_prime(void *PNum)
{
    int pnum = 1; // 1 is not prime number

    // Validating the void* is not null
    if (PNum != NULL) {
        // Casting PNum to integer pointer and de-referencing to display the content
        pnum  = *((int*) PNum);
        // Validation: Primes are +ve integer greater than 1
        if (pnum < 2) {
            // Revert to default value of 1
            pnum = 1;
        }
    }
    printf("Thread id: %ld, prime number: %d\n", syscall(SYS_gettid), pnum);
    return NULL;
}