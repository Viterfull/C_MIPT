#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>

int main(){
    key_t key = ftok("1.c", 1);
    int fd = shmget(key, sizeof(int)*3, 0777);
    if(fd == -1) {
        fd = shmget(key, sizeof(int)*3, 0777|IPC_CREAT);
        int* data = shmat(fd, NULL, NULL);
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }
    int* data = shmat(fd, NULL, NULL);
    data[0] += 1;
    data[2] += 1;
    printf ("[%d, %d, %d]\n", data[0], data[1], data[2]);
    shmdt(NULL);
    return 0;
}

// недостатки pipe
//     1) нет одновременного доступа к данным
//     2) умирает при неиспользовании
//     3) чтобы прочитать нужно записать
// новые
//     1) разделяемая память (shm)
//     2) симофоры (sem)
//     3) сообщения (msg)

// рассмотрим разделяющуюся память
//     писать перед этим umask(0)
//     key_t ftok(const char *pathname, int proj_id);  - создать ячейку
//     int shmget(key_t key, int size, int shmflg);  - либо создает память, либо плачет
//     void *shmat(int shmid, const void *shmaddr, int shmflg); - подключает область разделяемой памяти к процессу (возвращает указатель)
//     int shmdt(const void *shmaddr); - отключение памяти

// нужно написать
//     две программы, 

//     [счетчик запуска первой программы, счетчик запуска второй программы, счетсчик 1+2]

//     1) запуск. проверка бытия памяти