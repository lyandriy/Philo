# Philosophers

## Project Description

The `philosophers` project is part of the School 42 curriculum, designed to enhance your understanding of concurrent programming, process synchronization, and thread management. The goal of this project is to solve the classic Dining Philosophers problem, where multiple philosophers alternately think, eat, and try to avoid starvation and deadlock.

## What It Does

The `philosophers` program simulates the Dining Philosophers problem using threads and mutexes. Each philosopher alternates between thinking, eating, and sleeping, ensuring they do not starve and avoiding deadlock.

## Implementation Details

- **Language**: The project is implemented in C.
- **Concurrency**:
  - **Threads**: Each philosopher is represented by a separate thread.
  - **Mutexes**: Used to manage access to shared resources (forks).
- **Philosopher Actions**:
  - **Thinking**: The philosopher is thinking.
  - **Eating**: The philosopher picks up two forks (mutexes) and eats.
  - **Sleeping**: The philosopher puts down the forks and sleeps.
- **Headers**:
  - `#include <pthread.h>`: For thread creation and management.
  - `#include <stdlib.h>`: For memory management.
  - `#include <unistd.h>`: For standard input/output.
  - `#include <stdio.h>`: For standard I/O functions.
  - `#include <sys/time.h>`: For time management.

### How It Works

1. **Initializing Philosophers and Forks**:
   - Creates a thread for each philosopher.
   - Initializes mutexes for each fork.

2. **Philosopher Life Cycle**:
   - Each philosopher thread runs a loop where the philosopher alternates between thinking, eating, and sleeping.
   - Before eating, a philosopher must pick up the fork to their left and the fork to their right (in that order to prevent deadlock).
   - After eating, the philosopher puts down both forks and then sleeps.

3. **Synchronization**:
   - Mutexes ensure that only one philosopher can hold a fork at a time.
   - Proper use of mutexes prevents race conditions and deadlock.

4. **Time Management**:
   - Uses `gettimeofday` to track the time each philosopher spends in each state.
   - Ensures philosophers do not starve by checking the time since their last meal.

5. **Command-line Arguments**:
   - The program takes several command-line arguments to configure the simulation:
     - Number of philosophers.
     - Time to die (in milliseconds).
     - Time to eat (in milliseconds).
     - Time to sleep (in milliseconds).
     - [Optional] Number of times each philosopher must eat.

### Example Usage

To run the `philosophers` program, compile the project using the provided Makefile and then execute the program with the required arguments:

```sh
make
./philo 5 800 200 200
```
This example simulates 5 philosophers, where each philosopher dies if they do not eat for 800 milliseconds, takes 200 milliseconds to eat, and 200 milliseconds to sleep.

Example Output
The program will output the actions of each philosopher, for example:

```sh
timestamp_in_ms X has taken a fork
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
```
- timestamp_in_ms is the time elapsed since the start of the simulation.
- X is the philosopher number.

This project provides a practical exercise in concurrent programming, emphasizing the importance of thread management and synchronization techniques to solve complex problems in computer science.
