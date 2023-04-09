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
    msg messege;
    int id = msgget(key, 0777);
    if(id == -1){
        id = msgget(key, 0777|IPC_CREAT);
    }

    printf("жду действий другой программы\n");
    msgrcv(id, (void*)&messege, sizeof(msg) - sizeof(long), 0, 0);
    printf("время продолжить\n");

    msgctl(id, IPC_RMID, 0);
    return 0;
}