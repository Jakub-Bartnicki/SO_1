#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)

int counter = 0;
pthread_mutex_t accum_mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* _arg){
    while(1){
        pthread_mutex_lock(&accum_mutex);
        counter++;
        pthread_mutex_unlock(&accum_mutex);
    }

    return NULL;
}

void* thread2(void* _arg){
    int x = 0;
    while(1){
        printf("%d\n", counter);
    }

    return NULL;
}

int main()
{   
    pthread_t th1, th2;

    errno = pthread_create(&th1, NULL, thread1, NULL);
    test_errno("Failed pthread_create");
    errno = pthread_create(&th2, NULL, thread2, NULL);
    test_errno("Failed pthread_create");

    errno = pthread_join(th1, NULL);
    test_errno("pthread_join");
    errno = pthread_join(th2, NULL);
    test_errno("pthread_join");
    
    return 0;
}
