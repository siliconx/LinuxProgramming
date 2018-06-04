#include <stdio.h>  // for stdin/out
#include <stdlib.h>  // for malloc
#include <ctype.h>  // for islower/isupper, tolower/toupper
#include <string.h>  // for strlen
#include <sys/ipc.h>  // for key_t, ftok, IPC_CREAT
#include <sys/msg.h>  // for msgget/msgsnd/msgrcv/msgctl

#define BUFFER_SIZE 256

// for Up queue key
#define KEY_PATH_UP "UP"
#define KEY_ID_UP 32

// for Down queue key
#define KEY_PATH_DOWN "DOWN"
#define KEY_ID_DOWN 8

/**
* Message Queue server.
* writer of Down queue
* reader of Up queue
*/

struct msg_queue {  // structure for message queue
    long msg_type;
    char msg_text[BUFFER_SIZE];
} down_queue, up_queue;


int down_queue_writer(char*);  // Down queue writer
int up_queue_reader();  // Up queue reader
int reverse(char*, int);  // reverse char (upper to lower, lower to upper)

int main(int argc, char const *argv[]) {
    up_queue_reader();
    return 0;
}

int down_queue_writer(char* original_msg) {  // Down queue writer
    key_t key;
    int msgid;

    // generate unique key by KEY_PATH_DOWN and KEY_ID_DOWN
    key = ftok(/*path*/KEY_PATH_DOWN, /*id*/KEY_ID_DOWN);

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    down_queue.msg_type = 1;

    // copy message to Down queue
    strcpy(down_queue.msg_text, original_msg);

    // reverse message
    reverse(down_queue.msg_text, strlen(down_queue.msg_text));

    // msgsnd to send message
    msgsnd(msgid, &down_queue, sizeof(down_queue), 0);

    return 0;
}

int up_queue_reader() {  // Down queue reader
    key_t key;
    int msgid;

    // generate unique key by KEY_PATH_UP and KEY_ID_UP
    key = ftok(/*path*/KEY_PATH_UP, /*id*/KEY_ID_UP);

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // receive message
    msgrcv(msgid, &up_queue, sizeof(up_queue), 1, 0);

    // send received message
    down_queue_writer(up_queue.msg_text);

    // destroy the queue
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
