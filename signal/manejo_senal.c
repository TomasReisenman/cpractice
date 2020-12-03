#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void trataSenhal (int numeroSenhal)
{
	printf ("Recibida senal\n");
}

main()
{
	signal (SIGUSR1, trataSenhal);
	printf("PID =%d\n", getpid());
	while (1)
	{
		printf("Espero 10 seg, soy PID %d\n", getpid());
		sleep (10);
		printf("Dejo de esperar\n");
	}
}


