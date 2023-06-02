#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define LOCKFILE "/tmp/lock"

int kill(pid_t pid, int sig);
void signalHandler(int signalNumber);

int main() {
    FILE* file = fopen(LOCKFILE, "r");
    if (file == NULL) {
        file = fopen(LOCKFILE, "w");
        if (file == NULL) {
            printf("Error creating lock file.\n");
            return 1;
        }
        fprintf(file, "%i", getpid());
        fclose(file);
        signal(SIGUSR1, signalHandler);
        signal(SIGINT, signalHandler);
        while(1) {
            sleep(1);
        }
    } else {
        pid_t pid;
        fscanf(file, "%i", &pid);
        kill(pid, SIGUSR1);
    }
    return 0;
}

void signalHandler(int signalNumber) {
    if (signalNumber == SIGUSR1) {
        signal(SIGUSR1, signalHandler);
        printf("\nReceived signal SIGUSR1. Detected the attempt to start a second instance of the program.\n");
    } else if (signalNumber == SIGINT) {
        printf("\nReceived signal SIGINT (Ctrl+C). Removing lock file and exiting the program.\n");
        remove(LOCKFILE);
        exit(0);
    }
}
