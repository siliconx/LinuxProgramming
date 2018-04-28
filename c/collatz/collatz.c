#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {  // arguments error
        printf("ARG ERROR\n");
        exit(0);
    }

    long n =  atoi(argv[1]);
    if (n < 1) {  // convert failed
        printf("ARG ERROR\n");
        exit(0);
    }

    while (n > 1) {  // gen the collatz sequence
        printf("%ld ", n);
        if (n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n /= 2;
        }
    }
    printf("1\n");
    return 0;
}
