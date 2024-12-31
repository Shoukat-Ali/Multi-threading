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
        const int Count;
        int SharedRsc;
        mutable std::mutex mtx;

    public:
        SimpleMutex(int nthrds, int cnt);       //Constructor
        void run();
        int get_count();
        void increment_count();

};

#endif