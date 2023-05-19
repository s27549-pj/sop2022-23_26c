#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int input, sum, i, status;
    pid_t pid;
    input = atoi(argv[1]);
    switch (pid = fork()) {
    case -1:
        printf("Fork err\n");
        break;
    case 0:
        printf("Proces potomny: Wypisujący liczby nieparzyste od 1 do %i:", input);
        for (i = 1; i < input; i++)
            if (i % 2 != 0)
                printf(" %i", i);
        break;
    default:
        waitpid(pid, &status, 0);
        sum = 0;
        for (i = 0; i < input; i++)
            sum += i;
        printf("\nProces rodzica: Wartość sumy liczb od 0 do %i: %i\n", input, sum);
        break;
    }
    return 0;
}
