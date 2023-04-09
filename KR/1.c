// напсать 1 программы
// я второй вар
// 1) написать программу, которая создает n процессов(арг ком строки), все, кроме 0 отсылают сигнал 0

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct msg{
    long type;
    int process_id;
} msg;

int main(int argc, char* argv[]){
    key_t key = ftok("2_zad_1.c", 1);
    int id;
    if((id = msgget(key, 0777)) == -1) id = msgget(key, 0777|IPC_CREAT);
    int n = atoi(argv[1]);
    pid_t ret_fork = 1;
    for (int i = 0; i < n; i++)
    {
        if (ret_fork != 0)
        {
            ret_fork = fork();
        }
    }
    msg message;
    switch (ret_fork)
    {
    case 0:
        message = (msg){1, (int)getpid()};
        msgsnd(id, (void*)&message, sizeof(msg) - sizeof(long), 0);
        printf("отправил сообщение: %d\n", getpid());
        return 0;
        break;
    
    default:
        sleep(1);
        for (int i = 0; i < n; i++)
        {
            msgrcv(id, (msg*)&message, sizeof(msg) - sizeof(long), 1, 0);
            printf("принял сообщение от %d\n", message.process_id); 
            sleep(0.1);
        }
        
        break;
    }
    // msgsnd(id, (void*)&((msg){1}), sizeof(msg) - sizeof(long), 0); // отправка сообщений
    // printf("ret: %ld\n", msgrcv(id, (void*)&message, sizeof(msg) - sizeof(long), 0, 0)); // принятие сообщений

    msgctl(id, IPC_RMID, 0);//удаление потока сообщений
    return 0;
}