#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/sem.h>



int main(){
    key_t key = ftok("2_zad.c", 1);
    int fd = semget(key, 1, 0777|IPC_CREAT);

    struct sembuf f = {0, -1, 0};
    semop(fd, &f, 1);
    printf("hi\n");
    return 0;
}




// работа систем файл и its 
// semget() - берет ключ с ftok(), количество симофоров, флаги

// систем файл ips
// A(s, n): s+=n                (>0)
// B(s, n): while(s<n){} s-=n   (<0)
// Z(s): while (s > 0){}        (0)

// вызывеются через semop(id, действия(структуры), количество используемой штуки)

// struct sembuf
