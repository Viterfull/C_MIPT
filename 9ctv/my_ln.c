// жесткая связь что-то по типу количества файлов, которые ссылаются на одни и те же лог блоки
//     ln - создает жесткую связь
//     link() - ^
// мягкая связь(ярлык на винде):
//     ln -s - создает мягкую(сиволическую) связь
//     symlink() - ^

// unlink() - удаление

// напсать ln и ln -s

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int n_arg, char* arg[]){
    link(arg[1], arg[2]);
    return 0;
}