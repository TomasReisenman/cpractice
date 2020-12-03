#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define CANTIDAD 	2
#define PROCESO1	1
#define PROCESO2	2
#define ESPERA		5000


key_t creo_clave()
{
	key_t clave;
	clave = ftok ("/bin/ls", 33);	
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave para memoria compartida\n");
		exit(0);
	}
	return clave;
}


int creo_id_memoria(int size)
{
	int id_memoria;

	id_memoria = shmget (creo_clave(), size, 0777 | IPC_CREAT); 

	if (id_memoria == -1)
	{

		printf("No consigo id para memoria compartida\n");

		exit (0);

	}

	return id_memoria;
}

void* creo_memoria(int id_memoria)
{
	void* ptr_memoria;

	ptr_memoria = (void *)shmat (id_memoria, (char *)0, 0);

	if (ptr_memoria == NULL)
	{
		printf("No consigo memoria compartida\n");

		exit (0);
	}
	return ptr_memoria;
}


void trataSenhal (int numeroSenhal)
{
	static int cantidad=0;	
	printf ("\nRecibi %d senal\n", cantidad++);
}

int main(int argc, char *argv[])
{
	int i;	
	int nro_proceso = PROCESO1;	
	int *proceso = NULL;
	int id_memoria;
	signal (SIGUSR1, trataSenhal);
	printf("PID =%d\n", getpid());

	id_memoria = creo_id_memoria(sizeof(int)*CANTIDAD);
	proceso = (int*)creo_memoria(id_memoria);
	if(argc>1)
	{
		nro_proceso = atoi(argv[1]);	
	}
	proceso[nro_proceso-1]=getpid();

	while (1)
	{
		for(i=0; i<CANTIDAD; i++)
		{
			printf("PROCESO %d, PID %d\n", i, proceso[i]);
		}			
		printf("Espero %d mill, soy Proceso %d PID %d\n", ESPERA, nro_proceso, proceso[nro_proceso-1]);
		usleep (1000*ESPERA);
	
		if(nro_proceso==PROCESO1)
		{
			printf("Envio señal a PID %d\n", proceso[PROCESO2-1]);
			kill (proceso[PROCESO2-1], SIGUSR1);
		}
		else
		{
			printf("Envio señal a PID %d\n", proceso[PROCESO1-1]);
			kill (proceso[PROCESO1-1], SIGUSR1);
		}
		printf("Dejo de esperar\n");
	}
	return 0;
}


