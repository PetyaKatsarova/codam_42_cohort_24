# minitalk
Projet minitalk 42.

Both server and client are listening for incoming signals. The system works as a "handshake", the client sends a signal and waits for the server to send one back before continuing.
Eventually, the client sends a terminator signal to the server which then sends back a signal to the client to terminate its process.
not used:
global variable
memory allocation
usleep

## Run

make all
./server // PID=648574
// in new terminala run:
./client 648574 "Hello ku ku"

make bonus
./server_bonus

// in new terminal:
./client_bonus <PID> "test msg for bonus"

## Theory
main(int ac, char *av[]) 
int ac: het aantal argumenten dat is meegegeven bij het uitvoeren van het programma. ac staat voor argument count. 
./a.out 5, dan is ac gelijk aan 2. Eén voor de naam van het programma (./a.out) en één voor het getal (5).

char *av[]: een array van strings waarin de argumenten van het programma zijn opgeslagen. av[0] is de naam van het programma (./a.out), en av[1] is het eerste argument dat je meegeeft (in dit geval 5).

if (bit == 256)
bit starts at 1 and is shifted left (bit <<= 1) each time a signal is received.
After 8 shifts, bit becomes 256 (which is beyond the range of an 8-bit value).
When bit == 256, it means that all bits have been processed, and the value in val now represents one complete character.
At this point, the program either writes the character represented by val to the output or sends a termination signal if val is 0.

### KILL(pid, SIGUSR1)
kill() does not always mean terminating a process. Its main purpose is to send a signal to a process.
When you execute kill(pid, SIGUSR1), the operating system sends the SIGUSR1 signal to the process with the specified pid.
The target process must have a signal handler defined for SIGUSR1 to handle the signal properly. If there is no handler for SIGUSR1, the default behavior may be to terminate the process.