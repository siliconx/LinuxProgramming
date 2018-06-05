#include <stdio.h>
#include <stdlib.h>  // for rand()
#include <unistd.h>  // for sleep()
#include <time.h>
#include <sys/ipc.h>  // for IPC
#include <sys/shm.h>  // for shared memory
#include <fcntl.h>  // for O_CREAT
#include <semaphore.h>  // for semaphore

#define KEY 1
#define MIN 0

int main() {
    // unique key
    key_t key = KEY;

    // semaphore
    sem_t *avail = sem_open("available", O_CREAT, 0666, 3);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *shelf = (int*) shmat(shmid, /*shmaddr*/(void*)0, /*shmflg*/0);

    // Use current time as seed for random generator
    srand(time(0));

    while (1) {
        printf("Waitting until shelf available...\n");
        sem_wait(avail);
        printf("Shelf available, now checking the number of items on the shelf...\n");
        if ((*shelf) > MIN) {
            printf("Shelf not empty, getting a item from the shelf...\n");
            --(*shelf);
            printf("Now, there are %d items on the shelf\n", (*shelf));
        } else {
            printf("Shelf is empty, let it go!\n");
        }
        sleep(rand() % 2);
        sem_post(avail);
        printf("=============================================\n");
    }

    //detach from shared memory
    shmdt(shelf);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}