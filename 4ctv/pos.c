#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

const char* path = "1.fifo";
const int SIZE = 100;

int main(){
    umask(0);
    mkfifo(path, 0777);
    int fd = open(path, O_RDWR|O_NDELAY);
    char msg[SIZE];

    while (strcmp(fgets(msg, SIZE, stdin), "!q\n")){
        write(fd, msg, SIZE);
    }
    write(fd, "!q\n", SIZE);
    close(fd);
    return 0;
}