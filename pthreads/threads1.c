//      threads.c
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
#include <unistd.h>

#define NUMBER_OF_THREADS 10

void *print_hello_world( void *tid )
{
	long long int i;
	/*Esta função imprime o identificador do thread e sai */
	for( i=0; i<100000000; i++ );
	printf( "Hello World! Greetings from thread %ld \n", (long int)tid );
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
		status = pthread_create( &threads[ i ], NULL, print_hello_world, (void *)(long)i );
		
		if( status != 0 )
		{
			printf( "Ooops, pthread_create returned error code %d \n", status );
			exit( -1 );
		}
	}
	sleep(2);
	return 0;
}

