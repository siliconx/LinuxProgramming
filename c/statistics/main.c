#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    char* path = argv[1];
    if (argc != 2) {
        printf("ARGS ERROR\n");
        return 1;
    }

    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        printf("PATH INCORRECT!!!\n");
        return 1;
    }

    if (S_ISREG(path_stat.st_mode)) {
        printf("`%s` is a file\n", path);

        if (is_owner(path_stat.st_uid)) {
            printf("you are the owner of the file, and now changing the permissions to 777 of the file\n");
            chmod_to_777(path);
            printf("done!\n");
        } else {
            printf("you are NOT the owner of the file\n");
        }
    } else {
        printf("`%s` is a dir\n", path);
    }
}
