#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// linkedlist
struct node {
    int e;
    struct node *next;
};

struct node *head = NULL;  // header of list
struct node *r = NULL;  // pointer of current positoin

void *gen_collatz(void *param);  // thread to generate collatz

int main(int argc, char *argv[]) {
    pthread_t tid;  // the thread identifier
    pthread_attr_t attr;  // set of attributes for the thread

    if (argc != 2) {
        fprintf(stderr, "usage: %s <integer value>\n", argv[0]);
        return -1;
    }

    // get the default attributes
    pthread_attr_init(&attr);

    // create the thread
    pthread_create(&tid, &attr, gen_collatz, argv[1]);

    // now wait for the thread to exit
    pthread_join(tid, NULL);

    //  traversing the list
    r = head;
    while (r != NULL) {
        printf("%d ", r->e);
        r = r->next;
    }
    printf("\n");
}

/**
 * The thread will begin control in this function
 */
void *gen_collatz(void *param) {
    int n = atoi(param);  // convert string to int

    if (n > 1) {
        struct node *temp;

        while (n > 1) {  // gen the collatz sequence

            // create a node by malloc
            temp = (struct node *) malloc(sizeof(struct node));
            temp->e = n;
            temp->next = NULL;

            if (head == NULL) {
                head = temp;  // first node
                r = temp;
            } else {  // latter node
                r->next = temp;
                r = r->next;
            }

            if (n % 2 == 1) {
                n = 3 * n + 1;
            } else {
                n /= 2;
            }
        }

        // lastest node -- value: 1
        temp = (struct node *) malloc(sizeof(struct node));
        temp->e = 1;
        temp->next = NULL;

        r->next = temp;
    }

    pthread_exit(0);
}
