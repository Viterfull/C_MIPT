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
    data[1] += 1;
    data[2] += 1;
    printf ("[%d, %d, %d]\n", data[0], data[1], data[2]);
    shmdt(NULL);
    return 0;
}