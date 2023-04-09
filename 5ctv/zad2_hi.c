#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <string.h>
#include <sys/stat.h>
int main(){
    umask(0);
    char mes [] = "hello word";
    key_t key = ftok("zad2_hi.c", 1);
    int fd = shmget(key, 11, 0777|IPC_CREAT);
    char* data = (char*)shmat(fd, NULL, 0);
    strcpy(data, mes);
    shmdt(NULL);
    return 0;
}

// ipcs - показывает память
// ipcrm - удаляет память

// int shmctl(int shmid, int cmd, struct shmid_ds *buf) - удаляет память.

// 1) отпрправляет текст второй и удаляет
// 2) чат