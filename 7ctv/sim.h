#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>


void init(){
    key_t key = ftok("sim.h", 1);
    int fd = shmget(key, 1, 0777|IPC_CREAT);
    char* s = (char*)shmat(fd, NULL, 0);
    *s = 0;
}

void p(){
    key_t key = ftok("sim.h", 1);
    int fd = shmget(key, 1, 0777);
    char* s = (char*)shmat(fd, NULL, 0);
    
    while (*s==0){
    }
    (*s)--;
}

void v(){
    key_t key = ftok("sim.h", 1);
    int fd = shmget(key, 1, 0777);
    char* s = (char*)shmat(fd, NULL, 0);
    (*s)++;
}

void del(){
    key_t key = ftok("sim.h", 1);
    int fd = shmget(key, 1, 0777);
    shmdt(NULL);
    shmctl(fd, IPC_RMID, NULL);
}
// p: while (s == 0) block; s--;
// v: s++
