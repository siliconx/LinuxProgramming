#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_SIZE 64
#define BUFFER_SIZE 4096
#define START 8

int main(int argc, char const *argv[]) {
    char* replace_head = "GET / HTTP/1.1\r\n";
    char* str = "CONNECT www.google.com:443 HTTP/1.1\r\nHost: www.google.com:443";
    int len = strlen(str);
    int i, j, k;
    for (i = 0; i < len; ++i) {
        if (str[i] == '\r' && str[++i]  == '\n') {
            break;
        }
    }
    char* new_str = (char*) malloc(BUFFER_SIZE * sizeof(char));
    char* host = (char*) malloc(STR_SIZE * sizeof(char));
    char* port = (char*) malloc(STR_SIZE * sizeof(char));
    strcat(new_str, replace_head);
    strcat(new_str, str + i + 1);

    for (j = START; j < i; ++j) {
        if (str[j] == ':') {
            break;
        }
        /* code */
    }

    for (k = j; k < i; ++k) {
        if (str[k] == ' ') {
            break;
        }
    }

    strncpy(host, str + START, j - START);
    strncpy(port, str + j + 1, k - j);

    printf("HOST: %s\n", host);
    printf("PORT: %s\n", port);
    printf("%s\n", new_str);
    return 0;
}