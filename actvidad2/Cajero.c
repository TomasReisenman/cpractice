#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#include <sys/ipc.h>
#include <sys/sem.h>

#define CANTIDAD 10
#define DESDE 0
#define HASTA 10
#define LARGO 100



#define CANTIDAD_PARTIDA 	10
#define INTERVALO_PRODUCTO 	100
#define INTERVALO_PARTIDA 	5000
#define ROJO  			0
#define VERDE 			1

#define MIN_IMPORT 100
#define MAX_IMPORT 500

#define CHECK1 1
#define CHECK0 0


#define MIN_DEPOS  10
#define MAX_DEPOS  20

int obtener_numero_aleatorio(int desde,int hasta)
{

	return  (rand()%(hasta-desde+1))+desde;

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

void inicia_semaforo(int id_semaforo, int valor)
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

int main(int argc,char *argv[])
{
	int num;	
	int check;
	int n;
	int num_cajero=atoi(argv[1]);
	int max_depos;
	FILE *cargador; 
	srand(time(NULL));
	char cadena[LARGO]; 

	int id_semaforo;

	id_semaforo =  creo_semaforo();

	if(num_cajero == 1){

		inicia_semaforo(id_semaforo, VERDE);

	}

	while(1)
	{
		espera_semaforo(id_semaforo);
		max_depos= obtener_numero_aleatorio(MIN_DEPOS,MAX_DEPOS);
		sprintf(cadena,"cajero%d.dat",num_cajero );	
		cargador = fopen(cadena, "a");
		printf("cargando cajero  %d \n",num_cajero);

		if(cargador != NULL)
		{
			for (n=0; n<max_depos;n++)
			{	
				num = obtener_numero_aleatorio(MIN_IMPORT,MAX_IMPORT);
				check = obtener_numero_aleatorio(CHECK0,CHECK1);
				sprintf(cadena,"%d-%d \n", num,check);	
				printf("%d %d \n", num,check);	
				usleep(INTERVALO_PRODUCTO*1000);
				fprintf(cargador,"%s",cadena);
			}

			fclose(cargador);
		}
		else
		{
			perror ("Error al abrir lote.dat");
		}
		levanta_semaforo(id_semaforo);
		usleep(INTERVALO_PARTIDA*1000);



	};
	return 0;
}
