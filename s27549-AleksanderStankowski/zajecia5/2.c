#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    waitpid(fork(), &status, 0);
    printf("PID: %i\tPPID: %i\n", getpid(), getppid());
    getchar();
    return 0;
}
