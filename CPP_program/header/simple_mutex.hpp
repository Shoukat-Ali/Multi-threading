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
        void increment_count();
        const int NumThreads;
        const int Count;
        int SharedRsc;
        mutable std::mutex mtx;

    public:
        //Constructor
        SimpleMutex(int nthrds, int cnt);
        void run();
        int get_count();

};

#endif