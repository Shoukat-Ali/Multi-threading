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


/**
 * 
 */
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


/**
 * 
 */
Producer::~Producer() 
{
    id = 0;
    running = false;
}


/**
 * 
 */
ProducerConsumer::ProducerConsumer(int numProd, int numCons) :  SharedBasket(0), ConsumersDone(false)
{
    for(int i = 0; i < numProd; ++i) {
        /**
         * Appends a new element to the end of the container. The element is constructed 
         * through std::allocator_traits::construct, which typically uses placement-new 
         * to construct the element in-place at the location provided by the container.
         * 
         */
        prodrs.emplace_back(i);
        // prodrs.push_back(Producer(i));
    }

    for(int i = 0; i < numCons; ++i) {
        consrs.emplace_back(i);
        // consrs.push_back(Consumer(i));
    }
}


/**
 * 
 */
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
            std::cout   << "Producer " << prod.id << " added " << amount << " food.\n\t Total :: " 
                        << lastVal + amount << std::endl;
            BasketCV.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(PRODUCER_REST));
    }
}


/**
 * 
 */
void ProducerConsumer::consumer(int index)
{
    auto& cons = consrs[index];
    if(cons.attempts > ATTEMPTS) {
        // TODO: throw exception
        std::cout << "Error, consumer attempts is more than allowed attempt\n";
        return;
    }
    while(cons.running.load() && cons.attempts > 0) {
        std::srand(std::time(nullptr)); // use current time as seed for pseudo-random integer generator
        int amount = std::rand();
        std::unique_lock<std::mutex> lock(BasketMutex);
        BasketCV.wait(lock, [this, &cons] { 
            return SharedBasket.load(std::memory_order_relaxed) > 0 ; 
        });
        /**
         * std::memory_order_relaxed 
         * Relaxed operation: there are no synchronization or ordering constraints 
         * imposed on other reads or writes, only this operation's atomicity is guaranteed
         */
        if(((unsigned int) amount) <= SharedBasket.load(std::memory_order_relaxed)) {
            /**
             * Atomically replaces the current value with the result of arithmetic subtraction of the 
             * value and arg. That is, it performs atomic post-decrement. 
             * The operation is read-modify-write operation.
             * 
             */
            unsigned int lastVal = SharedBasket.fetch_sub(amount, std::memory_order_relaxed);
            --cons.attempts;
            std::cout   << "Consumer " << cons.id << " consumed " << amount << " food.\n\t Remaining :: " 
                        << (lastVal - amount) << std::endl;
        } 
        // Better to release lock before going to rest/wait
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(CONSUMER_REST));
    }

}


/**
 * 
 */
void ProducerConsumer::stop_all() 
{
    for(auto& prod : prodrs) {
        prod.running = false;
    }

    for(auto& cons : consrs) {
        cons.running = false;
    }
    BasketCV.notify_all();
}


/**
 * 
 */
void ProducerConsumer::run() 
{
    for(unsigned int i = 0; i < prodrs.size(); ++i) {
        ProducerThrds.emplace_back(&ProducerConsumer::producer, this, i);
    }

    for(unsigned int i = 0; i < consrs.size(); ++i) {
        ConsumerThrds.emplace_back(&ProducerConsumer::consumer, this, i);
    }

    for(auto& thrd : ConsumerThrds) {
        thrd.join();
    }

    ConsumersDone.store(true);
    BasketCV.notify_all();
    
    for(auto& thrd : ProducerThrds) {
        thrd.join();
    }
    std::cout << "All consumers have exhausted their attempts. Program terminating." << std::endl;
}