#include <stdio.h>

int maximum(int a, int b) {return a > b ? a : b;}

int minimum(int a, int b) {return a < b ? a : b;}

int sum(int a, int b) {return a + b;}

int main() {
    int (*functions[3])(int, int) = {maximum, minimum, sum};
    int functionId, elementCount, v, element, i;

    scanf("%d %d %d", &functionId, &elementCount, &v);

    for (i = 1; i < elementCount; i++) {
        scanf("%d", &element);
        v = functions[functionId](v, element);
    }

    printf("%d", v);

    return 0;
}
