#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/sem.h>
#include "struct_msg_5.h"
#include <sys/msg.h>
/*
типы сообщений:
    в сервер:
        1 - новый клиент {type = 1}
        2 - передача сообщения {type = 2; int id; int b_id; char msg[100]}
    из сервера
        1 - прием id {}
        2+id_клиента - приём сообщений {type = 2+id_клиента; }
*/
int main(){
    key_t key = ftok("server.c", 1);
    msg messege;
    int id = msgget(key, 0777);
    if(id == -1){
        id = msgget(key, 0777|IPC_CREAT);
    }
    
    printf("[log]: сервер запущен\n");
    while (1){
        msgrcv(id, (void*)&messege, sizeof(msg) - sizeof(long), 0, 0);

    }
    printf("принял собщения окончани\n");
    msgctl(id, IPC_RMID, 0);

    return 0;
}
// клиент серверная модель взаимодействия

// есть равнозначные процессы
// каждый процесс знает адреса всех процессов

// добавляется сервер, адрес которого знает все

// допустим 1 хочет передать 6:
//   перед 6   от 1
// 1 -----> S -----> 6

// 1    2    3
// -----|-----
//      S
// -----|-----
// 4    5     6