#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP04 - Exercício01 - 10/10/2021        |*/
#define NUM_THREADS 1
#define C 5

//Declaração dos semáforos
sem_t passageiro, carrinho, andando, mutex;
int Npass = 0;

void passeia(){
    sem_wait(&andando);
    sem_post(&carrinho);
    sem_wait(&passageiro);
}

void *Passageiro(){

  while(1){
    //fecha o semaforo de passageiro
    sem_wait(&passageiro);
    //fecha semaforo mutex
    sem_wait(&mutex);
    Npass++; //enchendo carrinho

    if (Npass == C){
        //Se chegar no máximo de passageiros no carrinho
        //O semáforo carrinho vai ser liberado
        sem_post(&carrinho);
        //fecha semaforo andando
        sem_wait(&andando);
        //libera semaforo mutex
        sem_post(&mutex);
    }
    else{
        //fecha semaforo andando
        sem_wait(&andando);
        //libera semaforo mutex
        sem_post(&mutex);
    }
  }
  return NULL;
}

void *Carrinho(){
    while(1){
        sem_wait(&carrinho);
        passeia();
        Npass = 0; //esvaziando carrinho

        for(int i = 0; i<C; i++){
            sem_post(&andando);
            sem_post(&passageiro);
         }
    }
  return NULL;
}

int main(){
    sem_init(&passageiro,0,C);
    sem_init(&carrinho,0,0);
    sem_init(&andando,0,0);
    sem_init(&mutex,0,1);

    //Vetor com o Thread 0(carrinho) e Thread 1(passageiro)
    pthread_t threads[NUM_THREADS];
    int thread_id[2];

    pthread_create(&threads[0], NULL, Carrinho, (void *)&thread_id[0]);
    pthread_create(&threads[1], NULL, Passageiro, (void *)&thread_id[1]);
  return 0;
}
