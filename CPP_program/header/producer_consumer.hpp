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
    int attempts;
    std::atomic<bool> running;

    Consumer(int id);
    ~Consumer();
};




struct Producer 
{
    // Unlike class, struct elements are by default public
    int id;
    std::atomic<bool> running;

    Producer(int id);
    ~Producer();
};




class ProducerConsumer 
{
    private:
        std::vector<Producer> prodrs;
        std::vector<Consumer> consrs;
        std::vector<std::thread> ProducerThrds;
        std::vector<std::thread> ConsumerThrds;
        
        // Shared resource/basket
        unsigned int SharedBasket;
        std::mutex BasketMutex;
        std::condition_variable BasketCV;
        std::atomic<bool> ConsumersDone;

    public:
        ProducerConsumer(int NumProdrs, int NumConsrs);
        ~ProducerConsumer();
        void run();

    // Private member functions
    private:
        void producer(int index);
        void consumer(int index);
        void stop_all();
        int random_int(int min, int max);

};

#endif