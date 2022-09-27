#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP01 - Exercício02 - 16/09/2021        |*/

int main(int argc, char **argv){
    
    int pid = fork();
    
    if(pid == 0){
        fork();
        fork();
    }
    else{
        fork();
    }

    printf("PID do processo %d\n", getpid());
    return 0;
}

/*Um printf foi utilizado para identificar o PID do processo em execução e, com isso,
foi possível verificar a presença de 6 processos criados ao decorrer da execução do 
código. O primeiro filho (C1) é criado na linha 10, o pai prossegue com a execução 
e entra na condicional else (linha 16), criando o filho 2 (C2). Por outro lado, o 
C1 entra na condicional if (linha12) e cria mais dois processos (C3) e (C4). O 
processo C3 é reponsável pela criação de C5. Logo, P->C1 e C2 | C1-> C3 e C4 | C3->C5.*/