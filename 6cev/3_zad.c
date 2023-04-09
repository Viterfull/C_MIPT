#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg){
    pthread_t th_id2 = pthread_self();
    printf("next thread: %lu \n", th_id2);
    (*(int*)arg)++;
    return NULL;
}

int main(){
    int d;
    d = 0;
    pthread_t th_id[5];
    printf("first thread: %lu \n", pthread_self());

    for (char i = 0; i < 5; i++)
    {
        pthread_create((pthread_t*)(th_id+i), NULL, thread_func, (void*)(&d));
    }

    for (char i = 0; i < 5; i++)
    {
        pthread_join(th_id[i], NULL);
    }

    printf("%d\n", d);
    return 0;
}