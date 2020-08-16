#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define CANTIDAD_PARTIDA 	10
#define INTERVALO_PRODUCTO 	500
#define INTERVALO_PARTIDA 	1000
#define ROJO  			0
#define VERDE 			1
#define LARGO 			100

typedef struct {

	int cant;

}Reserva;

inicializarArray(Reserva reservas[]){

	int i;

	for(i=0;i<11;i++){

		reservas[i].cant=0;

	}

}

mostrarArray(Reserva reservas[]){

	int i;

	for(i=0;i<11;i++){

		printf("%d %d \n",i,reservas[i]);

	}

}

key_t creo_clave()
{
	key_t clave;
	clave = ftok ("/bin/ls", 33);
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave de semáforo\n");
		exit(0);
	}
	return clave;
}

int creo_semaforo()
{
	key_t clave = creo_clave();
	int id_semaforo = semget(clave, 1, 0600|IPC_CREAT); 
	if(id_semaforo == -1)
	{
		printf("Error: no puedo crear semaforo\n");
		exit(0);
	}
	return id_semaforo;
}

void inicio_semaforo(int id_semaforo, int valor)
{
	semctl(id_semaforo, 0, SETVAL, valor);
}

void levanta_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Levanta SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = 1; 
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);
}

void espera_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Espera SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = -1; 
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);

}

int main()
{
	char cadena[LARGO]; 
	int cant_reserva=0,nro_partida=0;
	FILE *reservador; 

	int id_semaforo;
	id_semaforo =  creo_semaforo();
	int numActual;

	Reserva reservas[11];


	while(1)
	{
		espera_semaforo(id_semaforo);

		reservador = fopen("lote.dat", "r");
		if (reservador!=NULL)
		{
			printf("\nCONSUMIMOS\n");

			printf("reservando partida numero %d \n",nro_partida);
			inicializarArray(reservas);
			while (!feof(reservador))
			{
				fscanf(reservador,"%s",cadena);
				//printf("%s\n", cadena);
				numActual = atoi(cadena);
				reservas[numActual].cant++;
				printf("%d\n",numActual);
				usleep(INTERVALO_PRODUCTO*1000);
				cant_reserva++;
			}
			nro_partida++;
			mostrarArray(reservas);
			fclose(reservador);
			if(cant_reserva>0)
			{
				printf("\nBORRAMOS\n");
				remove("lote.dat");
				cant_reserva=0;
			}
		}
		else
			perror ("Error al abrir lote.dat");
		printf("\nESPERAMOS\n");

		levanta_semaforo(id_semaforo);
		usleep(INTERVALO_PARTIDA*1000);
	};
	return 0;
}
