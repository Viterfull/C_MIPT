#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int n_arg, char* arg[]){
    DIR* dir = opendir (getenv ("PWD"));
    struct dirent* dir_n;
    while((dir_n = readdir(dir)) != NULL)
    {
        if(!(dir_n->d_name[0] == '.'))
            printf("%s ", dir_n->d_name);
    }
    printf("\n");
	return 0;
}

// 1) ls -r
// 2) ls -l
// 3) ls


