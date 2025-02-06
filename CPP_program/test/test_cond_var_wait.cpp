/**
 * This program demonstrates the use of condition variables for thread synchronization, 
 * allowing multiple threads to wait for a specific condition to be met before proceeding.
 * 
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_cond_var_wait.cpp ../source/cond_var_wait.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_cond_var_wait.cpp ../source/cond_var_wait.cpp -o prog
 * 
 * For using -fsanitize=thread, if you get the following memory mapping error
 * FATAL: ThreadSanitizer: unexpected memory mapping
 * 
 * then one solution could be to run
 * sudo sysctl vm.mmap_rnd_bits=30
 * 
 * Note that, for the above solution to work, you need to run the command on every reboot
 */

#include <vector>
#include <thread>
#include "../header/cond_var_wait.hpp"


/**
 * 
 */
int main() 
{
    const unsigned int sec = 6;
    const unsigned int NumThrds = 5;

    try {
        CondVarWait Obj(sec);
        std::vector<std::thread> thrds;
        
        // Waiting threads 
        for (unsigned int i = 1; i < NumThrds; ++i) {
            thrds.push_back(std::thread(&CondVarWait::wait, &Obj));
        }
        
        // Signal thread
        thrds.push_back(std::thread(&CondVarWait::signal, &Obj));
        
        for (auto& thrd : thrds) {
            thrd.join();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error, " << e.what() << "\n";
        return 1;
    }

    return 0;
}