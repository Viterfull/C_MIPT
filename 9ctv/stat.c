// что такое файловая система?
// - часть операционной системы, которая эффективно работает с помощью интерфейса с данными во внешней памяти

// в unix есть n типов файлов:
//     - регулярный файл (что записали, то и сохраняется)
//     - директории (образуют дерево каталогов) (не регулярный)
//     - FIFO (когда открываем, создается именованный pipe)
//     - файлы устройств 
//     - сокеты (сетевые штуки)
//     - файлы связи (link)

// операции над файлами
//     последовательный доступ:
//         - чтение порици (read)
//         - запись порции (write)
//         - позиционарирование на начале(rewind)
//     прямой доступ:
//         - чтение порици (read)
//         - запись порции (write)
//         - позиционарирование куда хочешь (seek)
//     p.s:
//         - new
//         - free
//         - еще что-то, не успел

// p.s: есть int create();

// атрибуты:
//     - stat()
//     - fstat()
//     - lstat()
//     дают атрибуты файлов и т.д --^

// 1)написать программу, которая принимает путь к файлу и выводит его отребуты

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int n_arg, char* arg[]){
    struct stat stats;
    stat(arg[1],  &stats);
    printf("dev_t: %llu\n",     stats.st_dev);         
    printf("ino_t: %llu\n",     stats.st_ino); 
    printf("mode_t: %llu\n",    stats.st_mode);      
    printf("nlink_t: %llu\n",   stats.st_nlink);       
    printf("uid_t: %llu\n",     stats.st_uid);     
    printf("gid_t: %llu\n",     stats.st_gid);      
    printf("dev_t: %llu\n",     stats.st_rdev);       
    printf("off_t: %llu\n",     stats.st_size);        
    printf("blksize_t: %llu\n", stats.st_blksize);     
    printf("blkcnt_t: %llu\n",  stats.st_blocks);   
    printf("st_atime: %llu\n", stats.st_atim.tv_sec);
    printf("st_mtime: %llu\n", stats.st_mtim.tv_sec);
    printf("st_ctime: %llu\n", stats.st_ctim.tv_sec);
    //
    return 0;
}