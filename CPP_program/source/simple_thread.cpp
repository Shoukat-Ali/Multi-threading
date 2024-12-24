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
    std::cout << "\tthrd_int(" << a << ")" << std::endl;
}


/**
 * 
 */
void thrd_float(float& b)
{
    std::cout << "\tthrd_float(" << b << ")\n";
}