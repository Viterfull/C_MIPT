// изменение длины файла
//     truncate()

// изменение текущей позиции
//     lseek()
// 2) программа, которая увеличивает размер файла и записывает

// есть файл с инфой

// увеличиваем

// изменяем указатель на новые байты

// записываем

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    char st[] = "hello word\n";
    int fd = open("file.txt", O_WRONLY);
    ftruncate(fd, 11);
    lseek(fd, -1, SEEK_END);
    write(fd, st, 11);
    close(fd);
    return 0;
}