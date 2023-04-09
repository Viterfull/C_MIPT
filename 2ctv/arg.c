#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    if (argc > 1) printf("\n");
    return 0;
}

// argc - количество аргументов(по умалчанию 1)
// argv - все аргументы командной строки
//
// программа эхо (вывод == ввод) 