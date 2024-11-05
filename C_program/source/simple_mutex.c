/**
 * 
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>     // Required for syscall()
#include <sys/syscall.h>    // Required for SYS_* constant
#include "../header/simple_mutex.h"


#define ITERATIONS 1000000

void* simple_thread()
{
    /**
     * pid_t getpid(void);
     * 
     * getpid() returns the process ID (PID) of the calling process. 
     * (This is often used by routines that generate unique temporary filenames.)
     * 
     * getppid() returns the process ID of the parent of the calling process. 
     * This will be either the ID of the process that created this process using fork(), 
     * or, if that process has already terminated, the ID of the process to which 
     * this process has been reparented (either init(1) or a "subreaper" process defined via 
     * the prctl(2) PR_SET_CHILD_SUBREAPER operation).
     * 
     * These functions are always successful.
     * 
     * Note: syscall() is system-dependent, therefore, portability issue across different platforms
     * Therefore, one can use pthread_self(void);
     */
    // printf("Starting: Process id: %d, Thread id: %ld\n", getpid(), syscall(SYS_gettid));
    printf("Starting:: Process id: %d, Thread id: %lu\n", getpid(), (unsigned long)pthread_self());

    for(int i = 0; i < ITERATIONS; ++i) {
        /**
         * POSIX Manual
         * int pthread_mutex_lock(pthread_mutex_t *mutex);
         * 
         * The mutex object referenced by mutex shall be locked by a call to pthread_mutex_lock() 
         * that returns zero or [EOWNERDEAD]. If the mutex is already locked by another thread, 
         * the calling thread shall block until the mutex becomes available.
         * 
         * If successful, the pthread_mutex_lock() functions shall return zero;
         * otherwise, an error number shall be returned to indicate the error.
         * 
         * TODO: check for the deadlock
         */
        if(!pthread_mutex_lock(&lock)) {
            // Obtained lock and owned, therefore, update shared resource
            shared++;
        
            /**
             * int pthread_mutex_unlock(pthread_mutex_t *mutex);
             * 
             * The pthread_mutex_unlock() function shall release the mutex object referenced by mutex. 
             * The manner in which a mutex is released is dependent upon the mutex's type attribute. 
             * If there are threads blocked on the mutex object referenced by mutex when
             * pthread_mutex_unlock() is called, resulting in the mutex becoming available, 
             * the scheduling policy shall determine which thread shall acquire the mutex.
             * 
             * If successful, the pthread_mutex_unlock() functions shall return zero;
             * otherwise, an error number shall be returned to indicate the error.
             * 
             */
            // Note: Shouldn't fail because locked and owner
            if(pthread_mutex_unlock(&lock)) {
                // in case of error
                perror("Failed to unlock");
            }
        }
    }
    // printf("Ending  :: Process id: %d, Thread id: %ld\n", getpid(), syscall(SYS_gettid));
    printf("Ending::   Process id: %d, Thread id: %lu\n", getpid(), (unsigned long)pthread_self());
    return NULL;
}