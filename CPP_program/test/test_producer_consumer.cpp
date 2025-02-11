/**
 * This program demonstrates the producer-consumer example using multi-threading 
 * where there is a shared resource and mutex and condition variable are used to ensuer synchronization. 
 * Both producers and consumers operate independently where consumers have limited attempt. 
 * The main thread signals producers to stop once all consumers exhaust their attempts.
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
    Basket basket;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Producer threads
    for (int i = 1; i <= NUM_PRODUCER; ++i) {
        producers.emplace_back(Producer(basket, i));
    }

    // Consumer threads
    for (int i = 1; i <= NUM_CONSUMER; ++i) {
        consumers.emplace_back(Consumer(basket, i));
    }

    // Wait for all consumers to finish
    for (auto& c : consumers) {
        c.join();
    }

    // Signal producer to stop
    basket.signal_stop();

    // Wait for producers to finish
    for (auto& p : producers) {
        p.join();
    }

    std::cout << "Program terminating." << std::endl;
    return 0;
}