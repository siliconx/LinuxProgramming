#include<stdio.h>
#include <sys/types.h>
#include<unistd.h>


int main() {
    // child process because return value zero
    if (fork() == 0)
        printf("Hello from Child!\n");

    // parent process because return value non-zero.
    else
        printf("Hello from Parent!\n");
    return 0;
}
