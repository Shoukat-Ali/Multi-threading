/**
 * 
 */

#include <iostream>
#include <thread>
#include <chrono>
#include "../header/thread_vec.hpp"


/**
 * 
 */
void thrd(int a) 
{
    for (int i = 0; i < COUNTER; ++i) {
        std::cout   << "Thread id (" << std::this_thread::get_id() << ") :: "
                    << a << "\n";
        /**
        * template< class Rep, class Period >
        * void sleep_for( const std::chrono::duration<Rep, Period>& sleep_duration );
        * 
        * Blocks the execution of the current thread for at least the specified sleep_duration.
        * The function may block for longer than sleep_duration due to scheduling or 
        * resource contention delays. The standard recommends that a steady clock is used 
        * to measure the duration. If an implementation uses a system clock instead, 
        * the wait time may also be sensitive to clock adjustments. 
        * 
        * 
        * std::chrono::milliseconds is defined	
        *      std::chrono::duration<int45, std::milli>
        * 
        * where int45 represents at least 45-bit signed integer
        * the std::milli represents std::ratio<1, 1000> 
        * 
        */
        // Sleep for 10ms
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}