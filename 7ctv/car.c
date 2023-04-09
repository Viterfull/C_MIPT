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

    semop(fd, &((struct sembuf){0, 1, 0}), 1); //добавляет машину

    printf("Я еду\n");

    sleep(3);
    printf("Я доехала до моста\n");

    if (semctl(fd, 1, GETVAL) <= 1){
        printf("кораблей нет или он один, еду\n");
        sleep(3);
        semop(fd, &((struct sembuf){0, -1, 0}), 1);
        printf("проехала мост\n");
    }
    else{
        printf("жду, пока проплывут\n");
        semop(fd, &((struct sembuf){1, 0, 0}), 1);
        printf("еду\n");
        semop(fd, &((struct sembuf){0, -1, 0}), 1);
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

// пока кораблей один И есть машины, мост согнут, машины едут, _______----___
// как только все машины проезжают или есть второй карабль, мост разогнут  ____/  \____

// мост разводится, когда к нему подплывает >=2 корабля
// пока запущен один корабль, он ждет карабля
// если караблей <2 то автомобиль без блакировки
// если караблей >=2 то авто не дигаются, карабли вигаются