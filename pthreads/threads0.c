#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_THREADS 10

//tabela com os identificadores das threads
pthread_t tabela_thr[MAX_THREADS];

//tipo de dados e tabela com os parâmetros
typedef struct {
	int id;
	char *cadeia;
} thr_param_t;

thr_param_t param[MAX_THREADS];
//Tivemos que criar uma tabela para os parâmetros pois os passamos por referência.
//Assim, se só tivermos uma variável para os parâmetros, ao modificá-la estaremos
//modificando todas as que havíamos passado anteriomente, porque as threads não
//armazenam os valores e sim os endereços

void *funcao_thr(thr_param_t *p)
{
	int i;
//Esta é a função que as threads executam
//Como se pode ver não há maiores segredos
	printf("%s %d\n", p->cadeia, p->id);
	for( i = 0; i < 1000000000; i++ );

//Uma vez que terminamos, devolvemos o valor
	pthread_exit(&(p->id));
}

int main (void)
{
	time_t inicio, fim;
	double tempo;
	int i, *res;

//criamos as theads
	time( &inicio );
	printf("Criando as threads...\n");
	for(i=0; i < MAX_THREADS; i++ )
	{
		param[i].cadeia = strdup("Olá, sou a thread");
		param[i].id = i;
		pthread_create(&tabela_thr[i], NULL, (void*)&funcao_thr, (void*) & param[i]);
	}
//esperamos que as threads terminem

	printf("Threads criadas. Esperando que terminem...\n");
	for(i=0; i < MAX_THREADS; i++ )
	{
		pthread_join(tabela_thr[i], (void*)&res);
		printf("A thread %d retornou o valor %d\n", i, *res);
	}

//imprimimos uma mensagem e saimos do programa
	printf("Todas as threads terminadas!\n");

	time( &fim );
	tempo = difftime( fim, inicio );
	printf( "Tempo decorrido de cpu = %.2lf segundos\n", tempo );

	return(0);
}
