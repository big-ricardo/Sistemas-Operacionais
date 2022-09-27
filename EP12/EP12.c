#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>

/*|Matheus Martins Batista (2019005687) - Sistemas Operacionais (COM120) |
  |Ciências da Computação (CCO) - EP12 - Exercício01 - 05/12/2021        |*/

//Definir os structs utilizados ao decorrer do código
typedef struct cluster {

    char dados[512];
    unsigned long int prox;

} cluster;

int v_clusters[100];

typedef struct data {

    unsigned short dia;
    unsigned short mes;
    unsigned short ano;
    unsigned short hora;
    unsigned short min;
    unsigned short seg;

} data;

typedef struct arquivos {

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

int main() {
    cluster ctr;
    FILE *arq;
    arquivo a, arq_ext4;
    int qtd_cluster = 0;
    arq = fopen("Disco.dat", "rb");

    //Buscar apenas o arquivo EXT4.TXT no Disco.dat
    while (!feof(arq)) {
        fflush(stdin);
        fread(&a, sizeof (arquivo), 1, arq);

        if (!strcmp(a.nome, "EXT4") && !strcmp(a.extensao, "TXT")) {
            arq_ext4 = a;
            break;
        }
    }

    //Registrar o tamanho do arquivo EXT4.TXT e o cluster atual
    unsigned long int cluster_atual = arq_ext4.cluster;
    unsigned long int tam_arq = arq_ext4.tamanho;

    while (!feof(arq)) {
        fseek(arq, sizeof (cluster) * cluster_atual, SEEK_SET);
        fread(&ctr, sizeof (cluster), 1, arq);
        v_clusters[qtd_cluster] = cluster_atual;

        if (ctr.prox) {
            cluster_atual = ctr.prox;
            qtd_cluster++;
            printf("%s", ctr.dados);
            tam_arq -= 512;

        } else {
            qtd_cluster++;

            for (int i = 0; i < tam_arq; i++) {
                printf("%c", ctr.dados[i]);
            }
            break;
        }
    }

    printf("\nQuantidade de clusters: %d\n", qtd_cluster);
    printf("Tamanho do arquivo: %lu\n", arq_ext4.tamanho);
    fclose(arq);
}
