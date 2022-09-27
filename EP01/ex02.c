#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP01 - Exercício02 - 16/09/2021        |*/

int main(int argc, char *argv[]){

    int pid = 0, i;
    int pidpai, pidfilho, statusfilho;
    pidpai = getpid();
    pid = fork();
/*Conferir se o fork conseguiu criar um novo processo*/
    if(pid<0){
        perror("Fork");
        return 1;
    }
/*Verificar se o processo rodando é o pai ou filho com base no pid(fork do filho retorna 0)*/
/*Usar laço for para printar o status repetidamente do pai e do filho*/

    if (pid == 0){
        pidfilho = getpid();
        for(i=0;i<50;i++){
        printf("Sou processo filho!!! Meu PID é %d e o PID do meu pai é %d\n", pidfilho, pidpai);
        }
    }
/*incluir a função waitpid para forçar o pai a esperar o fiho terminar as impressões*/   
    else{
        waitpid(pid, &statusfilho, 0);
        for(i=0;i<30;i++){
        printf("Sou o processo pai!!!Meu PID é %d\n", pidpai);
        }
    }
    return 0;
}
/*A variável pid recebe o PID do filho como retorno do fork(), ao rodar o pai pela
primeira vez (fork do pai !=0) a condicional else executa a função waitpid, o 
processo pai espera a execução do filho(impressões do PID com laço for), após a 
execução do filho, o pai prossegue com as impressões e retorna o 0 (execução sem erros)*/