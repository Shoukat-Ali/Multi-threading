This is an attempt to show some examples of multi-threading C programs using pthread on Ubuntu. These examples are not meant to be exhaustive but hope that you'll find the range of programs useful/interesting. 

You'll find some instructions and explanations at the top of each program in the ***test*** directory where the ```main()``` function is defined.

# Examples

The examples include a basic demonstration of creating and managing multiple threads by passing arguments to threads and synchronizing their completion with the main/parent thread using using ```pthread_join()``` function.

There is a simple detached thread example where each thread releases its resources automatically upon termination. Note that detached threads are independent and cannot be joined. In other words, detached thread avoids blocking the **main/parent thread** so that threads run to completion independently.

One example demonstrates a multi-threaded increment operation on a (globally) shared variable with synchronization using a **mutex** lock to avoid race conditions.

One of the programs implements a multi-threaded simulation where each thread represents a dice roll. The threads and main/parent thread coordinate using **barriers** and **mutex** locks to determine the winner of each dice roll round.