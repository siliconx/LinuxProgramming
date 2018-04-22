#include "functions.h"

int is_owner(int file_uid) {
    return getuid() == file_uid;
}


int chmod_to_777(char* path) {
    chmod(path, S_IRWXU | S_IRWXG | S_IRWXO);
    return 0;
}
