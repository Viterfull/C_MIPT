#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <time.h>

int file_filter (char name[1000], int len)
{
    struct dirent *current = NULL;
    int n = 0;
    DIR *dir = opendir (name);

    for (current = readdir (dir); current != NULL; current = readdir (dir))
    {
        if (strcmp (current->d_name, ".") && strcmp (current->d_name, ".."))
        {
            if (current->d_type == DT_DIR)
            {
                strcat (name, "/");
                strcat (name, current->d_name);
                n += file_filter (name, len);
            }
            else{
                n++;
            }
        }
    }
    closedir (dir);
    char *name_len    = strrchr (name, '/');
    if ((int) (name_len - name) >= len)
        memset (name_len, '\0', strlen (name) - (int) (name_len - name));
    rewinddir (dir);
    return n;
};

int Link_filter (char name[1000], int len)
{
    struct dirent *current = NULL;
    int n = 0;
    struct stat buf = {};
    DIR *dir = opendir (name);

    for (current = readdir (dir); current != NULL; current = readdir (dir))
    {
        if (strcmp (current->d_name, ".") && strcmp (current->d_name, "..") && current->d_type)
        {    
            stat (current->d_name, &buf);
            if (buf.st_nlink > 1)
                n++;
            if (current->d_type == DT_DIR)
            {
                strcat (name, "/");
                strcat (name, current->d_name);
                n += Link_filter (name, len);
            }
        }
    }
    closedir (dir);
    char *name_len    = strrchr (name, '/');
    if ((int) (name_len - name) >= len)
        memset (name_len, '\0', strlen (name) - (int) (name_len - name));
    rewinddir (dir);
    return n;
};

int main (int argc, char *argv[])
{
    char name[1000] = {};
    sprintf (name, argv[1]);
    printf ("всего файлов в директориях: %d\n", file_filter (name, strlen (name)));
    printf ("файлов с жеткими файлами: %d\n", Link_filter (name, strlen (name)));
    printf ("директории:\n");
    DIR *dir    = opendir (name);
    struct dirent *current  = NULL;
    for (current = readdir (dir); current != NULL; current = readdir (dir))
    {
        if (current->d_type == DT_DIR && strcmp (current->d_name, ".") && strcmp (current->d_name, ".."))
            printf ("%s\n", current->d_name);
    }    
    closedir (dir);

    return 0;
}