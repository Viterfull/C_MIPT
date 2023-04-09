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
    
    printf("жду сообщения\n");
    while (1){

        msgrcv(id, (void*)&messege, sizeof(msg) - sizeof(long), 0, 0);
        printf("сообщение принято: type: %ld \n", messege.type);
        if (messege.type == 2) break;
    }
    printf("принял собщения окончани\n");
    msgctl(id, IPC_RMID, 0);

    return 0;
}

// сообщения

// ftok() -> ключ
// ключ -> создание очереди сообщений( msgget() )
// есть да приметива:
//     msgsnd() - отправка
//     msgrcv() - принятие
//     msgctl() - удаление 

// 1) сделать две программы, одна отсылает другой (n = const) сообщений, и отсылает закрывающие сообщение
// 2) сделать отправлку сообщений
// 3) сделать синхронизацию программ