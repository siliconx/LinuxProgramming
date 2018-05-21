// Client side
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8000
#define BUFFER_SIZE 1024
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *request;
    char buffer[BUFFER_SIZE] = {0};

    while (1) {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }


        memset(&serv_addr, '0', sizeof(serv_addr));
      
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
          
        // Convert IP addresses from text to binary form
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
            printf("\nInvalid address\n");
            return -1;
        }
      
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }

        printf("Enter a message: ");
        fgets(request, BUFFER_SIZE, stdin);

        send(sock, request, strlen(request), 0);
        valread = read(sock ,buffer, 1024);
        printf("Response: %s\n", buffer);
    }
    return 0;
}