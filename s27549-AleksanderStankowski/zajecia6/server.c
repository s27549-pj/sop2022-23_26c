#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <signal.h>

#define FILENAME_MAX_LENGTH 256
#define FILEBUFFER_SIZE 1024
#define LOG_FILE_NAME "./server_logs.txt"

void error(char* msg) {
    perror(msg);
    exit(1);
}

bool server_active = true;

void signalHandler(int signalNumber) {
    printf("\nReceived signal number: %d\n", signalNumber);
    server_active = false;
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, filename_length, file_size, bytes_read;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char filebuffer[FILEBUFFER_SIZE];
    char filename[FILENAME_MAX_LENGTH];
    FILE* file;
    FILE* log_file;

    remove(LOG_FILE_NAME);
    log_file = fopen(LOG_FILE_NAME, "w+");
    if (file == NULL)
        error("ERROR on opening log file");

    if (argc < 2)
        error("ERROR no port provided");
    portno = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    if (listen(sockfd, 1) < 0)
        error("ERROR on listen");
    clilen = sizeof(cli_addr);

    signal(SIGINT, signalHandler);
    while (server_active)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        fprintf(log_file, "Accepted connection from: %s on port: %i\n", inet_ntoa(cli_addr.sin_addr), (int) ntohs(cli_addr.sin_port));

        read(newsockfd, &filename_length, sizeof(int));
        read(newsockfd, filename, filename_length);
        filename[filename_length] = '\0';
        fprintf(log_file, "Received request for a file: %s\n", filename);

        file = fopen(filename, "rb");
        if (file == NULL) {
            filename_length = -1;
            write(newsockfd, &filename_length, sizeof(int));
            error("ERROR file not found");
        } else {
            fseek(file, 0, SEEK_END);
            file_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            write(newsockfd, &file_size, sizeof(int));

            while ((bytes_read = fread(filebuffer, sizeof(char), FILEBUFFER_SIZE, file)) > 0)
                write(newsockfd, filebuffer, bytes_read);
        }

        fprintf(log_file, "File %s sent successfully\n", filename);
        fclose(file);
        close(newsockfd);
    }

    fclose(log_file);
    close(sockfd);
    return 0;
}
