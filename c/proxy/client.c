#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEST_PORT 80
#define BUFF_SIZE 4096
#define DEST_IP_ADDR "10.0.9.139"
#define DEST_IP_BY_NAME "demo.git.com"


void process_info(int socket_fd) {
    int send_num;
    char send_buf [] = "helloworld";
    char recv_buf [BUFF_SIZE];
    char str1[BUFF_SIZE];
    while (1) {
        printf("begin send\n");
        memset(str1, 0, BUFF_SIZE);
        strcat(str1, "POST http://demo.git.com/sum.php HTTP/1.1\r\n");
        strcat(str1, "Host: demo.git.com\r\n");
        strcat(str1, "Content-Length: 65\r\n");
        strcat(str1, "Content-Type: application/x-www-form-urlencoded\r\n");
        strcat(str1, "\r\n");
        strcat(str1, "mathod=adb_signe&token=0E1FEECD0EE54E3B8568A536A7036D78B1AC7EEE");
        strcat(str1, "\r\n\r\n");
        printf("str1 = %s\n", str1);
        send_num = send(socket_fd, str1, strlen(str1), 0);
        if (send_num < 0) {
            perror("send error");
            exit(1);
        } else {
            printf("send successful\n");
            printf("begin recv:\n");
            int recv_num = recv(socket_fd, recv_buf, sizeof(recv_buf), 0);
            if (recv_num < 0) {
                perror("recv");
                exit(1);
            } else {
                printf("recv sucess:%s\n", recv_buf);
            }
        }
        break;
        sleep(5);
    }
}


int main() {
    int socket_fd;
    struct sockaddr_in addr_serv;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket error");
        exit(1);
    } else {
        printf("socket successful");
    }

    struct hostent* hostInfo = gethostbyname(DEST_IP_BY_NAME);  // get host infromation
    if (NULL == hostInfo) {
        printf("hostInfo is null\n");
        return -6;
    }

    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(DEST_PORT);
    //addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDR);

    printf("Ip address = %s \n", inet_ntoa(*((struct in_addr*)hostInfo->h_addr)));
    memcpy(&addr_serv.sin_addr, &(*hostInfo->h_addr_list[0]),
        hostInfo->h_length);

    if (connect(socket_fd, (struct sockaddr*)(&addr_serv),
        sizeof(addr_serv)) < 0) {
        perror("connect error\n");
        exit(1);
    } else {
        printf("connect successful\n");
    }
    process_info(socket_fd);
}