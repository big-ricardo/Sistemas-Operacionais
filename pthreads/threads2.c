//      threads1.c
//      
//      Copyright 2011 Carlos Minoru Tamaki <minoru@unifei.edu.br>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10

// Variáveis Globais
int x;

void *counter( void *tid )
{
	int i;
	/*Esta função imprime o identificador do thread e sai */
	printf( "I'm thread %ld, stating count\n", (long)tid );
	for( i = 0; i < 1000000; i++ ) x=x+1;
	printf( "I'm thread %ld, end count\n", (long)tid );
	pthread_exit( NULL );
}

int main(int argc, char **argv)
{
	/* Programa principal cria 10 threads e sai */
	pthread_t threads[ NUMBER_OF_THREADS ];
	int status, i;
	
	for( i = 0; i < NUMBER_OF_THREADS; i++ )
	{
		printf( "Main here. Creating thread %d \n", i );
		status = pthread_create( &threads[ i ], NULL, counter, (void *)(long)i );
		
		if( status != 0 )
		{
			printf( "Ooops, pthread_create returned error code %d \n", status );
			exit( -1 );
		}
	}
	for( i = 0; i < 100000000; i++ );
	printf( "Valor de X = %d \n", x );
	return 0;
}

