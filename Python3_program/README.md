This is an attempt to show some examples of multi-threading programs using threading module in Python3 on Ubuntu. These examples are not meant to be exhaustive but hope that you'll find the range of programs useful/interesting. 

You'll find some instructions and explanations at the top of each program.

# Examples

There is a simple multi-threaded example where arguments are passed to some threads. The threads are started and stopped using ```thread.start()``` and ```thread.join()```, respectively.

In one of the examples, the program demonstrates the classic producer-consumer problem using a class with synchronized resource sharing in multi-threading. To prevent deadlock and ensuring synchronization, ```threading.Semaphore()``` and ```threading.Lock()``` are used, respectively. Since the program runs indefinitely, therefore, graceful shutdown is performed via signal handling **(Ctrl+C/SIGTERM)**.

One of the programs implements the dining philosopher problem as a multi-threaded solution. Each philosopher runs in its own thread, alternating between thinking and eating. The deadlock is prevented by consistently ordering fork acquisition and ensures thread safety 
through proper synchronization using ```threading.Lock()```.

One example demonstrates the Sleeping Barber problem. The simulation uses ```threading.Lock()```, ```threading.Semaphore()```, and ```queue.Queue()``` to manage concurrency, ensuring thread safety and preventing race conditions.

One example illustrates the Reader-Writer problem with proper synchronization using threading primitives such as ```threading.Lock()``` and ```threading.Semaphore()```.