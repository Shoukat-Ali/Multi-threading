/**
 * The program demonstrates thread synchronization using jobs as an example where std::mutex is used to protect 
 * shared resources. One job has access to shared and exclusive resources while other job can access shared resource only.
 * 
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_jobs_mutex.cpp ../source/jobs_mutex.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_jobs_mutex.cpp ../source/jobs_mutex.cpp -o prog
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

#include "../header/jobs_mutex.hpp"

int main(void)
{
    // sleep or wait time
    std::chrono::milliseconds mswait(10);

    JobMutex handler(mswait);
    handler.run();
    return 0;
}