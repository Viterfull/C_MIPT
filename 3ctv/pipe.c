#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int pipefd [2];
    pipe(pipefd);
    int a = 6, b;
    write(pipefd[1], &a, sizeof(int));
    read(pipefd[0], &b, sizeof(int));
    printf("метнул данные(%d) и получил обратно (%d)\n", a, b);
    
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;   
}