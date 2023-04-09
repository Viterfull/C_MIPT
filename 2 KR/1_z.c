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

char* names[100] = {0};
char out[100] = {0};
int n_of_names = 0;

void recurseve_file_sistem_down(DIR* dir, char* name){
    struct dirent* dir_n;
    // printf("%s:\n", name);

    while((dir_n = readdir(dir)) != NULL)
    {
        if(dir_n->d_type != DT_DIR){
            
            if(strcmp(dir_n->d_name, "..") && strcmp(dir_n->d_name, ".")) continue;
            names[n_of_names] = calloc(20, 1);

            strcpy(names[n_of_names], name);
            strcat(names[n_of_names], "/");
            strcat(names[n_of_names], dir_n->d_name);
            n_of_names++;
            // printf("%s ", dir_n->d_name);
        }
    }
    // printf("\n\n");

    rewinddir(dir);

    while((dir_n = readdir(dir)) != NULL)
    {
        if(strcmp(dir_n->d_name, "..") && (dir_n->d_type == DT_DIR)){
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
    char name[100] = {0};
    printf("\n%s\n", arg[1]);
    strcpy(name, arg[1]);

    recurseve_file_sistem_down(opendir (arg[1]), name);
    int n_ind = 0;
    struct stat stats, temp;
    for (int i = 0; i < n_of_names; i++)
    {
        stat(names[i],  &stats);

        if (out[i] == 1){


        for (int j = 0; j < n_of_names; j++)
        {
            if ((i != j) && out[j] == 0){
                stat(names[j],  &temp);
                if(temp.st_ino == stats.st_ino){ 
                    out[j] = 1;
                }
            }
        }
        
        }
        out[i] = 1;
        n_ind++;
    }
    printf("%d", n_ind);

    printf("Дириктории:\n");
    DIR* dir = opendir (getenv ("PWD"));
    struct dirent* dir_n;
    int flag = 0;
    while((dir_n = readdir(dir)) != NULL)
    {
        if(strcmp(dir_n->d_name, "..") && strcmp(dir_n->d_name, ".") && (dir_n->d_type != DT_DIR)){
            printf("\t%10s\n", dir_n->d_name);
            flag++;
        }
    }
    if(!flag){
        printf("нет директорий");
    }
    printf("\n");
    closedir(dir);
    for (int i = 0; i < n_of_names; i++)
    {
        free(names[i]);
    }
    
	return 0;
}