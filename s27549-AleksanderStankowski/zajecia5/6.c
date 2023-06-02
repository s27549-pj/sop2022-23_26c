#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_MESSAGE_LENGTH 100

void send_message(const char* message) {
    FILE* file = fopen("/tmp/chat.txt", "w");
    if (file == NULL) {
        perror("Błąd otwarcia pliku");
        exit(1);
    }

    fprintf(file, "%s\n", message);
    fclose(file);
}

void receive_message(char* message) {
    FILE* file = fopen("/tmp/chat.txt", "r");
    if (file == NULL) {
        perror("Błąd otwarcia pliku");
        exit(1);
    }

    fgets(message, MAX_MESSAGE_LENGTH, file);
    fclose(file);
}

int main() {
    pid_t pid;
    char message[MAX_MESSAGE_LENGTH];

    pid = fork();

    if (pid < 0) {
        perror("Błąd przy tworzeniu procesu");
        exit(1);
    }

    if (pid == 0) {
        while (1) {
            printf("Wpisz wiadomość: ");
            fgets(message, MAX_MESSAGE_LENGTH, stdin);
            message[strcspn(message, "\n")] = '\0';

            send_message(message);
        }
    } else {
        while (1) {
            receive_message(message);
            printf("Otrzymano wiadomość: %s\n", message);
        }
    }

    return 0;
}
