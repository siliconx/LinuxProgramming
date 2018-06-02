// Client side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080
#define IP_LEN 64
#define BUFFER_SIZE 4096
#define SERVER_ADDRESS "119.29.148.227"

int main(int argc, char const *argv[]) {
    printf("Client Running...\n");
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* ip = (char*) malloc(IP_LEN * sizeof(char));  // ip address
    char* request = "GET / HTTP/1.1\r\nHost: 119.29.148.227\r\n\r\n";
    char buffer[BUFFER_SIZE] = {0};

    printf("Enter IP: ");
    scanf("%s", ip);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket create failed \n");
        return -1;
    }
    printf("\n Socket created \n");

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP addresses from text to binary form
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("\n Connected \n");

    // printf("Enter a message: ");
    // fgets(request, BUFFER_SIZE, stdin);

    send(sock, request, strlen(request), 0);
    valread = read(sock ,buffer, 1024);
    printf("Response: %s\n", buffer);

    return 0;
}