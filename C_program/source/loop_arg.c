/**
 * 
*/

#include <stdio.h>
#include <unistd.h>     // Required for syscall()
#include <sys/syscall.h>  // Required for SYS_* constant
#include <pthread.h>
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
    /**
     * long syscall(long number, ...);
     * 
     * syscall() - indirect system call
     * syscall() is a small library function that invokes the system call 
     * whose assembly language interface has the specified number with the 
     * specified arguments. Employing syscall() is useful, for example, 
     * when invoking a system call that has no wrapper function in the C library.
     * 
     * Symbolic constants for system call numbers can be found in the header file <sys/syscall.h>.
     * 
     * The return value is defined by the system call being invoked. In general, 
     * a 0 return value indicates success.  A -1 return value indicates an error, 
     * and an error number is stored in errno.
     * 
     * Note: syscall() is system-dependent, therefore, portability issue across different platforms 
     */
    printf("Thread id using syscall()     : %ld, \t\t prime number: %d\n", syscall(SYS_gettid), pnum);

    /**
     * pthread_t pthread_self(void);
     * 
     * The pthread_self() function returns the ID of the calling thread. 
     * This is the same value that is returned in *thread in the pthread_create(3) 
     * call that created this thread.
     * 
     * This function always succeeds, returning the calling thread's ID.
     */
    printf("Thread id using pthread_self(): %lu, prime number: %d\n", (unsigned long)pthread_self(), pnum);
    return NULL;
}