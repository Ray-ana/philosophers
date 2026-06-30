*This project has been created as part of the 42 curriculum by rzimaeva.*

# Description
Philosophers is a project that depicts a specific scene

    There are a chosen number of philosophers around a round table, each one of them have a fork and a meal.
    Each philosopher has to take their turns eating, sleeping and thinking while in the same simulation but they can't do more than one action at once.
    To eat, they will have to take their own fork and a second one belonging to another philosopher. Once they're done eating they just have to put them back down so the others can do the same as him.

To do so, we will have to use the concept of threads and therefore create a solid structure that can handle all of it without causing any data race.
The final goal of the project is that no philosopher should die before the end of the simulation.

# Instructions
Start by making the command

    Make

Then once everything is created,you can execute with the following script

    ./philo number_of_philosophers time_to_die  time_to_eat  time_to_sleep [number_of_times_each_philosopher_must_eat]

time_to_die : Time in ms after which a philosopher dies if they did not eat yet
time_to_eat : Duration of a meal in ms
time_to_sleep : Duration of sleeping time in ms
[number_of_times_each_philosopher_must_eat] : (optional) Program stops once every philosopher ate the number of times chosen

# Resources

I used AI to lead me toward the main ideas so I could be more organized and to do debug when it was too hard. The rest of it was mainly peer learning and the following links.

### Threads, Francois Schwarzentruber
https://perso.ens-lyon.fr/francois.schwarzentruber/teaching/l3-prog/book/c_thread.html

### C pthread, The Linux Craftsman
https://tala-informatique.fr/index.php?title=C_pthread

### Threads, mutex et programmation concurrente en C, Mia Combeau, 2 novembre 2022
https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/