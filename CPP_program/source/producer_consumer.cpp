/**
 * 
 */


#include <iostream>
#include "../header/producer_consumer.hpp"

ProducerConsumer::ProducerConsumer(int numProd, int numCons) 
{
    for (int i = 0; i < numProd; ++i) {
        /**
         * Appends a new element to the end of the container. The element is constructed 
         * through std::allocator_traits::construct, which typically uses placement-new 
         * to construct the element in-place at the location provided by the container.
         * 
         */
        producers.emplace_back();
    }

    for (int i = 0; i < numCons; ++i) {
        consumers.emplace_back(i);
    }
}


ProducerConsumer::~ProducerConsumer() 
{
    stop_all();
    for (auto& thrd : Pthrds) {
        if (thrd.joinable()) thrd.join();
    }

    for (auto& thrd : Cthrds) {
        if (thrd.joinable()) thrd.join();
    }
}


void ProducerConsumer::stop_all() 
{
    for (auto& prod : producers) {
        prod.running = false;
    }

    for (auto& cons : consumers) {
        cons.running = false;
        cons.cv.notify_one();
    }
}