/**
 * 
 */

#ifndef PRODUCER_CONSUMER_HPP
#define PRODUCER_CONSUMER_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


#define ATTEMPTS 3


struct Consumer 
{
    // Unlike class, struct elements are by default public 
    int id;
    int basket;
    int attempts;
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic<bool> running;

    
    // Constructor
    Consumer(int id) : id(id), basket(0), attempts(ATTEMPTS), running(true) {
        // For now, empty
    }

    // Destructor
    ~Consumer() {
        id = 0;
        running = false;
        basket = 0;
        attempts = 0;
    }
};


struct Producer 
{
    // Unlike class, struct elements are by default public
    std::atomic<bool> running;


    Producer() : running(true) {
        // For now, empty
    }

    ~Producer() {
        running = false;
    }
};



class ProducerConsumer 
{
    private:
        std::vector<Producer> producers;
        std::vector<Consumer> consumers;
        std::vector<std::thread> Pthrds;
        std::vector<std::thread> Cthrds;

        void stop_all();

    public:
        ProducerConsumer(int numProd, int numCons);
        ~ProducerConsumer();
        void run();

};

#endif