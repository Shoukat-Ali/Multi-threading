/**
 * 
 */

#ifndef ATOMIC_EXAMPlE_HPP
#define ATOMIC_EXAMPlE_HPP

#include <atomic>
#include <vector>
#include <thread>


class SimpleAtomic 
{
    public:
        SimpleAtomic(int NumThrds, int cnt);
        void increment_atomic();
        int get_atomic_value();
        void run();

    private:
        int nthrds;
        int counter;
        /**
         * Each instantiation and full specialization of the std::atomic template
         * defines an atomic type. If one thread writes to an atomic object while another
         * thread reads from it, the behavior is well-defined.
         * 
         * In addition, accesses to atomic objects may establish inter-thread synchronization and
         * order non-atomic memory accesses as specified by std::memory_order.
         * 
         * std::atomic is neither copyable nor movable.
         */
        std::atomic<int> shared_rsc;

};

#endif