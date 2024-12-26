/**
 * This program demonstrates a simple multi-threading program using the class thread (std::thread since C++11)
 * where class vector is used for threads. Moreover, threads are created usig normal and lambda function and tested on Ubuntu.
 * 
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_thread_vec.cpp ../source/thread_vec.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_thread_vec.cpp ../source/thread_vec.cpp -o prog
 * 
 * For using -fsanitize=thread, if you get the following memory mapping error
 * FATAL: ThreadSanitizer: unexpected memory mapping
 * 
 * then one solution could be to run
 * sudo sysctl vm.mmap_rnd_bits=30
 * 
 * Note that, for the above solution to work, you need to run the command on every reboot
 * 
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "../header/thread_vec.hpp"


int main()
{
    // Defining vector of threads
    std::vector<std::thread> threads;
    
    // Defining lambda function/experssion i.e., unnamed function
    auto lambda_thread = [] (int n) {
        for (int i = 0; i < COUNTER; ++i) {
            std::cout << "Thread id (" << std::this_thread::get_id() << ") :: "
                      << n << "\n";
            // sleep for 10ms
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }   
    };
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (i & 1) {
            // If Odd, then lambda function
            threads.push_back(std::thread(lambda_thread, i));
        }
        else {
            // If Even, then normal function
            threads.push_back(std::thread(thrd, i));
        }
    }
    
    std::cout << "Main thread waiting for other threads to finish\n";
    for (int i = 0; i < NUM_THREADS; ++i) {
        // Blocks the current thread until the thread identified by *this finishes its execution
        threads[i].join();
        std::cout << "threads[" << i << "] id after join: " << threads[i].get_id() << "\n";
    }
    
    return 0;
}