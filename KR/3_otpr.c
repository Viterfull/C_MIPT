// 3) написать две проги, первая передает команды, вторая исполняет
// 3.2) сделать через сообщения 

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct msg{
    long type;
    char buf[100];
} msg;

int main(int argc, char* argv[]){
    key_t key = ftok("2_zad_1.c", 1);
    int id;
    char mes[100];
    msg s;
    s.type = 1;
    if((id = msgget(key, 0777)) == -1) id = msgget(key, 0777|IPC_CREAT);
    // msgrcv(id, (msg*)&message, sizeof(msg) - sizeof(long), 1, 0); // принятие
    while (1)
    {
        fgets(mes, 100, stdin);
        mes[strlen(mes)-1] = ' ';
        strcpy(s.buf, mes);
        msgsnd(id, (void*)&s, sizeof(msg) - sizeof(long), 0); //отправлка
    }
    

    msgctl(id, IPC_RMID, 0);//удаление потока сообщений
    return 0;
}