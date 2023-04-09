#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t id = fork();
    if (id == 0)
        printf("i doch\n my id --- %u\n id my pyrants --- %u\n\n", getpid(), getppid());
    else if (id > 0)
        printf("i papa\n my id --- %u\n id my pyrants id--- %u\n my doch id --- %u\n\n", getpid(), getppid(), id);
    else
        printf("erorr");
    return 0;
}

//          | 0 (дочь)
// fork() = | <0 (erorrrrrrrrrrrrrr)
//          | pid_дочь (отец)
//
// запускается, создает дочь(проц.), процесс родитель пишет: "id ребенка/его/родителя", 