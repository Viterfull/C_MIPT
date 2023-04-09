#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int p = fork();
    if (p > 0)
        execvp(argv[1], argv+1);
    else if (p == 0){
        for (int i = 0; i < 1200; i++)
        {
            printf("%d\n", i);
        }
        
    } 
    else{
        printf("erorr");
    }
    return 0;
}

// дочь - шалава
// cын - счтитает до 15000
// батя - делает шляпы