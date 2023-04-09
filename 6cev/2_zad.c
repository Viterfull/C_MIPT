// pthread_self
// pthread_create
// pthread_join
// Это функции для счетчика в проге
// 1. Просто вывести Id нити
// 2. Вывести id нити, создать еще одну нить и вывести ее id
// Каждая нить должна прибавить единицу к переменной (типа первая нить отработала прибавила единицу и вторая также)
// 3. Тоже самое, что и 2, только нитей должно быть 5 и у каждый разные id
// 4. С помощью этой всей хуйни модернизировать 1 или хз какую прогу с предыдущего семинара
// Вот так
#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg){
    pthread_t th_id2 = pthread_self();
    printf("next thread: %lu \n", th_id2);
    (*(int*)arg)++;
    return NULL;
}

int main(){
    int i;
    i = 0;
    pthread_t th_id;
    printf("first thread: %lu \n", pthread_self());
    int create = pthread_create(&th_id, NULL, thread_func, (void*)(&i));
    i++;
    create = pthread_join(th_id, NULL);
    printf("%d\n", i);
    return 0;
}