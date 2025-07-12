# Philosophers - 42 Project

## Overview

The Philosophers project is a classic computer science problem that introduces students to the fundamentals of concurrent programming, threading, and synchronization mechanisms. This project simulates the famous "Dining Philosophers Problem" originally formulated by Edsger Dijkstra.

## The Problem

The dining philosophers problem consists of philosophers sitting at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. However, a philosopher can only eat when they have both left and right forks. Each fork can be held by only one philosopher at a time.

## Project Requirements

- **N philosophers** sit at a round table
- **N forks** (one between each pair of philosophers)
- Philosophers alternate between **eating**, **sleeping**, and **thinking**
- A philosopher needs **both forks** to eat
- When done eating, philosopher puts down forks and sleeps
- When done sleeping, philosopher thinks
- The simulation stops when a philosopher **dies of starvation**

### Program Arguments
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Key Concepts Learned

### 1. Threads

**What are threads?**
Threads are lightweight processes that allow concurrent execution within a single program. Each philosopher in our simulation runs as a separate thread.

**Implementation:**
- Each philosopher is represented by a thread using `pthread_create()`
- All threads share the same memory space
- Threads can run simultaneously on multi-core systems

**Key Functions:**
- `pthread_create()` - Create a new thread
- `pthread_join()` - Wait for thread completion
- `pthread_detach()` - Detach thread for automatic cleanup

### 2. Mutexes (Mutual Exclusion)

**What are mutexes?**
Mutexes are synchronization primitives that ensure only one thread can access a shared resource at a time. In our project, each fork is protected by a mutex.

**Why we need them:**
- Prevent race conditions when accessing shared resources
- Ensure data integrity
- Coordinate access to forks between philosophers

**Implementation:**
- Each fork has its own mutex
- Philosophers must lock both fork mutexes before eating
- Mutexes are unlocked after eating

**Key Functions:**
- `pthread_mutex_init()` - Initialize mutex
- `pthread_mutex_lock()` - Lock mutex (blocking)
- `pthread_mutex_unlock()` - Unlock mutex
- `pthread_mutex_destroy()` - Destroy mutex

### 3. Race Conditions

**What are race conditions?**
Race conditions occur when multiple threads access shared data concurrently, and the final result depends on the timing of their execution.

**Examples in Philosophers:**
- Multiple philosophers trying to grab the same fork simultaneously
- Checking if a philosopher should die while another thread is updating the last meal time
- Printing messages without proper synchronization

**Prevention:**
- Use mutexes to protect shared data
- Implement proper locking mechanisms
- Ensure atomic operations for critical sections

### 4. Deadlocks

**What is a deadlock?**
A deadlock occurs when two or more threads are blocked forever, waiting for each other to release resources.

**Classic Deadlock Scenario:**
1. Philosopher 1 picks up fork A, waits for fork B
2. Philosopher 2 picks up fork B, waits for fork A
3. Both philosophers wait forever

**Prevention Strategies:**
- **Ordering**: Always acquire forks in the same order (e.g., lower-numbered fork first)
- **Timeout**: Use timed locks to avoid infinite waiting
- **Odd/Even Strategy**: Odd philosophers pick left fork first, even philosophers pick right fork first

### 5. Data Races

**What are data races?**
Data races occur when multiple threads access the same memory location concurrently, and at least one access is a write operation, without proper synchronization.

**Common Examples:**
- Reading/writing philosopher's last meal time
- Checking death status
- Updating shared counters

**Prevention:**
- Protect all shared data with mutexes
- Use atomic operations where appropriate
- Implement proper synchronization protocols

## Implementation Strategy

### Structure Design
```c
typedef struct s_data                                                                                     
{
 	int philo_number;
       	int time_t_die;
	int time_t_eat;
        int time_t_sleep;                                                     
        int must_eat_times;                                                   
        long long       start_time;                                                               
        int             simulation_end;                                                   
        pthread_t       threads[MAX_NUMBER];                                                      
        pthread_mutex_t forks[MAX_NUMBER];                                                                
        pthread_mutex_t simulation;                                                                       
}  t_data;                                                           
        
typedef struct s_philo
{               
        int              id;                                                               
        int              num_meals;                                                        
        time_t         	 last_meal;                                                                
        pthread_mutex_t *right_fork;                                                                      
        pthread_mutex_t *left_fork;
        pthread_mutex_t stats;
        t_data          *data;                                                                    
}      t_philo;

```

### Synchronization Approach

1. **Fork Management**: Each fork is protected by its own mutex
2. **Death Checking**: A separate monitoring thread or periodic checks
3. **Printing**: All output is synchronized with a print mutex
4. **Death Flag**: Protected by a death mutex to prevent race conditions

### Timing Considerations

- Use `gettimeofday()` for precise timing
- Calculate elapsed time carefully
- Account for execution overhead
- Implement accurate sleeping mechanisms

## Common Pitfalls and Solutions

### Memory Management
- Always initialize mutexes before use
- Properly destroy mutexes to prevent memory leaks
- Handle thread creation failures

### Timing Issues
- Avoid busy waiting (use `usleep()` for short delays)
- Ensure precise death detection
- Handle edge cases in timing calculations

### Thread Safety
- Never access shared data without proper synchronization
- Be consistent with locking order
- Minimize time spent holding locks

## Testing and Debugging

### Test Cases
- Single philosopher (should die)
- Two philosophers (edge case)
- Large numbers of philosophers
- Very short time limits
- Very long time limits

## Key Takeaways

This project teaches essential concurrent programming concepts:

1. **Thread Management**: Creating, managing, and synchronizing multiple threads
2. **Mutex Usage**: Protecting shared resources and preventing race conditions
3. **Deadlock Prevention**: Understanding and avoiding common deadlock scenarios
4. **Race Condition Awareness**: Identifying and preventing data races
5. **Timing Precision**: Implementing accurate timing mechanisms
6. **Resource Management**: Proper cleanup and memory management in multi-threaded environments

The Philosophers project provides a solid foundation for understanding concurrent programming challenges that are fundamental in systems programming, operating systems, and multi-threaded applications.

## Compilation

```bash
gcc -Wall -Wextra -Werror -pthread -o philo *.c
```
