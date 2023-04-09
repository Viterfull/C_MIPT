
// 2) создает файл, в который записывает все переенные окружения сеанса

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[], char* nvp[]) {
    umask(0);
    int fd = open("file.txt", O_CREAT|O_WRONLY, 0777);
    char n = '\n';
    for (size_t i = 0; nvp[i] != NULL; i++)
    {
        printf("записано %s(%lu) байт\n", nvp[i], write(fd, nvp[i], strlen(nvp[i])));
        write(fd, &n, 1);
    }
    
    close(fd);
    return 0;
}