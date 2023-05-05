#include <stdio.h>

int main() {
    int sum = 0, number;

    while (scanf("%d", &number) == 1)
        sum += number;

    printf("Suma: %d\n", sum);

    return 0;
}
