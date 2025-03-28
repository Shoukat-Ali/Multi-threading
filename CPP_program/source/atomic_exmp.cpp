/**
 * 
 */

#include <iostream>
#include <stdexcept>
#include <limits>
#include "../header/atomic_exmp.hpp"


/**
 * Constructor
 */
SimpleAtomic::SimpleAtomic(int NumThrds, int cnt) : nthrds(NumThrds), counter(cnt), shared_rsc(0) 
{
    if(NumThrds < 0 || cnt < 0) {
        // For now, simply print error message
        throw std::invalid_argument("Number of threads and counter cannot be negative integers");
    }
    if ((static_cast<long long>(NumThrds) * cnt) > std::numeric_limits<int>::max()) {
        throw std::overflow_error("Integer overflow can happend in shared_rsc");
    }
}


/**
 * The function returns the current value of the atomic integer variable
 */
int SimpleAtomic::get_atomic_value() 
{
    /**
     * T load(std::memory_order order = std::memory_order_seq_cst) const noexcept;
     * 
     * OR
     * 
     * T load(std::memory_order order = std::memory_order_seq_cst) const volatile noexcept;
     * 
     * Atomically loads and returns the current value of the atomic variable. 
     * Memory is affected according to the value of order. If order is 
     * one of std::memory_order_release and std::memory_order_acq_rel, 
     * then the behavior is undefined. 
     * 
     * memory_order_seq_cst: A load operation with this memory order performs an acquire operation, 
     * a store performs a release operation, and read-modify-write performs both an acquire operation 
     * and a release operation, plus a single total order exists in which all threads observe all 
     * modifications in the same order.
     *  
     */
    return shared_rsc.load();
}



/**
 * The function increments counter of times the atomic integer variable 
 */
void SimpleAtomic::increment_atomic() 
{
    for (int i = 0; i < counter; ++i) {
        ++shared_rsc;
        std::cout   << "Thread id: " << std::this_thread::get_id() 
                    << ", shared_rsc: " << shared_rsc.load() << '\n';
    }
    
}




/**
 * The function creates vector of threads and waits for the threads to finish execution  
 */
void SimpleAtomic::run() 
{
    std::vector<std::thread> threads;
    threads.reserve(nthrds);

    for (int i = 0; i < nthrds; ++i) {
        threads.push_back(std::thread(&SimpleAtomic::increment_atomic, this));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Finally we have, shared_rsc :: " << shared_rsc.load() << '\n';
}


/**
 * Destructor
 */
SimpleAtomic::~SimpleAtomic()
{
    nthrds = 0;
    counter = 0;
    shared_rsc = 0;
}