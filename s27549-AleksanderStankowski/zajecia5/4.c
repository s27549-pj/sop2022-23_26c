#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int p_count, i, status;
    p_count = 100;
    for (i = 0; i < p_count; i++)
    {
        switch (fork()) {
        case -1:
            printf("Fork err\n");
            return -1;
        case 0:
            printf("PID: %i\tPPID: %i\n", getpid(), getppid());
            break;
        default:
            printf("Proces %i\n", i + 1);
            waitpid(0, &status, 0);
            return 0;
        }
    }
    getchar();
    return 0;
}
