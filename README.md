*This project has been created as part of the 42 curriculum by fgreiff.*

# 🍝 Philosophers

> *I never thought philosophy would be so deadly.*

A simulation of the classic **Dining Philosophers Problem**, implemented in C using **POSIX threads** and **mutexes**. The goal is to make philosophers eat, think, and sleep without any of them starving — and without any data races.

---

## Description

One or more philosophers sit around a round table with a large bowl of spaghetti in the middle. There are as many forks as philosophers, each placed between two adjacent philosophers.

A philosopher must pick up **both** the fork to their left and the fork to their right before eating. When done eating, they put the forks back and go to sleep. Once awake, they think again. The simulation ends when a philosopher dies of starvation — or, if a meal count is specified, when every philosopher has eaten enough times.

**The constraints:**
- Philosophers cannot communicate with each other.
- Philosophers do not know if another philosopher is about to die.
- No global variables allowed.
- No data races allowed.
- Each philosopher runs as a **separate thread**.
- Each fork is protected by a **mutex** to prevent duplication.

---

## Instructions

### Compilation

```bash
cd philo
make
```

### Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time after which a philosopher dies if they haven't started eating |
| `time_to_eat` (ms) | Time it takes to eat (holds 2 forks during this time) |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops once all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, die at 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same but stops after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Edge case: 1 philosopher (can never eat, will die)
./philo 1 800 200 200
```

### Log format

Every state change is printed to standard output in the following format:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

A death message is guaranteed to appear within **10 ms** of the actual death event.

### Cleanup

```bash
make clean   # Remove object files
make fclean  # Remove object files and binary
make re      # Recompile from scratch
```

---

## Resources

### The Dining Philosophers Problem
- [Wikipedia — Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### Concurrency & Data Races
- [Helgrind: a thread error detector (Valgrind)](https://valgrind.org/docs/manual/hg-manual.html)
- [ThreadSanitizer (clang/gcc)](https://clang.llvm.org/docs/ThreadSanitizer.html) — useful for detecting data races during development

