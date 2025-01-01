/**
 * 
 */

#ifndef JOBS_MUTEX_HPP
#define JOBS_MUTEX_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>




class JobMutex {
    private:
        std::chrono::milliseconds interval;
        std::mutex mtx;
        int job_shared;
        int job_exclusive;

    public:
        JobMutex(std::chrono::milliseconds mswait);
        void job_1();
        void job_2();
        void run();
};


#endif