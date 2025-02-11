This is an attempt to show some examples of multi-threading C++11 programs using class thread on Ubuntu. These examples are not meant to be exhaustive but hope that you'll find the range of programs useful/interesting. 

You'll find some instructions and explanations at the top of each program in the ***test*** directory where the ```main()``` function is defined.

# Examples

The examples include some basic demonstrations of creating and managing multiple threads using class thread i.e., **std::thread**.

There is a simple program to demonstrate multi-threading program using the class thread. Similarly, there is another short program that demonstrates the use of **atomic** templated for thread synchronization. 

One of the examples demonstrates a simple multi-threading program where class vector is used for threads. Moreover, threads are created usig normal and ```lambda``` functions.

In one of the examples, a simple multi-threading program is demonstrated using **std::mutex** to protect a shared data from simultaneous access by multiple threads.

One of the programs demonstrates thread synchronization using jobs as an example where **std::mutex** is used to protect shared resources. One job has access to shared and exclusive resources while other job can access shared resource only.

In one of the programs, the use of **condition variables** for thread synchronization is demonstrated. The condition variable allows multiple threads to wait for a specific condition to be met before proceeding.

One of the programs demonstrates the producer-consumer example where there is a shared resource and mutex and condition variable are used to ensuer synchronization. Both producers and consumers operate independently where consumers have limited attempt. The main/parent thread signals producers to stop once all consumers exhaust their attempts.