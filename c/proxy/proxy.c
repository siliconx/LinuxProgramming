// Server Side
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  // gethostbyname

#define BUFFER_SIZE 4096
#define STR_SIZE 64
#define START 8  // len("CONNECT ") == 8

char* proxy_server(int);
char* proxy_client(const char*, char*, const char*);


char* proxy_server(int proxy_port) {  // proxy server
    printf("Proxy Server Running on PORT: %d\n", proxy_port);
    int server_fd, tcp_socket, valread;
    struct sockaddr_in address;

    int i, j, k;
    int opt = 1;
    int addrlen = sizeof(address);
    int msg_len = 0;  // message length
    char* request_msg = (char*) malloc(BUFFER_SIZE * sizeof(char));
    char* new_msg = (char*) malloc(BUFFER_SIZE * sizeof(char));  // to store new mssage
    char* host = (char*) malloc(STR_SIZE * sizeof(char));
    char* port = (char*) malloc(STR_SIZE * sizeof(char));
    char* response_msg;  // Response string
    char* replace_head = "GET / HTTP/1.1\r\n";

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
    address.sin_port = htons(proxy_port);

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

    // replace request message, which has proxy information
    msg_len = strlen(request_msg);
    for (i = 0; i < msg_len; ++i) {
        if (request_msg[i] == '\r' && request_msg[++i]  == '\n') {
            break;
        }
    }
    strcat(new_msg, replace_head);
    strcat(new_msg, request_msg + i + 1);
    printf("Original Message:\n%s\n", request_msg);

    // get HOST
    for (j = START; j < i; ++j) {
        if (request_msg[j] == ':') {
            break;
        }
        /* code */
    }
    strncpy(host, request_msg + START, j - START);
    printf("Remote HOST: %s\n", host);

    // get PORT
    for (k = j; k < i; ++k) {
        if (request_msg[k] == ' ') {
            break;
        }
    }
    strncpy(port, request_msg + j + 1, k - j);
    printf("Remote PORT: %s\n", port);

    // release the old requst message
    free(request_msg);

    // now, resend the request to remote server
    // host = "good.ncu.edu.cn";
    // port = "80";
    printf("New Mssage: \n%s\n", new_msg);
    response_msg = proxy_client(host, port, new_msg);

    // send response
    send(tcp_socket, response_msg, strlen(response_msg), 0);

    // close sokect
    close(tcp_socket);

    return response_msg;
}

char* proxy_client(const char* host, char* str_port, const char* request) {  // proxy client

    printf("Proxy Client Running...\n");
    struct sockaddr_in address;
    int sock = 0, valread;
    int port;
    struct sockaddr_in serv_addr;
    char ip[STR_SIZE];  // ip address
    char* response_msg = (char*) malloc(BUFFER_SIZE * sizeof(char));
    char **pptr;
    struct hostent *hptr;

    // port to int
    port = atoi(str_port);

    // Convert HOSTNAME to IP
    if ((hptr = gethostbyname(host)) == NULL) {
        fprintf(stderr, " gethostbyname error for host: %s\n", host);
        return NULL;
    }
    printf("HOSTNAME: %s\n", hptr->h_name);

    if (hptr->h_addrtype == AF_INET
        && (pptr = hptr->h_addr_list) != NULL) {
            inet_ntop(hptr->h_addrtype, *pptr, ip, sizeof(ip));
    } else {
        fprintf(stderr, "Error call inet_ntop \n");
    }

    printf("IP: %s\nPORT: %d\n", ip, port);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket create failed \n");
        return NULL;
    }
    printf("\n Socket created \n");

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IP addresses from text to binary form
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("\n Invalid address \n");
        return NULL;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Connection Failed \n");
        return NULL;
    }
    printf("\n Connected \n");

    send(sock, request, strlen(request), 0);
    valread = read(sock ,response_msg, 1024);

    return response_msg;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("USAGE: [PORT]\n");
        return -1;
    }

    int port = atoi(argv[1]);

    while (1) {
        char* response_msg = proxy_server(port);
        if (response_msg == NULL) {
            printf("No Message\n");
        } else {
            printf("%s\n", response_msg);
        }

    }

    return 0;
}
