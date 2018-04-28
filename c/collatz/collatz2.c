#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {  // arguments error
        printf("ARG ERROR\n");
        exit(0);
    }

    execlp("./collatz.out", "./collatz.out", argv[1], NULL);

    return 0;
}
