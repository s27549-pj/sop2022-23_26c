#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int i, j;
    int height = atoi(argv[1]);

    for (i = 1; i <= height; i++) {
        for (j = 1; j <= height - i; j++)
            printf(" ");
        for (j = 1; j <= 2 * i - 1; j++)
            printf("*");
        printf("\n");
    }

    return 0;
}
