#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* nvp[]) {
    for (size_t i = 0; nvp[i] != NULL; i++)
    {
        printf("%s\n", nvp[i]);
    }
    return 0;
}

// nvp - локальные переменные окружения
//
// вывод всех таких переменных