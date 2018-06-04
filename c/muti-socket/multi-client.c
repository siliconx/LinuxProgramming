// Client side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // fork()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define N 7

int main(int argc, char const *argv[]) {
    for (int i = 0; i < N; ++i) {  // create (2^N - 1) child processes
        fork();
    }

    printf("Multi-Client Running...\n");
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *request = "Multi-Processes Client";  // request message
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket create failed \n");
        return -1;
    }


    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, request, strlen(request), 0);
    valread = read(sock , buffer, 1024);
    printf("Message from Multi-Server: %s\n", buffer);
    fflush(stdout);

    return 0;
}