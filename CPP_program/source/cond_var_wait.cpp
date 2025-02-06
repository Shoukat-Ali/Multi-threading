/**
 * 
 */

#include <thread>
#include <vector>
#include "../header/cond_var_wait.hpp"

#define MAX_SLEEP_TIME 60

/**
 * Constructor
 */
CondVarWait::CondVarWait(unsigned int sec) : interval(sec), ready(false) 
{
    if(sec > MAX_SLEEP_TIME) {
        std::cout << "The maximum thread sleep is defined :: " << MAX_SLEEP_TIME << "-second\n";
        throw std::length_error("Thread sleep exceeds the maximum limit defined");
    }
}


/**
 * The functions attempts to writing to std::cout by preventing race conditions 
 * and ensuring thread-safe output.
 */
void CondVarWait::print_msg(const std::string& msg) 
{
    /**
     * When a lock_guard object is created, it attempts to take ownership of the mutex 
     * it is given. When control leaves the scope in which the lock_guard object was created, 
     * the lock_guard is destructed and the mutex is released. 
     * The lock_guard class is non-copyable.
     */
    std::lock_guard<std::mutex> lkgrd(CoutMtx);
    std::cout << msg << std::endl;
}


/**
 * The function attempts to make a thread wait for some condition to be met 
 * using a condition variable. 
 */
void CondVarWait::wait() 
{
    /**
     * The class unique_lock is a general-purpose mutex ownership wrapper allowing 
     * deferred locking, time-constrained attempts at locking, recursive locking, 
     * transfer of lock ownership, and use with condition variables.
     * The class unique_lock is movable, but not copyable
     * 
     */
    std::unique_lock<std::mutex> uqlk(mtx);
    print_msg("Waiting...");
    /**
     * void wait(std::unique_lock<std::mutex>& lock);
     * 
     * OR
     * 
     * template< class Predicate >
     * void wait(std::unique_lock<std::mutex>& lock, Predicate pred);
     * 
     * wait causes the current thread to block until the condition variable is notified 
     * or a spurious wakeup occurs. pred can be optionally provided to detect spurious wakeup.
     * 
     * Here the predicate ([this] { return ready; }) is a lambda function
     * 
     * For more details, please check https://en.cppreference.com/w/cpp/thread/condition_variable/wait
     *  
     */
    cv.wait(uqlk, [this] { return ready; });
    print_msg("...waiting over!");
}


/**
 * The function attempts thread synchronization by notifying waiting 
 * threads twice with a delay between notifications. 
 * The delay is set in seconds 
 */
void CondVarWait::signal() 
{
    // sleep for interval seconds
    std::this_thread::sleep_for(std::chrono::seconds(interval));
    {
        std::lock_guard<std::mutex> lk(mtx);
        print_msg("Notifying...");
    }
    cv.notify_all();

    // sleep for interval seconds
    std::this_thread::sleep_for(std::chrono::seconds(interval));

    {
        std::lock_guard<std::mutex> lk(mtx);
        ready = true;
        print_msg("Notifying again...");
    }
    cv.notify_all();
}


/**
 * Destructor
 */
CondVarWait::~CondVarWait()
{
    interval = 0; 
    ready = false;
}