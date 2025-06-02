./philo 5 800 200 200
5 philosophers run in parallel
Nobody dies
Each philosopher cycles through thinking → taking forks → eating → sleeping
============================================
./philo 1 500 200 200

Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.

1. ================= 
./philo 1 800 200 200
The philosopher should not eat and should die. -- TODO --

2. ===============
./philo 5 800 200 200
No philosopher should die. -- WORKS -- :)

3. =================
./philo 5 800 200 200 7
No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times. -- WORKS -- :)

4. ===================
./philo 4 410 200 200
No philosopher should die.  -- WORKS -- :)

5. ===============
./philo 4 310 200 100
One philosopher should die. -- WORKS -- :)

6. =================
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is
unacceptable.

7. ==================
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time,
that they don't steal forks, and so forth.

./philo 200 1000 100 100
All philosophers eat and sleep, no one dies.
