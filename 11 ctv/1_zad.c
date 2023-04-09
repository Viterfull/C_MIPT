#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

const int file_size_buf = 100;
int main(int n_arg, char* arg[]){
    srand(time(NULL));
    int fd = open("file.txt", O_RDWR);
    // perror("fopen() ");
    char* h =  (char*)mmap(NULL, file_size_buf, PROT_READ|PROT_WRITE, MAP_SHARED,
                  fd, 0);

    printf("быдло, |%s|\n", h);
    for (int i = 0; i < 30; i++)
    {
        h[i] = 32*2 + rand()%40;
    }
    
    printf("стадо, |%s|\n", h);
    munmap((void*) h, file_size_buf);
    close(fd);
    return 0;
}


// файлы отоброженные в памяти(memory_map_что-то там):
//     создаем копию файла, в адресном пространстве,
//     далее рабоатем, как с массивом(работает быстрее, чем просто читать)
//     1) open()
//     2)адрес в области адресного пространства - mmap(адрес, к которому мы присоединяем(null - никуда);
//                                                     число байт, которое мы хотим украсть; что хочу сделать; ....; offset с какого байта будет запись)


// открыть файл, прочитать его, вывести, изменить...