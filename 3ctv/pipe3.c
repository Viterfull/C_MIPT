#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[]) {
    int pipefd [2];
    pipe(pipefd);

    int id[3] = {0}, kol = 0, id_dot;
    char messege[30] = "", flux[40], id_str[12] = "", symbol;
    id[0] = fork();
    strcpy(messege, "i first dota");

    if (id[0] != 0){
        id[1] = fork();
        strcpy(messege, "i second dota");
        if (id[1] != 0)
        {
            id[2] = fork();
            strcpy(messege, "i thirt dota");
        }
    }
    
    switch (id[0] == 0||id[1] == 0||id[2] == 0)
    {
    case 1:
        //дочь
        sprintf(flux, "*%d*%s!", getpid(), messege);
        write(pipefd[1], &flux, strlen(flux));
        break;
    case 0:
        //отец или мать или я не знаю короче кто там главный, но это вот он
        while (kol < 3)
        {

            read(pipefd[0], &symbol, 1);
            if (symbol == '*') {
                kol+=1;
                while (read(pipefd[0], &symbol, 1)&&symbol != '*')
                {
                    strcat(id_str, &symbol);
                }
                memset(messege, 0, 30);
                while (read(pipefd[0], &symbol, 1)&&symbol != '!')
                {
                    strcat(messege, &symbol);
                }
                printf("от дочери(id = %s) получено сообщение: \"%s\"\n", id_str, messege);
                memset(id_str, 0, 8);
            }
        }
        break;
    }
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;   
}

// три процесса ---> пишет от кого и что

