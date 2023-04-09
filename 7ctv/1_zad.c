#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include "sim.h"

int main(){
    init();
    p();
    printf("\033[1;32mHi\033[0m\n");
    del();
    return 0;
}

// рассмотрим синхронизацию процессов(пример синхронизация нитей(join синхронизирует нить исполнения), нить бляяяяяяяяяяя)

// симофор дейкстры
// сегодня рассмотрим симофор(угарное название) - целая неотр. переменная s >= 0. в начале s = 0.
// разрешены две операции. 

// p: while (s == 0) block; s--;
// v: s++

// Задание: реальзовать симофор.