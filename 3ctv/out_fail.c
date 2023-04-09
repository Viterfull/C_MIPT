#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    umask(0);
    int fd = open("file", O_RDONLY);
    char buf[10];
    read(fd, buf, 10);
    printf("в файле содержится: %s \n", buf);
    close(fd);
    return 0;   
}