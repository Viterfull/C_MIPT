#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <string.h>

void *thread_func(void *data){
    int* dat = (int*) data;
    dat[1]++;
    dat[2]++;
    dat[4]++;
    dat[5]++;
    return NULL;
}

int main(){
    key_t key = ftok("4_zad_1.c", 1);
    int fd = shmget(key, sizeof(int)*6, 0777);
    if(fd == -1) {
        fd = shmget(key, sizeof(int)*6, 0777|IPC_CREAT);
        int* data = shmat(fd, NULL, NULL);
        memset(data, 0, sizeof(int)*6);
    }
    int* data = shmat(fd, NULL, NULL);

    pthread_t th_id;
    pthread_create(&th_id, NULL, thread_func, (void*)(data));
    pthread_join(th_id, NULL);

    for (int i = 0; i < 6; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    shmdt(NULL);
    return 0;
}
