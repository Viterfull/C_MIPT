#include "struct_msg_1.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/msg.h>

int main(){
    key_t key = ftok("1_zad_1.c", 1);
    msg message_non = {1};
    msg message_stop = {2};
    int id = msgget(key, 0777);
    if(id == -1){
        id = msgget(key, 0777|IPC_CREAT);
    }
    msgsnd(id, (void*)&message_non, sizeof(msg) - sizeof(long), 0);
    msgsnd(id, (void*)&message_non, sizeof(msg) - sizeof(long), 0);
    msgsnd(id, (void*)&message_non, sizeof(msg) - sizeof(long), 0);
    msgsnd(id, (void*)&message_non, sizeof(msg) - sizeof(long), 0);
    msgsnd(id, (void*)&message_non, sizeof(msg) - sizeof(long), 0);
    msgsnd(id, (void*)&message_stop, sizeof(msg) - sizeof(long), 0);
    return 0;
}