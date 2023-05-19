#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID: %i\nPPID: %i\n", getpid(), getppid());
    getchar();
    return 0;
}