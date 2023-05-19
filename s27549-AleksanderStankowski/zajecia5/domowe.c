
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createProcess(int depth, int children) {
    int i;
    for (i = 0; i < children; i++) {
        switch (fork()) {
            case -1:
                printf("Fork err\n");
                exit(1);
            case 0:
                printf("PID: %i\tPPID: %i\n", getpid(), getppid());
                if (depth > 1) {
                    createProcess(depth - 1, children);
                }
                sleep(15);
                exit(0);
        }
    }
}

int main() {
    int status;
    printf("PID: %i\tPPID: %i\n", getpid(), getppid());
    createProcess(2, 2);
    waitpid(0, &status, 0);
    return 0;
}
