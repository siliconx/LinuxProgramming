#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>  // for rand()
#include <time.h>
#include <unistd.h>  // for sleep()
#include <sys/ipc.h>  // for IPC
#include <sys/shm.h>  // for shared memory
#include <fcntl.h>  // for O_CREAT
#include <semaphore.h>  // for semaphore

#define KEY 1
#define MAX 5
#define N 20

int main() {
    printf("Producer running...\n");

    // ftok to generate unique key
    key_t key = KEY;

    // semaphore
    sem_t *avail = sem_open("available", O_CREAT, 0666, 3);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, /*size_tsize*/sizeof(int), 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *shelf = (int*) shmat(shmid, /*shmaddr*/(void*)0, /*shmflg*/0);
    *shelf = MAX;  // initial value is MAX

    // Use current time as seed for random generator
    srand(time(0));

    for (int i = 0; i < N; ++i) {
        printf("\n=========================No.%d=========================\n", i);
        printf("Waitting until shelf available...\n");
        sem_wait(avail);
        printf("Shelf available, now checking the number of items on the shelf...\n");
        if ((*shelf) < MAX) {
            printf("Shelf not full, putting a item to the shelf...\n");
            ++(*shelf);
            printf("Now, there are %d items on the shelf.\n", (*shelf));
        } else {
            printf("Shelf is full, let it go!\n");
        }

        sem_post(avail);
        sleep(rand() % 3);
    }

    printf("I'm tired, bye bye!\n");

    // detach from shared memory
    shmdt(shelf);

    return 0;
}