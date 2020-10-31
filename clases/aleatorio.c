#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#include <sys/ipc.h>
#include <sys/sem.h>

int obtener_numero_aleatorio(int desde,int hasta)
{

	return  (rand()%(hasta-desde+1))+desde;

}

int main(int argc,char *argv[])
{
	while(1)
	{
		printf("obtenes valor %d \n",obtener_numero_aleatorio(0,10));
	}

}
