## Philosophers 42 Project

**Welcome, fellow philosophers!** 

This repository tackles the classic "Dining Philosophers" problem, a cornerstone of concurrent programming. Let's explore solutions to ensure these wise minds don't starve or deadlock over their delicious meals!

### The Problem

Imagine a round table with several philosophers. A bowl of spaghetti (or any food of your choice!) sits in the center, but there are only as many forks as philosophers. Each philosopher cycles through these states:

* **Thinking:** Pondering the mysteries of life, the universe, and everything.
* **Eating:** Savoring the meal (with two forks, of course!).
* **Sleeping:** Catching some well-deserved rest.

The challenge lies in preventing:

* **Deadlock:** A state where all philosophers hold one fork and wait for the other, unable to proceed.
* **Starvation:** A scenario where a philosopher waits indefinitely to eat because they can never get both forks.

### This Project

This project offers two approaches to the problem:

* **Mandatory Part:** Implements a solution using threads and mutexes.
* **Bonus Part (Optional):** Explores a different approach using processes and semaphores.

### Usage

**Compiling:**

Utilisez ce code avec précaution.

make all


**Running:**

Both programs (`philo` and `philo_bonus`) accept the following arguments:

* `number_of_philosophers`: The number of philosophers (and forks) at the table.
* `time_to_die`: The time (in milliseconds) a philosopher can wait to eat before starving.
* `time_to_eat`: The time (in milliseconds) it takes a philosopher to eat.
* `time_to_sleep`: The time (in milliseconds) a philosopher spends sleeping.
* `number_of_times_each_philosopher_must_eat` (Optional): The minimum number of meals each philosopher must have before the simulation ends (defaults to continuing until someone starves).

**Example:**

./philo 5 800 200 200 3


This runs the mandatory part (`philo`) with 5 philosophers, a time-to-die of 800ms, 200ms eating time, 200ms sleeping time, and a minimum of 3 meals per philosopher.

**Output:**

The program logs the philosophers' actions to the console, detailing:

* `<timestamp>`: The current time in milliseconds.
* `<philosopher (1 to number_of_philosophers)>`: The ID of the philosopher.
* `<action>`: The action being performed (thinking, eating, sleeping, taking a fork, putting down a fork, dying).

### Resources

* The Dining Philosophers Problem: https://en.wikipedia.org/wiki/Dining_philosophers_problem
* Mutexes: https://en.wikipedia.org/?title=Mutex&redirect=no
* Semaphores: https://en.wikipedia.org/wiki/Semaphore_%28programming%29

### Contributing

Feel free to fork this repository and share your solutions! We welcome pull requests with your improvements.

**Happy philosophizing and coding!**
