#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID: %i\tPPID: %i\n", getpid(), getppid());
    getchar();
    return 0;
}
