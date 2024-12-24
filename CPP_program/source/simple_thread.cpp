/**
 * 
 */

#include <iostream>
#include "../header/simple_thread.hpp"

/**
 * 
 */
void thrd_int(int a)
{
    std::cout << "thrd_int(" << a << ")" << std::endl;
}


/**
 * 
 */
void thrd_float(float& b)
{
    std::cout << "thrd_float(" << b << ")\n";
}