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
Basket::Basket() : FoodAmount(0), stop(false) 
{
    // For now, empty

}

/**
 * 
 */
void Basket::add_food(unsigned int amount) 
{
    std::lock_guard<std::mutex> lock(mtx);
    if((amount + FoodAmount) <= UINT_MAX) {
        FoodAmount += amount;
        std::cout << "Added " << amount << " food.\n\t Total :: " << FoodAmount << std::endl;    
    }
    else {
        std::cout << "Food addition wasted due to overflow\n";
    }
    cv.notify_all();
}

/**
 * 
 */
void Basket::consume_food(unsigned int amount) 
{
    std::lock_guard<std::mutex> lock(mtx);
    if (FoodAmount >= amount) {
        FoodAmount -= amount;
        std::cout << "Consumed " << amount << " food.\n\t Remaining :: " << FoodAmount << std::endl;
    }
}

/**
 * 
 */
bool Basket::should_stop() 
{
    std::lock_guard<std::mutex> lock(mtx);
    return stop;
}

/**
 * 
 */
void Basket::signal_stop() 
{
    std::lock_guard<std::mutex> lock(mtx);
    stop = true;
    cv.notify_all();
}

/**
 * 
 */
unsigned int Basket::get_food_amount() 
{
    std::lock_guard<std::mutex> lock(mtx);
    return FoodAmount;
}


/**
 * 
 */
Basket::~Basket()
{
    FoodAmount = 0;
    stop = true;
}


/**
 * 
 */
Producer::Producer(Basket& bsk, unsigned int id) : basket(bsk), ProdID(id) 
{
    // For now, empty
}


/**
 * 
 */
void Producer::operator()() 
{   
    while(!basket.should_stop()) {
        std::srand(std::time(0)); // use current time as seed for pseudo-random integer generator
        std::cout << "Producer :: " << ProdID << " attempt\n"; 
        basket.add_food(std::rand() % MODULUS);
        std::this_thread::sleep_for(std::chrono::milliseconds(PRODUCER_REST));
    }
    std::cout << "Producer " << ProdID << " stopping production." << std::endl;
}


/**
 * 
 */
Consumer::Consumer(Basket& bsk, unsigned int id) : basket(bsk), ConrID(id), attempts(ATTEMPTS) 
{
    // For now, empty
}

/**
 * 
 */
void Consumer::operator()() 
{
    while(attempts > 0) {
        std::srand(std::time(0)); // use current time as seed for pseudo-random integer generator
        int food = std::rand() % MODULUS;
        if(basket.get_food_amount() > 0) {
            std::cout << "Consumer :: " << ConrID << ", attempt :: " << attempts << std::endl;
            basket.consume_food(food);
        }
        attempts--;
        std::this_thread::sleep_for(std::chrono::milliseconds(CONSUMER_REST));
    }
    std::cout << "Consumer " << ConrID << " has exhausted attempts." << std::endl;
}