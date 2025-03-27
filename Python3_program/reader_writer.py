'''
'''

#!/usr/bin/env python3

import threading
import time
import random
from typing import Optional
import logging

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)


class SharedResource:
    """Class to manage shared resource with reader-writer synchronization
    Ensures multiple readers can read simultaneously but writers get exclusive access.
    """
    
    def __init__(self):
        # Semaphore for writer priority
        self.resource = threading.Semaphore(1)
        # Mutex for reader count
        self.reader_mutex = threading.Lock()
        # Track number of active readers
        self.reader_count = 0
        # Shared data
        self.data = 0


    def begin_write(self):
        """Acquire resources for writing"""
        self.resource.acquire()


    def end_write(self):
        """Release resources after writing"""
        self.resource.release()


    def begin_read(self):
        """Acquire resources for reading"""
        self.reader_mutex.acquire()
        try:
            self.reader_count += 1
            # First reader locks the write lock
            if self.reader_count == 1:
                self.resource.acquire()
        finally:
            self.reader_mutex.release()


    def end_read(self):
        """Release resources after reading"""
        self.reader_mutex.acquire()
        try:
            self.reader_count -= 1
            # Last reader releases the write lock
            if self.reader_count == 0:
                self.resource.release()
        finally:
            self.reader_mutex.release()


def writer(resource:SharedResource, writer_id:int) -> None:
    """Writer thread function"""
    # Write time configuration
    WRITE_TIME = (0.5, 3)

    try:
        while True:
            logger.info(f"Writer {writer_id} wants to write")
            resource.begin_write()
            try:
                new_value = random.randint(1, 100)
                logger.info(f"Writer {writer_id} writing value: {new_value}")
                resource.data = new_value
                time.sleep(random.uniform(WRITE_TIME[0], WRITE_TIME[1]))  # Simulate writing time
            except Exception as e:
                logger.error(f"Writer {writer_id} error during write: {str(e)}")
                raise
            finally:
                resource.end_write()
            time.sleep(random.uniform(1, 2))  # Wait before next write
            
    except Exception as e:
        logger.error(f"Writer {writer_id} failed: {str(e)}")


def reader(resource:SharedResource, reader_id:int) -> None:
    """Reader thread function"""
    # Write time configuration
    READ_TIME = (0.1, 1)

    try:
        while True:
            logger.info(f"Reader {reader_id} wants to read")
            resource.begin_read()
            try:
                logger.info(f"Reader {reader_id} read value: {resource.data}")
                time.sleep(random.uniform(READ_TIME[0], READ_TIME[1]))  # Simulate reading time
            except Exception as e:
                logger.error(f"Reader {reader_id} error during read: {str(e)}")
                raise
            finally:
                resource.end_read()
            time.sleep(random.uniform(0.5, 1.5))  # Wait before next read
            
    except Exception as e:
        logger.error(f"Reader {reader_id} failed: {str(e)}")


def main():
    """Main function to set up and run the simulation"""
    # Simulation time in sec
    SIMULATION = 15

    try:
        # Input validation
        num_readers = max(1, int(input("Enter number of readers (min 1): ")))
        num_writers = max(1, int(input("Enter number of writers (min 1): ")))
        
        # Create shared resource
        resource = SharedResource()
        
        # Create and start reader threads
        readers = [threading.Thread(target=reader, args=(resource, i + 1),
                                    name=f"Reader-{i + 1}", daemon=True)
                                    for i in range(num_readers)]
        
        # Create and start writer threads
        writers = [threading.Thread(target=writer, args=(resource, i + 1),
                                    name=f"Writer-{i + 1}", daemon=True)
                                    for i in range(num_writers)]
        
        # Start all threads
        for thread in readers + writers:
            thread.start()
            
        # Run simulation for SIMULATION seconds
        time.sleep(SIMULATION)
        
        logger.info("Simulation completed")
        
    except ValueError as e:
        logger.error(f"Invalid input: {str(e)}")
    except Exception as e:
        logger.error(f"Simulation failed: {str(e)}")


if __name__ == "__main__":
    main()