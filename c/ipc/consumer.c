#include <stdio.h>  // for stdin/out
#include <stdlib.h>  // for srand()/rand()
#include <unistd.h>  // for sleep()
#include <time.h>  // for time()
#include <sys/ipc.h>  // for IPC
#include <sys/shm.h>  // for shared memory
#include <fcntl.h>  // for O_CREAT
#include <semaphore.h>  // for semaphore

#define KEY 1  // unique key for shared memory
#define MIN 0  // min item on shelf
#define M 3  // max times of shelf in empty status continuously
#define shelf_sem_name "shelf_semaphore"  // `shelf` semaphore name

int main() {
    printf("Consumer running...\n");

    // unique key
    key_t key = KEY;

    // semaphore for shelf
    sem_t *shelf_avail = sem_open(shelf_sem_name, O_CREAT, 0666, 3);

    // returns an identifier in shmid
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

    // attach to shared memory
    int *shelf = (int*) shmat(shmid, /*shmaddr*/(void*)0, /*shmflg*/0);

    // use current time as seed for random generator
    srand(time(0));

    // counter
    int count = 0;

    // times of shelf in empty status continuously
    int times = 0;

    while (times < M) {  // exists when shelf empty in M times continously
        printf("\n========================= No.%d =========================\n", count);
        printf("Waitting until shelf available...\n");
        sem_wait(shelf_avail);

        printf("Shelf available, now checking the number of items on the shelf...\n");
        if ((*shelf) > MIN) {  // not empty
            printf("Shelf has %d item(s) currently, not empty.\n", (*shelf));
            printf("Getting an item from the shelf...\n");
            --(*shelf);  // remove an itme
            printf("Now, there are %d item(s) on the shelf.\n", (*shelf));
            times = 0;
        } else {  // empty
            ++times;
            printf("Shelf is empty, let it go!\n");
        }

        sem_post(shelf_avail);
        sleep(rand() % 3 + 1);

        ++count;
    }

    printf("\n========================== End ==========================\n");
    printf("Times up, Shelf is empty in %d times continuously.\n", M);
    printf("Maybe the producer was tired and exited.\nI have to exit, too. Bye!!!\n");

    // detach from shared memory
    shmdt(shelf);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    // close and unlink semaphore
    sem_close(shelf_avail);
    sem_unlink(shelf_sem_name);

    return 0;
}