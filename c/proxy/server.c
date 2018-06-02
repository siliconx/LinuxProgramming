// Server Side
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8888
#define BUFFER_SIZE 4096

char* proxy_server();

char* proxy_server() {  // proxy server
    printf("Proxy Server Running on PORT: %d\n", PORT);
    int i = 0;
    int server_fd, tcp_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int msg_len = 0;  // message length
    char* replace_head = "GET / HTTP/1.1\r\n";
    char* request_msg = malloc(BUFFER_SIZE * sizeof(char));  // request message
    char* new_msg = malloc(BUFFER_SIZE * sizeof(char));  // // to store new mssage
    char *response = "HTTP/1.1 200 OK\r\nCache-Control: no-cache, private\r\n\r\nhello";  // Response string

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

    if ((tcp_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(tcp_socket, request_msg, BUFFER_SIZE);
    fflush(stdout);

    // replace request message, which has proxy information
    msg_len = strlen(request_msg);
    for (i = 0; i < msg_len; ++i) {
        if (request_msg[i] == '\r' && request_msg[++i]  == '\n') {
            break;
        }
    }
    strcat(new_msg, replace_head);
    strcat(new_msg, request_msg + i + 1);
    printf("%s\n", request_msg);
    free(request_msg);

    // response = request_msg;  // echo message
    send(tcp_socket, response, strlen(response), 0);
    close(tcp_socket);

    return new_msg;
}

int main(int argc, char const *argv[]) {
    while(1) {
        printf("%s\n", proxy_server());
    }

    return 0;
}
