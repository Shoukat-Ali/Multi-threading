/**
 * 
 */

#include "../header/jobs_mutex.hpp"

const unsigned int longerwait = 5;  // For job_2() longer sleep, interval * longer wait

/**
 * 
 */
JobMutex::JobMutex(std::chrono::milliseconds mswait) : interval(mswait), job_shared(0), job_exclusive(0)
{
    // For now, nothing here
}


/**
 * This thread can modify both 'job_shared' and 'job_exclusive'
 */
void JobMutex::job_1() 
{
    // Let's wait so that 'job_2()' get a change to lock mutex
    std::this_thread::sleep_for(interval); 

    while (true) {
        // Try to lock mutex to modify 'job_shared'
        if (mtx.try_lock()) { 
            std::cout << "job_1 (Thread id: " << std::this_thread::get_id()
                      << " shared :: " << job_shared << "\n";
            mtx.unlock();
            return;
        } else {
            // Can't get lock to modify 'job_shared'
            // Perform work on exclusive resource
            ++job_exclusive;
            std::cout << "job_1 (Thread id: " << std::this_thread::get_id() 
                      << " exclusive [" << job_exclusive << "]\n";
            std::this_thread::sleep_for(interval);
        }
    }
}


/**
 * This thread can modify only 'job_shared'
 */
void JobMutex::job_2() 
{
    // lock mutex
    mtx.lock();
    
    // First wait
    std::this_thread::sleep_for(longerwait * interval);
    // Modify the shared resource
    job_shared = longerwait;
    
    // unlock mutex
    mtx.unlock();
    std::cout << "job_2 (Thread id: " << std::this_thread::get_id() << ") done!\n";
}


/**
 * 
 */
void JobMutex::run() 
{
    std::thread thread_1(&JobMutex::job_1, this);
    std::thread thread_2(&JobMutex::job_2, this);

    thread_1.join();
    thread_2.join();
}