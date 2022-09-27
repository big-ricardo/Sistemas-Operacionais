/*
COM120 - Sistemas Operacionais
EP03 - 09/09/19

Nome: Rafael Greca Vieira               Matrícula: 2018000434
Nome: João Marcos Calixto Moreira       Matrícula:2018009636
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define C 7

//DECLARA SEMAFORO PASSAGEIRO
sem_t passageiro;

//DECLARA SEMAFORO CARRINHO
sem_t carrinho;

//DECLARA SEMAFORO ANDANDO
sem_t andando;

//DECLARA SEMAFORO MUTEX
sem_t mutex;

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

    Npass++;

    if (Npass == C){
        //Se chegar no máximo de passageiros no carrinho
        //O semáforo carrinho vai ser liberado
        sem_post(&carrinho);
        //fecha semaforo andando
        sem_wait(&andando);
        //libera semaforo mutex
        sem_post(&mutex);

    }else{
        //fecha semaforo andando
        sem_wait(&andando);
        //libera semaforo mutex
        sem_post(&mutex);
    }

  }

}

void *Carrinho(){

    while(1){

        sem_wait(&carrinho);
        passeia();
        Npass = 0;

        for(int i = 0; i<C; i++){

            sem_post(&andando);
            sem_post(&passageiro);

         }
    }
}

int main(void){

    sem_init(&passageiro,0,C);
    sem_init(&carrinho,0,0);
    sem_init(&andando,0,0);
    sem_init(&mutex,0,1);

    //td1 = thread carrinho
    //td2 = thread passageiro
    pthread_t td1, td2;
    int thread_id[2];

    pthread_create(&td1, NULL, Carrinho, (void *)&thread_id[0]);
    pthread_create(&td2, NULL, Passageiro, (void *)&thread_id[1]);

}
