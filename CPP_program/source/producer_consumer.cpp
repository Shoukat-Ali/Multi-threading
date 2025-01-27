/**
 * 
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include "../header/producer_consumer.hpp"


#define PRODUCER_REST 200
#define CONSUMER_REST 100


/**
 * 
 */
Consumer::Consumer(int id) : id(id), attempts(ATTEMPTS), running(true) 
{
    if(id < 0) {
        std::cout << "Error, consumer id is negative integer\n";
    }
}


Consumer::~Consumer() 
{
    id = 0;
    attempts = 0;
    running = false;
}



/**
 * 
 */
Producer::Producer(int id) : id(id), running(true) 
{
    if(id < 0) {
        std::cout << "Error, producer id is negative integer\n";
    }
}


Producer::~Producer() 
{
    id = 0;
    running = false;
}


ProducerConsumer::ProducerConsumer(int numProd, int numCons) :  SharedBasket(0), ConsumersDone(false)
{
    for(int i = 0; i < numProd; ++i) {
        /**
         * Appends a new element to the end of the container. The element is constructed 
         * through std::allocator_traits::construct, which typically uses placement-new 
         * to construct the element in-place at the location provided by the container.
         * 
         */
        prodrs.emplace_back();
    }

    for(int i = 0; i < numCons; ++i) {
        consrs.emplace_back(i);
    }
}


ProducerConsumer::~ProducerConsumer() 
{
    stop_all();
    for(auto& thrd : ProducerThrds) {
        if(thrd.joinable()) 
            thrd.join();
    }

    for(auto& thrd : ConsumerThrds) {
        if(thrd.joinable()) 
            thrd.join();
    }
}



/**
 * 
 */
void ProducerConsumer::producer(int index) 
{
    auto& prod = prodrs[index];
    /**
     * std::atomic<T>::load()
     * 
     * Atomically loads and returns the current value of the atomic variable. 
     * Memory is affected according to the value of order.
     */
    while(prod.running.load() && !ConsumersDone.load()) {
        std::srand(std::time(nullptr)); // use current time as seed for pseudo-random integer generator
        int amount = std::rand();
        // if((SharedBasket.load() + amount) < std::numeric_limits<unsigned int>::max)
        if((SharedBasket.load() + amount) < UINT_MAX) {
            /**
             * Atomically replaces the current value with the result of arithmetic addition of the value and arg. 
             * That is, it performs atomic post-increment. The operation is a read-modify-write operation. 
             * Memory is affected according to the value of order.
             * 
             */
            unsigned int lastVal = SharedBasket.fetch_add(amount, std::memory_order_relaxed);
            /**
             * Using mutex for console output and conditional variable
             */
            std::lock_guard<std::mutex> lock(BasketMutex);
            std::cout << "Producer " << prod.id << " added " << amount << " food.\n\t Total :: " << lastVal + amount << std::endl;
            BasketCV.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(PRODUCER_REST));
    }
}



/**
 * 
 */
void ProducerConsumer::stop_all() 
{
    for (auto& prod : prodrs) {
        prod.running = false;
    }

    for (auto& cons : consrs) {
        cons.running = false;
    }
    BasketCV.notify_all();
}