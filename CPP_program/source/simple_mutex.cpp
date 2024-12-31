/**
 * 
 */

#include <iostream>
#include "../header/simple_mutex.hpp"

/**
 * 
 */
SimpleMutex::SimpleMutex(int nthrds, int cnt) : NumThreads(nthrds), count(cnt), SharedRsc(0) 
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
void SimpleMutex::increment_count() 
{
    std::cout << "Thread id:" << std::this_thread::get_id() << "\n";
    for (int i = 0; i < count; ++i) {
        /**
         * void lock();
         * 
         * Locks the mutex. If another thread has already locked the mutex, 
         * a call to lock will block execution until the lock is acquired.
         * 
         * If lock is called by a thread that already owns the mutex, the behavior is undefined: 
         * for example, the program may deadlock. An implementation that can detect the invalid 
         * usage is encouraged to throw a std::system_error with error condition 
         * resource_deadlock_would_occur instead of deadlocking. 
         */
        mtx.lock();
        
        // Criticial resource/section or atomic code
        SharedRsc++;

        /**
         * void unlock();
         * 
         * Unlocks the mutex. The mutex must be locked by the current thread of execution, 
         * otherwise, the behavior is undefined.
         *   
         * */  
        mtx.unlock();
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
        /**
         * Non-static member function is used to create thread.
         * When creating a thread using a member function then it is requried to:
         *      Use the address-of operator (&) before the function name.
         *      Provide a pointer to the object instance (in this case, this) as the first argument.
         * 
         */
        threads.push_back(std::thread(&SimpleMutex::increment_count, this));
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
    // Lock mutex
    mtx.lock();
    CurrVal = SharedRsc;
    // Unlock mutex
    mtx.unlock();

    return CurrVal;
}


