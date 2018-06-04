#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFFER_SIZE 256
#define KEY_PATH "nothing"
#define KEY_ID 16

/**
* Message Queue Client.
* writer of Up queue
* reader of Down queue
*/

struct msg_buffer {  // structure for message queue
    long msg_type;
    char msg_text[BUFFER_SIZE];
} down_queue, up_queue;

int up_queue_writer();  // Up queue writer
int down_queue_reader();  // Down queue reader

int main(int argc, char const *argv[]) {
    up_queue_writer();
    down_queue_reader();
    return 0;
}

int up_queue_writer() {
    key_t key;
    int msgid;

    // ftok to generate unique key from KEY_PATH and KEY_ID
    key = ftok(/*path*/KEY_PATH, /*id*/KEY_ID);
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    up_queue.msg_type = 1;

    printf("Insert message to send to server: ");
    fgets(up_queue.msg_text, sizeof(up_queue.msg_text), stdin);

    // msgsnd to send message
    msgsnd(msgid, &up_queue, sizeof(up_queue), 0);

    return 0;
}

int down_queue_reader() {
    key_t key;
    int msgid;

    // ftok to generate unique key from KEY_PATH and KEY_ID
    key = ftok(/*path*/KEY_PATH, /*id*/KEY_ID);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgrcv to receive message
    msgrcv(msgid, &down_queue, sizeof(down_queue), 1, 0);

    // display the message
    printf("Msg processed: %s \n",
                    down_queue.msg_text);

    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}