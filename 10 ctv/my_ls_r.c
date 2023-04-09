#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void recurseve_file_sistem_down(DIR* dir, char* name){
    struct dirent* dir_n;
    printf("%s:\n", name);

    while((dir_n = readdir(dir)) != NULL)
    {
        if((dir_n->d_name[0] != '.') && (dir_n->d_type != DT_DIR))
            printf("%s ", dir_n->d_name);
    }
    printf("\n\n");

    rewinddir(dir);

    while((dir_n = readdir(dir)) != NULL)
    {
        if((dir_n->d_name[0] != '.') && (dir_n->d_type == DT_DIR)){
            char name_n[100];
            strcpy(name_n, name);
            strcat(name_n, "/");
            strcat(name_n, dir_n->d_name);
            recurseve_file_sistem_down(opendir(name_n), name_n);
        }
    }
    closedir(dir);
}

int main(int n_arg, char* arg[]) {
    char name[100];
    strcpy(name, getenv ("PWD"));
    recurseve_file_sistem_down(opendir (getenv ("PWD")), name);

	return 0;
}