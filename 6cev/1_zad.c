#include <stdio.h>
#include <pthread.h>

int main(){
    pthread_t th_id = pthread_self();
    printf("thread_id: %lu \n", th_id);
}