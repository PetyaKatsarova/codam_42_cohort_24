#include <stdio.h> 
#include <signal.h> 
#include <stdlib.h>
#include <unistd.h> // getpid()

void signalHandler(int sig)
{
    printf("caught sig %d\n", sig);
    exit(sig);
}

void signalHandler2(int sig)
{
    printf("interrupt handled: %d\n", sig);
    exit(sig);
}

void handle_signal(int signal_num) {
    printf("Received signal: %d\n", signal_num);
}

// example core dump:
void bad_func()
{
    int *ptr = NULL;
    *ptr  = 42; // crash seg fault
}

// ulimit -c unlimited    # Enable unlimited core dump size
// # Check system limits
//  cat /proc/sys/kernel/core_pattern
// -rw------- 1 user user 200704 Oct 20 15:30 core.12345

/*
ulimit -c unlimited
gcc -g crash.c -o crash  # -g for debug symbols
./crash
gdb ./crash core.12345
*/
int main()
{
    // signal(SIGINT, signalHandler);
    // while(1)
    //     printf("hello wl!\n");

    // signal(SIGINT, signalHandler2); //Install handler for SIGINT
    // raise(SIGINT); // Send SIGINT to myself

    // signal(SIGINT, handle_signal);
    // pid_t pid = getpid();
    // kill(pid, SIGINT); // generate signal using kill()

    printf("About to crash...\n");
    bad_func();
    printf("This never prints\n");
    return 0;
}