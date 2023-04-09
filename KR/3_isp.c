#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

typedef struct msg{
    long type;
    char buf[100];
} msg;

int main(int argc, char* argv[]){
    key_t key = ftok("2_zad_1.c", 1);
    int id;
    msg mes;
    char* arg[20] = {(char*)NULL};
    if((id = msgget(key, 0777)) == -1) id = msgget(key, 0777|IPC_CREAT);


    while (1)
    { 
        printf("принял команду размером %ld\n", msgrcv(id, (msg*)&mes, sizeof(msg) - sizeof(long), 1, 0)); // принятие
        char *istr;
        int i = 0;
        
        
        // Выделение первой части строки

        istr = strtok (mes.buf ," ");
        
        while (istr != NULL)
        {
            arg[i] = (char*)malloc(20);
            strcpy(arg[i], istr);
            i++;
            istr = strtok (NULL," ");
        }

        int p = fork();

        if (p == 0){
            execvp(arg[0], (arg+1));
            return 0;
        }       

        for (int j = 0; j < i; j++)
        {
            puts(arg[j]);
            free(arg[j]);
            arg[j] = NULL;
        }
        
    }
    

    msgctl(id, IPC_RMID, 0);//удаление потока сообщений
    return 0;
}