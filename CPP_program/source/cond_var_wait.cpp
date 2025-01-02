/**
 * 
 */

#include <thread>
#include <vector>
#include "../header/cond_var_wait.hpp"

/**
 * 
 */
CondVarWait::CondVarWait(std::chrono::seconds waitsec) : interval(waitsec), ready(false) 
{
    // For now, nothing 
    // TODO: Restriction on waitsec value
}


/**
 * 
 */
void CondVarWait::print_msg(const std::string& msg) 
{
    /**
     * 
     */
    std::lock_guard<std::mutex> lkgrd(CoutMtx);
    std::cout << msg << std::endl;
}


/**
 * 
 */
void CondVarWait::wait() 
{
    std::unique_lock<std::mutex> uqlk(mtx);
    print_msg("Waiting...");
    cv.wait(uqlk, [this] { return ready; });
    print_msg("...finished waiting");
}


/**
 * 
 */
void CondVarWait::signal() 
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(mtx);
        print_msg("Notifying...");
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lk(mtx);
        ready = true;
        print_msg("Notifying again...");
    }
    cv.notify_all();
}

