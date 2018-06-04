#include <stdio.h>
#include <sys/ipc.h>  // for key_t, ftok, IPC_CREAT
#include <sys/msg.h>  // for msgget/msgsnd/msgrcv/msgctl

#define BUFFER_SIZE 256

// for Up queue key
#define KEY_PATH_UP "UP"
#define KEY_ID_UP 16

// for Down queue key
#define KEY_PATH_DOWN "DOWN"
#define KEY_ID_DOWN 8

/**
* Message Queue Client.
* writer of Up queue
* reader of Down queue
*/

struct msg_queue {  // structure for message queue
    long msg_type;
    char msg_text[BUFFER_SIZE];
} down_queue, up_queue;

int up_queue_writer();  // Up queue writer
int down_queue_reader();  // Down queue reader

int main(int argc, char const *argv[]) {
    up_queue_writer();
    return 0;
}

int up_queue_writer() {
    key_t key;
    int msgid;

    // generate unique key by KEY_PATH_UP and KEY_ID_UP
    key = ftok(/*path*/KEY_PATH_UP, /*id*/KEY_ID_UP);
    int int_key = key;
    printf("key: %d\n", int_key);

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    up_queue.msg_type = 1;

    // input message
    printf("Insert message to send to server: ");
    fgets(up_queue.msg_text, sizeof(up_queue.msg_text), stdin);

    // msgsnd to send message
    msgsnd(msgid, &up_queue, sizeof(up_queue), 0);

    // now waitting for the message send from server in Down queue
    down_queue_reader();

    return 0;
}

int down_queue_reader() {
    key_t key;
    int msgid;

    // generate unique key by KEY_PATH_DOWN and KEY_ID_DOWN
    key = 2;//ftok(/*path*/KEY_PATH_DOWN, /*id*/KEY_ID_DOWN);
    int int_key = key;
    printf("key: %d\n", int_key);

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // receive message
    msgrcv(msgid, &down_queue, sizeof(down_queue), 1, 0);

    // show the message get from Down queue
    printf("Msg processed: %s \n", down_queue.msg_text);

    // destroy the queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
