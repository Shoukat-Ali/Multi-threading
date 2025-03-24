'''
This program is an attempt to demonstrate the classic producer-consumer problem 
using a class with synchronized resource sharing in multi-threading. Some of the key features are;

    1. Multiple producer/consumer threads
    2. Semaphore-controlled capacity with bounded buffer
    3. Graceful shutdown via signal handling (Ctrl+C/SIGTERM)
    4. Daemon threads for clean process exit
    5. Deadlock prevention through semaphore timeouts

'''


import threading
import time
import random
import signal



class ProducerConsumer:
    """Thread-safe producer-consumer implementation with bounded buffer"""
    
    #Configuration constants
    SEMAPHORE_LIMIT = 10
    ARRAY_BOUND = 10
    NUM_THREADS = 5
    PRODUCTION_BOUND = 100
    
    def __init__(self):
        """Initialize shared resources and synchronization primitives"""
        self.buffer = [0] * self.ARRAY_BOUND
        self.count = 0
        self.sem_empty = threading.Semaphore(self.SEMAPHORE_LIMIT)
        self.sem_full = threading.Semaphore(0)
        self.buffer_lock = threading.Lock()
        self.running = False
        self.threads = []
        
        #Set up graceful shutdown handler
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)


    def _signal_handler(self, signum, frame):
        """Handle termination signals for clean shutdown"""
        print(f"\nReceived signal {signum}, terminating...")
        self.stop()


    def _producer(self):
        """Producer thread workflow"""
        while self.running:
            try:
                amount = random.randint(0, self.PRODUCTION_BOUND - 1)
                time.sleep(1)  # Simulate production time
                
                if self.sem_empty.acquire(timeout=0.5):
                    with self.buffer_lock:
                        if self.count < self.ARRAY_BOUND:
                            self.buffer[self.count] = amount
                            self.count += 1
                            self._log_production(amount)
                            
                    self.sem_full.release()
                    
            except Exception as e:
                print(f"Producer error: {str(e)}")
                break


    def _consumer(self):
        """Consumer thread workflow"""
        while self.running:
            try:
                if self.sem_full.acquire(timeout=0.5):
                    with self.buffer_lock:
                        if self.count > 0:
                            self.count -= 1
                            amount = self.buffer[self.count]
                            self._log_consumption(amount)
                            
                    self.sem_empty.release()
                    time.sleep(8)  # Simulate consumption time
                    
            except Exception as e:
                print(f"Consumer error: {str(e)}")
                break


    def _log_production(self, amount):
        """Thread-safe logging for production events"""
        print(f"Food Produced (id: {threading.get_ident()}) :: {amount:3d}")


    def _log_consumption(self, amount):
        """Thread-safe logging for consumption events"""
        print(f"Food Consumed (id: {threading.get_ident()}) :: {amount:3d}")


    def start(self):
        """Start producer and consumer threads"""
        if self.running:
            return  # Prevent multiple starts
            
        self.running = True
        
        # Create thread pool
        for i in range(self.NUM_THREADS):
            if i % 2 == 0:
                thread = threading.Thread(target=self._consumer,
                                          name=f"Worker-{i} :: Consumer")
            else:
                thread = threading.Thread(target=self._producer,
                                          name=f"Worker-{i} :: Producer")
            
            thread.daemon = True  # Auto-terminate when main exits
            self.threads.append(thread)
            thread.start()


    def stop(self):
        """Stop all threads and clean up resources"""
        if not self.running:
            return
            
        self.running = False
        
        # Wait for threads to finish current operations
        for thread in self.threads:
            if thread.is_alive():
                thread.join(timeout=2)
                if thread.is_alive():
                    print(f"Still alive {thread.name}") 
                
        print("\nSystem shutdown completed")



if __name__ == "__main__":
    thrdmanager = ProducerConsumer()
    thrdmanager.start()
    
    try:
        while True:  # Keep main thread alive
            time.sleep(0.1)
            if not thrdmanager.running:
                print("Thread Manager is not running")
                exit(0)
    except KeyboardInterrupt:
        thrdmanager.stop()
    