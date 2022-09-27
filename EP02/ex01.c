#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP02 - Exercício01 - 24/09/2021        |*/

void verifica_fork(int *pid){
    if(pid<0){
        perror("Fork: ");
        exit(1);
    }    
}

int main(int argc, char *argv[]){

    int pid = 0, i;
    int pidpai, pidCA, pidCB, pidCC, pidCD; /*Guardar pid do pai e dos filhos C(child)*/
    pidpai = getpid();
    pid = fork();
    verifica_fork(&pid); /*Conferir se o fork conseguiu criar um novo processo*/
    
/*Verificar se o processo rodando é o pai ou filho com base no pid(fork do filho retorna 0)*/
    
    if (pid == 0){
        pidCA = getpid();
        fork();
        /*Verificar qual filho está executando e garantir que CA crie apenas CC e CD*/
        if(getpid() == pidCA){
            fork();
            if(getpid() == pidCA){ //CA já criou os filhos, pode começar a contar
                for(i=1000;i<2000;i++){
                    printf("Filho CA(%d) contando: %d\n", pidCA, i);
                }
            }
            else{
                pidCD = getpid();
                verifica_fork(&pidCD);
                for(i=4000;i<5000;i++){
                    printf("Filho CD(%d) contando: %d\n", pidCD,i);
                }

            }
        }
        /* Se CA não está em execução, CC fica livre para iniciar a contagem*/
        else{
            pidCC = getpid();
            verifica_fork(&pidCC);
            for(i=3000;i<4000;i++){
                printf("Filho CC(%d) contando: %d\n", pidCC, i);
            }
        }

    }
    /*Execução do pai e o filho CB é criado*/
    else{
        pid = fork();
        verifica_fork(&pid);
        if(pid==0){
            pidCB = getpid(); 
            for(i=2000;i<3000;i++){
                printf("Filho CB(%d) contando: %d\n", pidCB, i);
            }  
        }
        else{
            for(i=0;i<1000;i++){
                printf("Pai(%d) contando: %d\n", pidpai, i);
            }
        } 
    }
    
    return 0;
}
/*As condicionais garantem a criação dos filhos antes do processo de contagem, contudo sem uma função
que controle a ordem de execução dos processos as contagens são feitas ao mesmo tempo, intercalando as
impressões no terminal de forma desordenada.*/
