#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[]) {
    
    const char *path = "./1.fifo";
    char buf[3];

    int id = fork();
    if(id){
        mkfifo(path, 0777);
        int fd = open(path, O_WRONLY);
        write(fd, "Hi", 3);
        close(fd);
    } else {
        int fd = open(path, O_RDONLY);
        read (fd, buf, 3);
        printf("%s\n", buf);
        close(fd);
    }
    return 0;
}

// создаем именованый pipe
// связываем через форк
// в один печатаешь, выводится в другой

// два exe  s str (send)
//          r str (read)