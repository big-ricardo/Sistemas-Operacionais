#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x = 0, y = 0;
void funcao_1(void *threadarg){
x = 1;
    if(y==0){
        printf("1\n");
    }
    pthread_exit(0);
}

void funcao_2(void *threadarg){
    y = 1;
    if(x==0){
        printf("2\n");
    }
    pthread_exit(0);
}

int main(){
    pthread_t t1, t2;
    pthread_create(&t2, NULL, (void *)funcao_2, NULL);
    pthread_create(&t1, NULL, (void *)funcao_1, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}