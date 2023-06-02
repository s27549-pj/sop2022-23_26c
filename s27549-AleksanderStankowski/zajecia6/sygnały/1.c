#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signalHandler(int signalNumber);

int main() {
    printf("PID: %i\n", getpid());
    signal(SIGUSR1, signalHandler);
    while (1)
    {
        pause();
    }
    return 0;
}

void signalHandler(int signalNumber) {
    printf("\nReceived signal number: %d\n", signalNumber);
    exit(0);
}
