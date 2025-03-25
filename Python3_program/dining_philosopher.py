'''
'''

import threading
import time
import random


class DiningPhilosophers:
    # Eating and thinking time configuration for philosopher
    EATING_TIME = (1, 3)  # Range of time for eating
    THINKING_TIME = (2, 5)  # Range of time for thinking

    def __init__(self, num_philosophers:int, max_meals:int):
        if num_philosophers < 2:
            raise ValueError("Number of philosophers must be at least 2")
        
        self.num_philosophers = num_philosophers
        self.max_meals = max_meals
        self.forks = [threading.Lock() for e in range(num_philosophers)]
        self.meals_eaten = [0] * num_philosophers
        self.running = [True] * num_philosophers
        self.threads = []


    def philosopher(self, id: int):
        """Single method handling philosopher behavior"""
        left_fork = self.forks[id]
        right_fork = self.forks[(id + 1) % self.num_philosophers]
        
        while self.running[id] and self.meals_eaten[id] < self.max_meals:
            # Think
            print(f"Philosopher-{id} is thinking...")
            time.sleep(random.uniform(self.THINKING_TIME[0], self.THINKING_TIME[1]))
            
            # Eat
            try:
                with left_fork:
                    print(f"Philosopher-{id} picked up left fork")
                    with right_fork:
                        print(f"Philosopher-{id} picked up right fork")
                        self.meals_eaten[id] += 1
                        print(f"Philosopher-{id} is eating... (Meal #{self.meals_eaten[id]})")
                        time.sleep(random.uniform(self.EATING_TIME[0], self.EATING_TIME[1]))
                    print(f"Philosopher-{id} put down right fork")
                print(f"Philosopher-{id} put down left fork")
            except threading.ThreadError as e:
                print(f"Thread error for Philosopher-{id}: {e}")


    def start_dining(self):
        """Start all philosopher threads"""
        try:
            for i in range(self.num_philosophers):
                thread = threading.Thread(target=self.philosopher, args=(i,))
                self.threads.append(thread)
                thread.start()
            
            for thread in self.threads:
                thread.join()
                
            print("All philosophers have finished dining!")
            
        except Exception as e:
            print(f"Error during dining: {e}")
            self.cleanup()


    def cleanup(self):
        """Stop all philosophers"""
        for i in range(self.num_philosophers):
            self.running[i] = False
        for thread in self.threads:
            thread.join()


def main():
    # Number of philosopher and maximum meal per philosopher configuration
    NUM_PHILOSOPHERS = 7
    MAX_MEALS = 3

    try:
        dining = DiningPhilosophers(NUM_PHILOSOPHERS, MAX_MEALS)
        dining.start_dining()
    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    main()