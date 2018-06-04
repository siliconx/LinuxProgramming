#include <stdio.h>  // for stdin/out
#include <stdlib.h>  // for malloc
#include <ctype.h>  // for islower/isupper, tolower/toupper
#include <string.h>  // for strlen
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFFER_SIZE 256
#define KEY_PATH "nothing"
#define KEY_ID 16

/**
* Message Queue server.
* writer of Down queue
* reader of Up queue
*/

struct msg_buffer {  // structure for message queue
    long msg_type;
    char msg_text[BUFFER_SIZE];
} down_queue, up_queue;


int down_queue_writer(char*);
int up_queue_reader();
int reverse(char*, int);  // reverse char (upper to lower, lower to upper)

int main(int argc, char const *argv[]) {
    up_queue_reader();
    return 0;
}

int down_queue_writer(char* original_msg) {  // Down queue writer
    key_t key;
    int msgid;

    // ftok to generate unique key from KEY_PATH and KEY_ID
    key = ftok(/*path*/KEY_PATH, /*id*/KEY_ID);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    down_queue.msg_type = 1;

    strcpy(down_queue.msg_text, original_msg);
    reverse(down_queue.msg_text, strlen(down_queue.msg_text));  // reverse message

    // msgsnd to send message
    msgsnd(msgid, &down_queue, sizeof(down_queue), 0);

    // display the message
    // printf("Data send is : %s \n", down_queue.msg_text);

    return 0;
}

int up_queue_reader() {  // Down queue reader
    key_t key;
    int msgid;

    // ftok to generate unique key from KEY_PATH and KEY_ID
    key = ftok(/*path*/KEY_PATH, /*id*/KEY_ID);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgrcv to receive message
    msgrcv(msgid, &up_queue, sizeof(up_queue), 1, 0);

    // display the message
    // printf("Message Received from Client is : %s \n",
    //                 up_queue.msg_text);

    // send
    down_queue_writer(up_queue.msg_text);

    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

int reverse(char* msg, int len) {
    char c;
    for (int i = 0; i < len; ++i) {
        c = msg[i];
        if (islower(c)) {
            msg[i] = toupper(c);
        } else if (isupper(c)) {
            msg[i] = tolower(c);
        }
    }

    return 0;
}