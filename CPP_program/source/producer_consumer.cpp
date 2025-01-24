/**
 * 
 */


#include <iostream>
#include "../header/producer_consumer.hpp"



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
    for (int i = 0; i < numProd; ++i) {
        /**
         * Appends a new element to the end of the container. The element is constructed 
         * through std::allocator_traits::construct, which typically uses placement-new 
         * to construct the element in-place at the location provided by the container.
         * 
         */
        prodrs.emplace_back();
    }

    for (int i = 0; i < numCons; ++i) {
        consrs.emplace_back(i);
    }
}


ProducerConsumer::~ProducerConsumer() 
{
    stop_all();
    for (auto& thrd : ProducerThrds) {
        if (thrd.joinable()) 
            thrd.join();
    }

    for (auto& thrd : ConsumerThrds) {
        if (thrd.joinable()) 
            thrd.join();
    }
}



/**
 * 
 */
void ProducerConsumer::producer(int index) 
{
    auto& prod = prodrs[index];
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