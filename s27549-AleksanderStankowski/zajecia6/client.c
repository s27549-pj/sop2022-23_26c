#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define FILENAME_MAX_LENGTH 256
#define FILEBUFFER_SIZE 1024

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, fileLength, bytesRead, filename_length;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    FILE *file;
    char filename[FILENAME_MAX_LENGTH];
    char buffer[FILEBUFFER_SIZE];

    if (argc < 3)
        error("ERROR no port provided");
    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Filename: ");
    scanf("%s", filename);
    filename_length = strlen(filename);
    write(sockfd, &filename_length, sizeof(int));
    write(sockfd, filename, filename_length);
    read(sockfd, &fileLength, sizeof(int));
    if (fileLength == -1) {
        printf("File not found\n");
        return -1;
    }

    file = fopen("received_file", "wb");
    while (fileLength > 0 && (bytesRead = read(sockfd, buffer, FILEBUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), bytesRead, file);
        fileLength -= bytesRead;
    }
    
    fclose(file);
    printf("File received successfully\n");
    close(sockfd);
    return 0;
}
