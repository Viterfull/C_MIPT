#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/sem.h>
#include <unistd.h>


int main(){
    key_t key = ftok("2_zad.c", 1);
    int fd;
    if((fd = semget(key, 2, 0777)) == -1) fd = semget(key, 2, 0777|IPC_CREAT);
    // 0 - машины 1 - карабли
    printf("Я плыву\n");
    semop(fd, &((struct sembuf){1, 1, 0}), 1); //добавляет крабль
    sleep(3);

    printf("я доплыл до моста\n");
    int car = semctl(fd, 0, GETVAL);

    if (car == 0){
        printf("машин нет, плыву\n");
        sleep(5);
        semop(fd, &((struct sembuf){1, -1, 0}), 1);
        printf("проплыл\n");
    }
    else{
        printf("жду второго корабля или когда проедут машины\n");
        while (semctl(fd, 0, GETVAL) != 0 && semctl(fd, 1, GETVAL) == 1){}
        printf("плыву\n");
        sleep(2);
        semop(fd, &((struct sembuf){1, -1, 0}), 1);
        printf("доплыл\n");
    }
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