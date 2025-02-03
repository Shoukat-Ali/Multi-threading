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
#define MODULUS 1000

/**
 * 
 */
class Basket {
    private:
        std::mutex mtx;
        std::condition_variable cv;
        unsigned int FoodAmount;
        bool stop;

    public:
        Basket();
        ~Basket();
        void add_food(unsigned int amount);
        void consume_food(unsigned int amount);
        bool should_stop();
        void signal_stop();
        unsigned int get_food_amount();
};

/**
 * 
 */
class Producer {
    private:
        Basket& basket;
        unsigned int ProdID;
        
    public:
        Producer(Basket& bsk, unsigned int id);
        void operator()();
};


/**
 * 
 */
class Consumer {
    private:
        Basket& basket;
        unsigned int ConrID;
        unsigned int attempts;
        
    public:
        Consumer(Basket& bsk, unsigned int id);
        void operator()();
};



#endif