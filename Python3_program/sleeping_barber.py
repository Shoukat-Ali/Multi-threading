'''

To execute the program, run the following command
    python3 sleeping_barber.py 
'''


import threading
import time
import random
import queue


class BarberShop:
    # Some configuration
    MAX_CHAIRS = 5         # Limiting the maximum number of wiating chairs
    HAIRCUT_TIME = (2, 5)   # Haircut time

    def __init__(self, num_chairs:int):
        if not isinstance(num_chairs, int) or num_chairs <= 0:
            raise ValueError("Number of chairs must be a positive integer")
        
        if num_chairs > self.MAX_CHAIRS:
            print(f"Maximum number of waiting chair is limited to :: {self.MAX_CHAIRS}")
            num_chairs = self.MAX_CHAIRS

        """
        The queue module implements multi-producer, multi-consumer queues. It is especially useful 
        in threaded programming when information must be exchanged safely between multiple threads. 
        The Queue class in this module implements all the required locking semantics.

        class queue.Queue(maxsize=0)
        Constructor for a FIFO queue. maxsize is an integer that sets the upperbound limit on the number 
        of items that can be placed in the queue. Insertion will block once this size has been reached, 
        until queue items are consumed. If maxsize is less than or equal to zero, the queue size is infinite.
        """
        self.waiting_chairs:queue.Queue = queue.Queue(maxsize=num_chairs)
        self.barber_lock = threading.Lock()
        self.customer_semaphore = threading.Semaphore(0)
        self.barber_semaphore = threading.Semaphore(0)
        """
        An event object is one of the simplest mechanisms for communication between threads: 
        one thread signals an event and other threads wait for it. An event object manages an 
        internal flag that can be set to true with the set() method and reset to false with 
        the clear() method. The wait() method blocks until the flag is true.
        """
        self.shop_open = threading.Event()
        self.shop_open.set()  # Shop is open
        
    
    def barber(self) -> None:
        """Barber thread that cuts hair or sleeps when no customers."""
        while self.shop_open.is_set():
            if self.waiting_chairs.empty():
                print("Barber is sleeping...")

            self.customer_semaphore.acquire()  # Wait for a customer
            
            if not self.shop_open.is_set():
                break
                
            try:
                customer = self.waiting_chairs.get_nowait()
                print(f"Barber is cutting hair for customer {customer}")
                time.sleep(random.uniform(self.HAIRCUT_TIME[0], self.HAIRCUT_TIME[1]))  # Simulate haircut time
                print(f"Barber finished cutting hair for customer {customer}")
                self.barber_semaphore.release()  # Signal customer haircut is done
            except queue.Empty:
                print("Error: Queue should not be empty when customer signals")
                
    
    def customer(self, customer_id:int) -> None:
        """Customer thread that tries to get a haircut."""
        print(f"Customer {customer_id} enters the shop")
        
        with self.barber_lock:
            if self.waiting_chairs.full():
                print(f"Customer {customer_id} leaves - no chairs available")
                return
                
            try:
                self.waiting_chairs.put(customer_id, timeout=5)
                print(f"Customer {customer_id} takes a seat")
                self.customer_semaphore.release()  # Wake up barber
            except queue.Full:
                print(f"Customer {customer_id} failed to join queue")
                return
                
        self.barber_semaphore.acquire()  # Wait for haircut to finish
        print(f"Customer {customer_id} leaves with a fresh haircut")

    
    def close_shop(self) -> None:
        """Close the barber shop safely."""
        self.shop_open.clear()
        self.customer_semaphore.release()  # Wake barber to check closure


def simulate_barber_shop(num_customers:int, num_chairs:int) -> None:
    """Simulation of Sleeping Barber problem"""
    if not isinstance(num_customers, int) or num_customers <= 0:
        raise ValueError("Number of customers must be a positive integer")
    
    shop = BarberShop(num_chairs)
    
    # Start barber thread
    barber_thread = threading.Thread(target=shop.barber, name="Barber")
    barber_thread.start()
    
    # Start customer threads
    customer_threads = []
    for i in range(num_customers):
        t = threading.Thread(target=shop.customer, args=(i+1,), name=f"Customer-{i+1}")
        customer_threads.append(t)
        t.start()
        time.sleep(random.uniform(0.5, 2))  # Random arrival time
    
    # Wait for all customers to finish
    for t in customer_threads:
        t.join(timeout=10)  # Prevent infinite blocking
    
    # Close shop and wait for barber
    shop.close_shop()
    barber_thread.join(timeout=5)
    
    print("Barber shop simulation completed")


def main() -> None:
    # Number of customers and chairs configruation
    NUM_CUSTOMERS = 5
    NUM_CHAIRS = 1
    try:
        simulate_barber_shop(NUM_CUSTOMERS, NUM_CHAIRS)
    except ValueError as e:
        print(f"Invalid input: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")


if __name__ == "__main__":
    main()