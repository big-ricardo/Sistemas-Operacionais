#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP11 - Exercício01 - 25/11/2021        |*/

typedef struct
{
    unsigned short dia;
    unsigned short mes;
    unsigned short ano;
    unsigned short hora;
    unsigned short min;
    unsigned short seg;
} data;

typedef struct
{
    char nome[8]; //nome do arquivo iniciado com o hexadecimal 0ebh são arquivos deletados
    char extensao[3];
    // Proteção
    unsigned short sistema; //arquivo do sistema
    unsigned short hidden; //arquivo oculto
    unsigned short archieved; //arquivo arquivado
    // Data e hora da criação
    data criacao;
    // Data do último acesso
    data acesso;
    // Tamanho
    unsigned long int tamanho;
    // Cluster inicial
    unsigned long int cluster;
} arquivo;

int main(int argc, char *argv[]){

    FILE *f;
    arquivo a;
    int contaLinha = 0;

    f = fopen("Diretorio.dat", "rb"); //Abrir o arquivo para leitura de binário

    if(!f){ //Verificar sucesso na abertura
        printf("Erro ao tentar abrir o arquivo!\n");
    }

    while(!feof(f)){
        fflush(stdin);
        fread(&a, sizeof(arquivo), 1, f);

        if(argc == 1){ //Item 1
            if(a.hidden == 0 && a.sistema == 0 && strcmp(a.nome,"0EBH") != 0){
                if(contaLinha == 0){
                    printf("%30sNome.extensão\n", "");
                }
                printf("%s.%s    ", a.nome, a.extensao);
                contaLinha++;

                if(contaLinha % 5 == 0){
                    printf("\n");
                }
            }
        }
        else
            if(strcmp(argv[1],"-a") == 0){ //Item 2
                if(a.hidden == 0 && a.sistema == 0 && strcmp(a.nome,"0EBH") != 0){
                    if(contaLinha == 0){
                        printf("Nome/Extensão/Sistema/Oculto/Arquivado/Tamanho/Clustler\n\n");
                    }
                    printf("%s %s %d %d %d %lu %lu\n\n", a.nome, a.extensao, a.sistema, a.hidden, a.archieved, a.tamanho, a.cluster);
                    contaLinha++;
                }
            }
            else 
                if(strcmp(argv[1],"-s") == 0){ //Item 3
                    if(contaLinha == 0){
                        printf("Nome.extensão (incluso sistema !=0):\n");
                    }
                    if(a.hidden == 0 && strcmp(a.nome,"0EBH") != 0){
                        printf("\n");
                        printf("%s.%s\n", a.nome, a.extensao);
                        contaLinha++;
                    }
                }
                else 
                    if(strcmp(argv[1],"-w") == 0){ //Item 4
                        if(a.hidden == 0 && a.sistema == 0 && strcmp(a.nome,"0EBH") != 0){
                        printf("%s.%s  ", a.nome, a.extensao);
                        contaLinha++;
                        
                        if((contaLinha) % 4 == 0 ){
                            printf("\n");
                        }
                        }
                    }
                    else{ //Item 5
                        printf("Opção inválida para dir\n");
                        break;
                    }
    }
    printf("\n");
    return 0;
}

/* Item 1: todos as informações foram impressas no formato nome.extensão de acordo com os pré-requisitos 
           (OEBH, proteção de sistema e Hidden !=0) menos o IO.SYS e MSDOS.SYS
   Item 2: todos os dados do arquivo foram impressos de acordo com os pré-requisitos 
           (OEBH, proteção de sistema e Hidden != 0) menos o IO.SYS e MSDOS.SYS
   Item 3: todos as informações foram impressas no formato nome.extensão de acordo com os pré-requisitos  
           (OEBH e Hidden != 0) menos o IO.SYS
   Item 4: todos as informações foram impressas no formato nome.extensão de acordo com os pré-requisitos 
           (OEBH e Hidden != 0) menos o IO.SYS e MSDOS.SYS
   Item 5: nada é impreso e o programa é fechado*/
