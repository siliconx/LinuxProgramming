// Server Side
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>  // for threading, link with -lpthread

#define PORT 8000
#define BUFFER_SIZE 1024

int count = 0;  // counting total requests
char *response;  // Response string
char buffer[BUFFER_SIZE] = {0};  // message buffer

void *msg_handler(void*);

int main(int argc, char const *argv[]) {
    printf("Multi-Server Running...\n");
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    pthread_t tid;  // the thread identifier
    pthread_attr_t attr;  // set of attributes for the thread

    // socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            return -1;
        }

        /**
        * Now, Create thread to send message
        */

        // get the default attributes
        pthread_attr_init(&attr);

        // create the thread
        pthread_create(&tid, &attr, msg_handler, (void*) &new_socket);

        // now wait for the thread to exit
        pthread_join(tid, NULL);
    }

    return 0;
}


/**
 * This function will to handle the sending of reponse message
 */
void *msg_handler(void *new_socket) {
    int sock = *(int*) new_socket;
    read(sock, buffer, BUFFER_SIZE);

    printf("Message from Multi-Client(No.%d): %s\n", count, buffer);

    response = buffer;  // echo message

    send(sock, response, strlen(response), 0);
    count++;
}
