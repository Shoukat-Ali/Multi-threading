'''
A simple multi-threading program using the threading module in Python3.

The threading module allows multiple threads of execution to take place in a Python program.
While threads may appear to run simultaneously, only one thread can be executed at a time. 
This is enforced by Python’s global interpreter lock.

Threading is helpful when working with tasks that are I/O bound.
'''

import threading
import time

class ThreadManager:
    MAX_LEN = 55  # For testing by restricting maximum string length
    ERR_THRD_CREATE = 1
    ERR_THRD_JOIN = 2
    ERR_INVALID_ARG = 3
    
    
    def __init__(self):
        self.threads = []
    

    def my_thread1(self):
        """Thread function without arguments."""
        print("Starting thread")
        time.sleep(2)     #sleep for 2 sec
        print("Ending thread")
    

    def my_thread2(self, arg=None):
        """Thread function with an optional argument."""
        try:
            if arg is None:
                msg = "No argument provided"
            elif isinstance(arg, str):
                msg = arg[:self.MAX_LEN]  # Truncate if too long
            else:
                print("Error, Invalid argument type")
                return self.ERR_INVALID_ARG
            
            print(f"Starting thread with arg ({msg})")
            time.sleep(0.5)   # sleep for 0.5 sec
            print(f"Ending thread with arg ({msg})")
        except Exception as e:
            print(f"Error in my_thread2: {e}")
    

    def create_threads(self):
        """Create and start threads."""
        try:
            """class threading.Thread(group=None, target=None, name=None, args=(), kwargs={}, *, daemon=None)
            The constructor should always be called with keyword arguments.
            
            The argument target is the callable object to be invoked by the run() method. 
            Defaults to None, meaning nothing is called.

            The argument args is a list or tuple of arguments for the target invocation. Defaults to (). 
            """
            t1 = threading.Thread(target=self.my_thread1)
            t2 = threading.Thread(target=self.my_thread2, args=("Testing argument",))
            t3 = threading.Thread(target=self.my_thread2, args=(None,))  # Explicitly passing None
            t4 = threading.Thread(target=self.my_thread2, args=[123,])  # Invalid argument test case
            
            self.threads.extend([t1, t2, t3, t4])
            
            for thread in self.threads:
                """Start the thread’s activity.
                It must be called at most once per thread object. It arranges for the object’s run() method 
                to be invoked in a separate thread of control.

                This method will raise a RuntimeError if called more than once on the same thread object.
                """
                thread.start()
        except Exception as e:
            print(f"Failed to create/start threads: {e}")
            return self.ERR_THRD_CREATE
        
        return 0
    

    def join_threads(self):
        """Wait for threads to terminate."""
        try:
            for thread in self.threads:
                """join(timeout=None)
                Wait until the thread terminates. This blocks the calling thread until the thread whose join() 
                method is called terminates - either normally or through an unhandled exception - or until 
                the optional timeout occurs.
                
                When the timeout argument is present and not None, it should be a floating-point number specifying 
                a timeout for the operation in seconds (or fractions). As join() always returns None, you must call 
                is_alive() after join() to decide whether a timeout happened.

                join() raises a RuntimeError if an attempt is made to join the current thread as that would cause a deadlock. 
                It is also an error to join() a thread before it has been started and attempts to do so raise the same exception.
                """
                thread.join()
        except Exception as e:
            print(f"Failed to join threads: {e}")
            return self.ERR_THRD_JOIN
        
        return 0
    
    def run(self):
        """Execute thread operations."""
        if self.create_threads() == self.ERR_THRD_CREATE:
            return self.ERR_THRD_CREATE
        return self.join_threads()


if __name__ == "__main__":
    manager = ThreadManager()
    exit(manager.run())
