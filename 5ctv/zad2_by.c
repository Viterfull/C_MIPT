#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <string.h>
#include <sys/stat.h>
int main(){
    umask(0);
    char mes [11];
    key_t key = ftok("zad2_hi.c", 1);
    int fd = shmget(key, 11, 0777);
    char* data = (char*)shmat(fd, NULL, 0);
    strcpy(mes, data);
    printf("%s\n", mes);
    shmdt(NULL);
    shmctl(fd, IPC_RMID, NULL);
    return 0;
}