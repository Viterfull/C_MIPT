#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    umask(0);
    int fd = open("file", O_CREAT|O_WRONLY, 0777);
    char a[10] = "1234567890";
    printf("записано %lu байт\n", write(fd, a, 10));
    close(fd);
    return 0;
}

// потоки:
//     0 - ввод/вывод
//     1 - вывод/ввод
//     2 - errors
//     3 - возможно наш поток
//
// флаги(формируется из побитовых сумм (|)) open:
//     есть три(не три) флага:
//         O_WRONLY(возожно не существует)
//         O_RDONLY
//         O_RDWR
//         O_CREAT(создает)
//         O_EXCL
//
//     права доступа первым аргументом
//         есть системные вызовы:
//             int open(const char *pathname, int flags) - создаем поток
    // read() - читаем с потока
    // write() - пишем в поток
    // close() - уничтожаем поток