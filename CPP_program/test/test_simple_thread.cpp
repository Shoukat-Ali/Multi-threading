/**
 * This program demonstrates a simple multi-threading program using the class thread (std::thread since C++11)
 * while the program is tested on Ubuntu.
 * 
 * The class thread represents a single thread of execution. 
 * Threads allow multiple functions to execute concurrently.
 * 
 * No two std::thread objects may represent the same thread of execution; 
 * std::thread is not CopyConstructible or CopyAssignable, although it is MoveConstructible and MoveAssignable.
 * 
 * -fsanitize=thread: Enable ThreadSanitizer, a fast data race detector. 
 * Memory access instructions are instrumented to detect data race bugs. 
 * See https://github.com/google/sanitizers/wiki#threadsanitizer for more details. 
 * The run-time behavior can be influenced using the TSAN_OPTIONS environment variable; 
 * see https://github.com/google/sanitizers/wiki/ThreadSanitizerFlags for a list of supported options.
 *
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_simple_thread.cpp ../source/simple_thread.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_simple_thread.cpp ../source/simple_thread.cpp -o prog
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
#include <thread> // C++11
#include "../header/simple_thread.hpp"


int main()
{
    int x = 7;
    float y = 2.34f;
    

    // Using lambda function as thread
    auto lambda_func = [] (int z) {
        std::cout << "\tLambda thread: " << z << "\n"; 
    };

    std::cout << "Main/Parent thread\n";
    
    // Creating threads using constructor
    /**
     * std::thread thread(Function&& f, Args&&... args);
     * 
     * The constructor creates a new std::thread object and associates it with a thread of execution.
     * The first argument f is a callable object to execute in the new thread
     * The second argument args represents the arguments to pass to the new function/thread
     * 
     * The arguments to the thread function are moved or copied by value. 
     * If a reference argument needs to be passed to the thread function, 
     * it has to be wrapped (e.g., with std::ref or std::cref).
     * 
     * Any return value from the function is ignored. If the function throws an exception, std::terminate is called. 
     * 
     */
        
    std::thread thrd1(&thrd_int, x);
    std::thread thrd2(&thrd_float, std::ref(y));
    std::thread thrd3(lambda_func, 99);
    std::thread thrd4(thrd_int, x + 10);

    std::cout << "Main threading waiting for other threads to finish\n";
    /**
     * std::thread::id get_id();
     * 
     * The get_id() function returns a value of std::thread::id identifying the thread associated with *this.
     * If there is no thread associated, default constructed std::thread::id is returned.
     * 
     */
    std::thread::id thrd1_ID = thrd1.get_id();
    std::thread::id thrd2_ID = thrd2.get_id();
    std::thread::id thrd3_ID = thrd3.get_id();
    std::thread::id thrd4_ID = thrd4.get_id();

    // stoud the thread ids
    std::cout << "\tThread1 ID :: " << thrd1_ID << "\n"
              << "\tThread2 ID :: " << thrd2_ID << "\n"
              << "\tThread2 ID :: " << thrd3_ID << "\n"
              << "\tThread4 ID :: " << thrd4_ID << "\n";

    /**
     * void join();
     * 
     * The function blocks the current thread until the thread identified by *this finishes its execution.
     * The completion of the thread identified by *this synchronizes with the corresponding successful 
     * return from join(). No synchronization is performed on *this itself. 
     * Concurrently calling join() on the same thread object from multiple threads constitutes 
     * a data race that results in undefined behavior. 
     * 
     */
 
    thrd1.join();
    thrd2.join();
    thrd3.join();
    thrd4.join();

    std::cout << "All Done!\n";
    return 0;
}