#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void trataSenhal (int);

void *funcionThread (void *parametro)
{
	signal (SIGUSR1, trataSenhal);
	pthread_exit ((void *)"listo");
}

main()
{
	//pid_t idProceso;
	pthread_attr_t 	atributos;
	pthread_t 		idHilo;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	pthread_create (&idHilo, &atributos, funcionThread, NULL);

	while (1)
	{
		sleep (1);
		kill (getpid(), SIGUSR1);
	}
}

void trataSenhal (int numeroSenhal)
{
	printf ("Recibida señal del padre\n");
}