#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/sem.h>



int main(){
    key_t key = ftok("2_zad.c", 1);
    int fd = semget(key, 1, 0777|IPC_CREAT);

    printf("hi\n");
    struct sembuf f = {0, 1, 0};
    semop(fd, &f, 1);


    return 0;
}