/**
 * 
 */

#include <iostream>
#include "../header/simple_mutex.hpp"

/**
 * 
 */
SimpleMutex::SimpleMutex(int nthrds, int cnt) : NumThreads(nthrds), Count(cnt), SharedRsc(0) 
{
    if (nthrds <= 0 || cnt <= 0) {
        // For now, simply printing error message
        // TODO: throw exception
        std::cout << "Number of threads and count value must be positive\n";
    }
}


/**
 * 
 */
void SimpleMutex::run() 
{
    // Creating vector of threads
    std::vector<std::thread> threads;

    for (int i = 0; i < NumThreads; ++i) {
        threads.push_back(std::thread(increment_count, this));
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}


/**
 * 
 */
int SimpleMutex::get_count() 
{
    int CurrVal = -1;
    mtx.lock();
    CurrVal = SharedRsc;
    mtx.unlock();

    return CurrVal;
}


/**
 * 
 */
void SimpleMutex::increment_count() 
{
    std::cout << "Thread id:" << std::this_thread::get_id() << "\n";
    for (int i = 0; i < Count; ++i) {
        // Locks the mutex. If another thread has already locked the mutex, 
        // a call to lock will block execution until the lock is acquired.
        // syntax: void lock();
        mtx.lock();
        
        // Criticial section or atomic code
        SharedRsc++;

        // unlocks the mutex
        // The mutex must be locked by the current thread of execution, otherwise, the behavior is undefined.
        // syntax: void unlock();  
        mtx.unlock();
    }
}