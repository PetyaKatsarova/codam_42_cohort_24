#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

/**
 *  1 second = 1000 ms
    1 millisecond = 1/1000 of a second
    500 ms = 0.5 seconds
    2000 ms = 2 seconds
    1 second = 1,000,000 microseconds

    struct timeval {
    time_t      tv_sec;   // the full seconds
    suseconds_t tv_usec;  // the left over microseconds
};
 */

unsigned long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL);
}

int main()
{
    unsigned long start = get_time_ms();
    while (get_time_ms() - start < 5000) // 5 sec
    {
        printf("tick\n");
        usleep(1000000); // 500 ms = .5 sec
    }
    return (0);
}