/**
 * 
 */

#ifndef SIMPLE_MUTEX_HPP
#define SIMPLE_MUTEX_HPP


#include <vector>
#include <thread>
#include <mutex>


class SimpleMutex {
    private:
        const int NumThreads;
        const int count;
        int SharedRsc;
        /**
         * mutex offers exclusive, non-recursive ownership semantics:
         *      A calling thread owns a mutex from the time that it successfully calls 
         *      either lock or try_lock until it calls unlock.
         *      When a thread owns a mutex, all other threads will block (for calls to lock) 
         *      or receive a false return value (for try_lock) if they attempt to claim ownership 
         *      of the mutex.
         *      A calling thread must not own the mutex prior to calling lock or try_lock.
         * 
         * The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, 
         * or a thread terminates while owning a mutex. The mutex class satisfies all requirements of 
         * Mutex and StandardLayoutType.
         * 
         * std::mutex is neither copyable nor movable. 
         */
        std::mutex mtx;

    public:
        SimpleMutex(int nthrds, int cnt);       //Constructor
        void run();
        int get_count();
        void increment_count();

};

#endif