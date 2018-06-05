#include <fcntl.h>  // for O_CREAT
#include <semaphore.h>  // for semaphore

int main(int argc, char const *argv[]) {
    sem_t *avail = sem_open("available", O_CREAT, 0666, 3);
    sem_post(avail);
    return 0;
}