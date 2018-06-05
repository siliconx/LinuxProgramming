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
#define M 5

int main() {
    printf("Consumer running...\n");
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

    // count
    int count = 0;

    // times of shelf in empty status continuously
    int times = 0;

    while (1) {
        printf("\n=========================No.%d=========================\n", count);
        printf("Waitting until shelf available...\n");
        sem_wait(avail);
        printf("Shelf available, now checking the number of items on the shelf...\n");
        if ((*shelf) > MIN) {
            printf("Shelf not empty, getting a item from the shelf...\n");
            --(*shelf);
            printf("Now, there are %d items on the shelf.\n", (*shelf));
            times = 0;
        } else {
            ++times;
            printf("Shelf is empty, let it go!\n");
        }

        sem_post(avail);
        sleep(rand() % 3 + 1);

        if (times >= M) {
            printf("Times up, Shelf is empty in %d times continuously, Maybe the producer was tired.\nI have to exist, too.\nBye!!!\n", M);
            break;
        }
        ++count;
    }

    //detach from shared memory
    shmdt(shelf);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}