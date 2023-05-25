#include <stdio.h>

int main(int argc, char** argv) {
    unsigned char buffer[16], char_read;
    int current_row = 0;
    int i;
    FILE *file;

    printf("Loading file: %s\n", argv[1]);
    file = fopen(argv[1], "rb");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    while ((char_read = fread(buffer, sizeof(unsigned char), 16, file)) > 0) {
        printf("%08x  ", current_row * 16);
        for (i = 0; i < 16; i++) {
            if (i < char_read)
                printf("%02x ", buffer[i]);
            else
                printf("   ");
            if (i == 16 / 2 - 1)
                printf(" ");
        }
        printf(" ");
        for (i = 0; i < char_read; i++) {
            if (buffer[i] >= 32 && buffer[i] != 127)
                printf("%c", buffer[i]);
            else
                printf(".");
        }
        printf("\n");
        current_row++;
    }

    printf("Closing file: %s\n", argv[1]);
    fclose(file);

    return 0;
}
