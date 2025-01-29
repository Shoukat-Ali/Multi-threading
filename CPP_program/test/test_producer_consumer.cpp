/**
 * This program demonstrates the use of condition variables for thread synchronization, 
 * allowing multiple threads to wait for a specific condition to be met before proceeding.
 * 
 * g++ -Wall -Werror -g3 -O3 -fsanitize=thread -std=c++11 test_producer_consumer.cpp ../source/producer_consumer.cpp -o prog
 * or
 * g++ -Wall -Werror -g3 -O3 -fsanitize=address -std=c++11 test_producer_consumer.cpp ../source/producer_consumer.cpp -o prog
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
#include "../header/producer_consumer.hpp"

#define NUM_PRODUCER 2
#define NUM_CONSUMER 5

int main(void)
{
    ProducerConsumer obj(NUM_PRODUCER, NUM_CONSUMER); 
    obj.run();
    return 0;
}