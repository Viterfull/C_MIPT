#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <string.h>
#include <sys/stat.h>

const int SIZE_MSG_BUF = 1000;

int main(){
    umask(0);
    key_t key = ftok("chel1.c", 1);
    int fd = shmget(key, SIZE_MSG_BUF, 0777|IPC_CREAT);
    char* data_msg_1 = (char*)shmat(fd, NULL, 0);
    memset(data_msg_1, '\0', SIZE_MSG_BUF);
    
    key = ftok("chel1.c", 2);
    fd = shmget(key, SIZE_MSG_BUF, 0777|IPC_CREAT);
    char* data_msg_2 = (char*)shmat(fd, NULL, 0);
    memset(data_msg_2, '\0', SIZE_MSG_BUF);
    

    char com;
    char msg[SIZE_MSG_BUF];
    while ((com=getchar ()) != 'q')
    {
        if (com == 'w'){
            gets(msg);
            strcat(data_msg_1, strcat(msg, "|"));
        }
        if (com == 'r'){
            int n_msg = 0;
            for (size_t i = 0; i < SIZE_MSG_BUF; i++)
            {
                if (data_msg_2[i] == '\0')
                {
                    if (n_msg == 0)
                    {
                        printf("сообщений не было");
                        break;
                    }
                    break;
                }
                if (n_msg == 0)
                {
                    n_msg++;
                    printf("%d:", n_msg);
                }
                
                if (data_msg_2[i] == '|')
                {
                    if (data_msg_2[i+1] == '\0') break;
                    n_msg++; i++;
                    printf("\n%d: ", n_msg);
                    continue;
                }
                printf("%c", data_msg_2[i]);
            }
            printf("\n");
            memset(data_msg_2, '\0', SIZE_MSG_BUF);
        }
    }


    shmdt(NULL);
    shmctl(fd, IPC_RMID, NULL);
    return 0;
}

// рассмотрим разделяющуюся память
//     писать перед этим umask(0)
//     key_t ftok(const char *pathname, int proj_id);  - создать ячейку
//     int shmget(key_t key, int size, int shmflg);  - либо создает память, либо плачет
//     void *shmat(int shmid, const void *shmaddr, int shmflg); - подключает область разделяемой памяти к процессу (возвращает указатель)
//     int shmdt(const void *shmaddr); - отключение памяти

