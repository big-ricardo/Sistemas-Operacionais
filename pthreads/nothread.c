/*
 * sem título.c
 * 
 * Copyright 2013 Carlos Minoru Tamaki <professorcco@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <time.h>
#include <unistd.h>

void contador ( int x )
{
	int i;
	printf( "Chamada da função contador %d\n", x );
	for( i = 0; i < 1000000000; i++ );
}

int main(int argc, char **argv)
{
	time_t inicio, fim;
	double tempo;
	int i;

	time( &inicio );
	printf( "Processo sem threads: \n\n" );
	for( i = 0; i < 5; i++)
		contador( i );
	//usleep(3000000);
	printf( "Contagem encerrada!\n" );

	time( &fim );
	tempo = difftime( fim, inicio );
	printf( "Tempo decorrido de cpu = %.2lf segundos\n", tempo );
	return 0;
}

