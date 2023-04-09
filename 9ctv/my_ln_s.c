
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int n_arg, char* arg[]){
    symlink(arg[1], arg[2]);
    return 0;
}