#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE *userFile;
    int size, i;
    int* numbers;

    userFile = argc < 2 ? stdin : fopen(argv[1], "r");

    if (fscanf(userFile, "%d\n", &size) != 1) {
        printf("format err");
        fclose(userFile);
        return 1;
    }

    numbers = malloc(size * sizeof(int));

    if (numbers == NULL) {
        printf("malloc err");
        fclose(file);
        return 1;
    }

    for (i = 0; i < size; i++) {
        if (fscanf(userFile, "%d\n", &numbers[i]) != 1) {
            printf("format err");
            fclose(userFile);
            free(numbers);
            return 1;
        }
    }

    fclose(userFile);

    for (i = size - 1; i >= 0; i--)
        printf("%d\n", numbers[i]);

    free(numbers);

    return 0;
}
