#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const char *path = "1.fifo";
const int SIZE = 100;

int main(){
    int fd = open(path, O_RDONLY);
    char msg[SIZE];
    while (read(fd, msg, SIZE)||strcmp(msg, "!q\n")){
        printf("%s", msg);
    }  
    printf("был произведен выход\n");
    close(fd);
    return 0;
}