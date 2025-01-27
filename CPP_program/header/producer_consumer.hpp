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
    /**
     * Each instantiation and full specialization of the std::atomic template 
     * defines an atomic type. If one thread writes to an atomic object while 
     * another thread reads from it, the behavior is well-defined.
     * 
     * std::atomic is neither copyable nor movable. 
     */
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
        std::atomic<unsigned int> SharedBasket;
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