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

#define BUFFER_SIZE 1024
#define LOG_FILE_NAME "./webserver_logs.txt"
#define PORTNO 8080

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
    int sockfd, newsockfd, valwrite, valread;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    FILE* log_file;
    char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html>TEST HTML</html>\r\n";

    remove(LOG_FILE_NAME);
    log_file = fopen(LOG_FILE_NAME, "w+");
    if (log_file == NULL)
        error("ERROR on opening log file");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORTNO);

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
        
        valread = read(newsockfd, buffer, BUFFER_SIZE);
        if (valread < 0)
            error("ERROR on server read");

        fprintf(log_file, "TEST");
        sscanf(buffer, "%s %s %s", method, uri, version);
        fprintf(log_file, "[%s:%u] %s %s %s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), method, version, uri);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), method, version, uri);

        valwrite = write(newsockfd, resp, strlen(resp));
        if (valwrite < 0)
            error("Error on server write)");
        close(newsockfd);
    }
    fclose(log_file);
    close(sockfd);
    return 0;
}
