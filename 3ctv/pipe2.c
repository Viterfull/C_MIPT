#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int pipefd [2];
    pipe(pipefd);
    // write(pipefd[1], st_in, 6);
    // read(pipefd[0], st_out, 6);
    // printf("метнул данные(%s) и получил обратно (%s)\n", st_in, st_out);
    char st[6];
    int id = fork();
    char poslan[] = "12345";
    int bit;
    switch (id == 0)
    {
    case 1:
        read(pipefd[0], st, 6);
        printf("дочь получила последние в виде %s\n", st);
        break;
    case 0:
        //отец
        bit = write(pipefd[1], poslan, 6);
        printf("отец записал %u байт в сообщении %s\n", bit, poslan);
        break;
    }
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;   
}