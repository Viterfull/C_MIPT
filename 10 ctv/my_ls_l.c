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

int main(int n_arg, char* arg[]) {
    DIR* dir = opendir (getenv ("PWD"));

    struct dirent* dir_n;
    struct stat stats;
    struct tm *timeinfo;
    char tbuf[11];

    while((dir_n = readdir(dir)) != NULL) {
        if(!(dir_n->d_name[0] == '.')) {
            stat(dir_n->d_name,  &stats);
            printf("%10u %10lu %10s %10s %10lu "
            ,stats.st_mode, stats.st_nlink, getpwuid(stats.st_uid)->pw_name, getpwuid(stats.st_gid)->pw_name
            ,stats.st_size);
            
            strftime(tbuf, 11, "%d/%m/%Y", localtime(&stats.st_ctim.tv_sec));
            fprintf(stdout, "%10s ", tbuf);

            printf("%10s\n", dir_n->d_name);
        }
    }



    printf("\n");   

	return 0;
}