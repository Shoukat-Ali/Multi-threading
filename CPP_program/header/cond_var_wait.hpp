/**
 * 
 */

#ifndef CONDITION_VARIABLE_WAIT_HPP
#define CONDITION_VARIABLE_WAIT_HPP

#include <iostream>
#include <mutex>
#include <chrono>
#include <condition_variable>



class CondVarWait {
    private:
        unsigned int interval;
        std::condition_variable cv;
        std::mutex mtx;
        bool ready;

        // Use a separate mutex for cout to avoid potential deadlocks
        std::mutex CoutMtx;

    public:
        CondVarWait(unsigned int sec);
        void wait();
        void signal();
        void print_msg(const std::string& message);
        ~CondVarWait();

};

#endif