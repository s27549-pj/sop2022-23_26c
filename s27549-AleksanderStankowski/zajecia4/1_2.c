#include <stdio.h>

int main() {
    int sum = 0, number;

    while (scanf("%d", &number) == 1)
        sum += number;

    return sum; //echo $?
}
