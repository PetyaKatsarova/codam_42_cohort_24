Each philosopher cycles through thinking → taking forks → eating → sleeping
============================================

!!NB!! test with: 
valgrind --tool=drd ./philo 5 410 200 200

=============================================================

./philo 5 800 200 200 7 | grep "eating" | wc -l

returns 35: 5 philos eat 5 times = 35
==============================================

Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.

1. ================= 
./philo 1 800 200 200
The philosopher should not eat and should die. -- TODO --

2. ===============
./philo 5 800 200 200
No philosopher should die. -- WORKS -- :)

3. =================
./philo 5 800 200 200 7 | grep "eating" | wc -l
No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times returns 35. -- WORKS -- :)

4. ===================
./philo 4 410 200 200
No philosopher should die.  -- WORKS -- :) dies...

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
=====================================

./philo 200 1000 100 100 -- works :)
./philo 3 610 200 200 -- works :)
./philo 200 2000 200 200 -- works ;)
./philo 199 2000 200 200 -- works ;)
// todo: tsts for die
./philo 3 320 200 100

===============================
works:
./philo 30 410 200 200
./philo 50 610 200 200
./philo 
=================================
time_to_die ≥ time_to_eat + time_to_sleep + margin

For 3 philosophers:

time_to_eat = 200 ms

time_to_sleep = ~100–200 ms

margin = 10–50 ms (for thread delays)
-------------------------------------
time_to_die ≈ 200 (eat) + 100 (sleep) + 10 (margin) = 310 ms
Anything below 310ms may cause random deaths due to:

OS thread scheduling delays

minor CPU lag

mutex wait times


=================================
!!!!!
time_to_die ≥ time_to_eat + time_to_sleep + scheduling_overhead
!!!!!

should pass:
./philo 199 310 150 150
5 310 100 200 
