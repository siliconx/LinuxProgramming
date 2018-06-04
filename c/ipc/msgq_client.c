#include <stdio.h>
#include <sys/ipc.h>  // for key_t, ftok, IPC_CREAT/IPC_RMID
#include <sys/msg.h>  // for msgget/msgsnd/msgrcv/msgctl

#define BUFFER_SIZE 256

#define UP_KEY 16  // for Up queue key
#define DOWN_KEY 8  // for Down queue key
#define UP_MSG_TP 1  // for Up message type
#define DOWN_MSG_TP 2  // for Down message type

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
    key_t key = UP_KEY;  // unique key for message
    int msgid;

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    up_queue.msg_type = UP_MSG_TP;

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
    key_t key = DOWN_KEY;  // unique key for message
    int msgid;

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // receive message
    msgrcv(/*msqid*/msgid, /*msgp*/&down_queue, /*msgsz*/sizeof(down_queue),
    /*msgtyp*/DOWN_MSG_TP, /*msgflg*/0);

    // show the message get from Down queue
    printf("Msg processed: %s \n", down_queue.msg_text);

    // destroy the queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
