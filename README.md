# phliosphers
 [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

 <img alt="image" src="https://github.com/leebo155/philosphers/blob/main/img/phliosophers6.jpg">

 ## Introduction
 * This project is to recreate the dining philosophers problem in code.
 * One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
 * The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
 * There are also forks on the table. There are as many forks as philosophers.
 * Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
 * When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
 * Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
 * The program simulates the problem and outputs the changing philosophers states.   
  ```shall
  $> ./philo 5 50 30 40
  0 3 has taken a fork
  0 1 has taken a fork
  0 2 is thinking
  0 5 is thinking
  0 4 is thinking
  0 3 has taken a fork
  0 3 is eating
  0 1 has taken a fork
  0 1 is eating
  30 3 is sleeping
  30 1 is sleeping
  30 2 has taken a fork
  30 2 has taken a fork
  30 2 is eating
  30 4 has taken a fork
  30 4 has taken a fork
  30 4 is eating
  30 5 has taken a fork
  50 2 died
  ```

## Process
* Flowchart
  <img alt="image" src="https://github.com/leebo155/philosphers/blob/main/img/phliosophers5.jpg">
* To prevent deadlocks, adopt a non-circular waiting approach.
  <img alt="image" src="https://github.com/leebo155/philosphers/blob/main/img/phliosophers1.jpg">
* To avoid starvation as much as possible, philos briefly wait based on remaining lifespan.
  <img alt="image" src="https://github.com/leebo155/philosphers/blob/main/img/phliosophers2.jpg">
* Use mutex to prevent unintended data modification in data race.
  <img alt="image" src="https://github.com/leebo155/philosphers/blob/main/img/phliosophers3.jpg">
* The philo structure contains data that the philosopher threads will reference during the simulation. The rule structure contains data that the main thread will reference for termination conditions and is also shared among the philosopher threads.
  <img alt="image" src="https://github.com/leebo155/philosphers/blob/main/img/phliosophers4.jpg">

 ## Makefile
| Rules | Description |
| ----- | ----------- |
| all | Compile a program philo. |
| clean | Remove all the temporary generated files. |
| fclean | Remove all the generated files. |
| re | Remove all the generated files and compile a philo. |

 ## Usage
 ```shall
 $> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
 ```
 * Program can take the following arguments.   
   ◦ `number_of_philosophers`: The number of philosophers and also the number of forks.   
   ◦ `time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.   
   ◦ `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.   
   ◦ `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.   
   ◦ `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
