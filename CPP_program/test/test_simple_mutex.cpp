/**
 * This program demonstrates a simple multi-threading program using the class thread (std::thread since C++11)
 * where mutex is used to protect a shared data from simultaneous access by multiple threads..
 * 
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_simple_mutex.cpp ../source/simple_mutex.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_simple_mutex.cpp ../source/simple_mutex.cpp -o prog
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
#include "../header/simple_mutex.hpp"


int main()
{
    const int NUM_THREADS = 55;
    const int COUNTER = 123456789;
    
    try {
        SimpleMutex ObjThrd(NUM_THREADS, COUNTER);
        ObjThrd.run();
        std::cout << "Final value of shared resource/counter is :: " << ObjThrd.get_count() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error, " << e.what() << "\n";
        return 1;
    }
    return 0;
}