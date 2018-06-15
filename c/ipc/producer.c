#include <stdio.h>  // for stdin/out
#include <stdlib.h>  // for srand()/rand()
#include <time.h>  // for time()
#include <unistd.h>  // for sleep()
#include <sys/ipc.h>  // for IPC
#include <sys/shm.h>  // for shared memory
#include <fcntl.h>  // for O_CREAT
#include <semaphore.h>  // for semaphore

#define KEY 1  // unique key for shared memory
#define MAX 5  // max item on shelf
#define N 20  // times of producer to run
#define shelf_sem_name "shelf_semaphore"  // `shelf` semaphore name

int main() {
    printf("Producer running...\n");

    // unique key
    key_t key = KEY;

    // semaphore for shelf
    sem_t *shelf_avail = sem_open(shelf_sem_name, O_CREAT, 0666, 3);

    // returns an identifier in shmid
    int shmid = shmget(key, /*size_tsize*/sizeof(int), 0666 | IPC_CREAT);

    // attach to shared memory
    int *shelf = (int*) shmat(shmid, /*shmaddr*/(void*)0, /*shmflg*/0);
    *shelf = MAX;  // initial itmes on shelf is `MAX`

    // use current time as seed for random generator
    srand(time(0));

    for (int i = 0; i < N; ++i) {  // loop N times
        printf("\n========================= No.%d =========================\n", i);
        printf("Waitting until shelf available...\n");
        sem_wait(shelf_avail);

        printf("Shelf available, now checking the number of items on the shelf...\n");
        if ((*shelf) < MAX) {  // not full
            printf("Shelf has %d item(s) currently, not full.\n", (*shelf));
            printf("Putting an item to the shelf...\n");
            ++(*shelf);  // add an item
            printf("Now, there are %d item(s) on the shelf.\n", (*shelf));
        } else {  // full
            printf("Shelf is full, let it go!\n");
        }

        sem_post(shelf_avail);
        sleep(rand() % 3 + 1);
    }

    printf("\n========================== End ==========================\n");
    printf("I'm tired, bye bye!\n");

    // detach from shared memory
    shmdt(shelf);

    return 0;
}