/**
 * This program demonstrates the use of atomic templated for thread synchronization, 
 * .
 * 
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_atomic_exmp.cpp ../source/atomic_exmp.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_atomic_exmp.cpp ../source/atomic_exmp.cpp -o prog
 * 
 * For using -fsanitize=thread, if you get the following memory mapping error
 * FATAL: ThreadSanitizer: unexpected memory mapping
 * 
 * then one solution could be to run
 * sudo sysctl vm.mmap_rnd_bits=30
 * 
 * Note that, for the above solution to work, you need to run the command on every reboot
 */

#include <iostream>
#include "../header/atomic_exmp.hpp"


int main() 
{
    const int NUM_THREADS = 7;
    const int COUNTER = 7;

    try {
        SimpleAtomic Obj(NUM_THREADS, COUNTER);
        std::cout << "Initial value of atomic shared resource :: " << Obj.get_atomic_value() << "\n";
        Obj.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error, " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}