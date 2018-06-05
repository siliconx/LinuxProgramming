#include <stdio.h>  // for stdin/out
#include <ctype.h>  // for islower()/isupper(), tolower()/toupper()
#include <string.h>  // for strlen()
#include <sys/ipc.h>  // for key_t, ftok, IPC_CREAT/IPC_RMID
#include <sys/msg.h>  // for msgget()/msgsnd()/msgrcv()/msgctl()

#define BUFFER_SIZE 256

#define UP_KEY 16  // for Up queue key
#define DOWN_KEY 8  // for Down queue key
#define UP_MSG_TP 1  // for Up message type
#define DOWN_MSG_TP 2  // for Down message type

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
    printf("Message Queue Server Running...\n");
    up_queue_reader();
    return 0;
}

int down_queue_writer(char* original_msg) {  // Down queue writer
    key_t key = DOWN_KEY;  // unique key for message
    int msgid;

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    down_queue.msg_type = DOWN_MSG_TP;

    // copy message to Down queue
    strcpy(down_queue.msg_text, original_msg);

    // reverse message
    reverse(down_queue.msg_text, strlen(down_queue.msg_text));

    // send message
    msgsnd(msgid, &down_queue, sizeof(down_queue), 0);

    return 0;
}

int up_queue_reader() {  // Up queue reader
    key_t key = UP_KEY;  // unique key for message
    int msgid;

    // create a message queue with `key` and returns its identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // receive message
    printf("Waitting for message in Up Queue arrive...\n");
    msgrcv(/*msqid*/msgid, /*msgp*/&up_queue, /*msgsz*/sizeof(up_queue),
    /*msgtyp*/UP_MSG_TP, /*msgflg*/0);

    // send the received message to Down Queue
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
