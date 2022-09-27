#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/wait.h>

/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP02 - Exercício02 - 25/09/2021        |*/

double calcula_senx(double x, double xp ){ //Função para calcular o valor do seno
    double senx, ant, prox, prec;
    int i = 1;
    senx = x;
    do{
        ant = senx;
        senx = senx*(1-(xp/pow(i, 2)));
        prox = senx;
        //Pegar o valor absoluto para comparar a precisão
        if(ant>prox){
            prec = ant - prox;
        }
        else{
            prec = prox - ant;
        }
        i++;
    }while(prec>=pow(10,-12));

    return senx;
}

double calcula_cosx(double xp){ //Função para calcular o valor do cosseno
    double cosx = 1, ant, prox, prec;
    int i = 0;
    do{
        ant = cosx;
        cosx = cosx*(1-(4*xp/pow((2*i+1), 2)));
        prox = cosx;
        //Pegar o valor absoluto para comparar a precisão
        if(ant>prox){
            prec = ant - prox;
        }
        else{
            prec = prox - ant;
        }
        i++;
    }while(prec>=pow(10,-12)); //Se o valor absoluto for menor que precisão ele para

    return cosx;
}

void verifica_fork(int *pid){
    if(pid<0){
        perror("Fork: ");
        exit(1);
    }    
}

int main(int argc, char *argv[]){

    double x;      
    int pid = 0, pidC1 = 0, pidC2 = 0, cstatus;
    int fdc1[2], fdc2[2];                          //File descriptor para definir a saída e entrada nos pipes
    printf("Digite um ângulo em radiano entre 0 e π/2\n");
    scanf("%lf", &x);
    //Verificar se entrada é válida
    if(x>M_PI/2 || x<0){
        printf("Ângulo inválido! Fechando programa...\n");
        exit(1);
    }
    double xp = (x*x)/(M_PI*M_PI);                  //XP é um constante nos somatórios
    if (pipe(fdc1)<0 || pipe(fdc2)<0){             //Verificar erro nos pipes
        perror("Pipe: ");
        exit(1);
    }

    //Início da execução com processos pai e filho
    clock_t tic2 = clock(); //começa contagem

    pid = fork();
    verifica_fork(&pid);
    if(pid == 0){ //Filho escreve, fecha leitura
        double resultado_sen = 0;
        close(fdc1[0]);
        pidC1 = getpid();
        resultado_sen = calcula_senx(x, xp);
        write(fdc1[1], &resultado_sen, sizeof(resultado_sen));
        exit(0);
    }
    else{
        pid = fork();
        verifica_fork(&pid);
        if(pid == 0){ //Filho escreve, fecha leitura
            double resultado_cos = 0;
            close(fdc2[0]);
            pidC2 = getpid();
            resultado_cos = calcula_cosx(xp);
            write(fdc2[1], &resultado_cos, sizeof(resultado_cos));
            exit(0);        
        }
        else{ //Pai calcula tangente
            double senx = 0, cosx = 0, tanx = 0;
            //Aguardar cálculo dos filhos
            waitpid(pidC1, &cstatus, 0);
            waitpid(pidC2, &cstatus, 0);
            //0 leitura, 1 escrita
            //Pai apenas lê, deve-se fechar a escrita
            close(fdc1[1]);
            close(fdc2[1]);
            read(fdc1[0], &senx, sizeof(senx));
            read(fdc2[0], &cosx, sizeof(cosx));
            tanx = senx/cosx;
            printf("A tangente é %.20lf\n", tanx);
            clock_t toc2 = clock(); //termina contagem
            double tempo_execucao2 = (double)(toc2-tic2) / CLOCKS_PER_SEC;
            printf("%fs decorridos com execução com processos\n", tempo_execucao2);


        }
        
    }
    //Parte dedicada aos testes de precisão com tan() da math.h e análise do tempo com execução linear
    /*printf("A tan(x) da math.h calcula o valor: %.20lf \n", tan(x));

    double senx = 0, cosx = 0, tanx = 0;
    clock_t tic = clock(); 
    senx = calcula_senx(x, xp);
    cosx = calcula_cosx(xp);
    tanx = senx/cosx;
    printf("A tangente é %.20lf\n", tanx);
    clock_t toc = clock(); 
    double tempo_execucao = (double)(toc-tic) / CLOCKS_PER_SEC;
    printf("%fs decorridos com execução linear\n", tempo_execucao);*/

    return 0;
}

/*O programa foi escrito com funções para calcular o seno e cosseno com base nas fórmulas
fornecidas. A utilização de pipes foi essencial para garantir a comunicação entre pai (lê as
informações) e filhos(escreve o resultado do cálculo), surgiu a dúvida se há a necessidade da
utilização da waitpid() para garantir que o pai espere os filhos terminarem a execução, uma 
vez que o programa também funcionou sem a utilização dessa função. Utilizando a biblioteca 
math.h foi possível perceber que a precisão da fórmula somatória é muito próxima ao ressultado
obtido pela função tan(). Logo, o programa é capaz de calcular as funções seno, cosseno e 
tangente com precisão. Ademais, a função clock() foi responsável por mensurar o tempo de 
execução, rodando linearmente, o programa demora mais para executar o cálculo e é possível fazer 
o teste, só é necessário retirar o comentário da parte dedicada aos testes.*/


