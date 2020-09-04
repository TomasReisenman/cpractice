#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <time.h>

#include <sys/sem.h>
#define ROJO 0
#define VERDE 1

#define CANTIDAD 1
#define CANTIDAD_TOTAL 10
#define DESDE 0
#define HASTA 10

#define CLAVE_BASE 34

typedef struct tipo_juego juego;

struct tipo_juego
{
  char* nombre_jugador[100];
  int numero_pensado;
  int estado_acierto;
};



int obtener_numero_aleatorio(int desde,int hasta)
{

	return  (rand()%(hasta-desde+1))+desde;

}


int* generarRandom(int desde, int hasta, int cantidad)
{
	/* * * El 'desde' no es incluido en la seleccion del numero aleatorio. Ejemplo: para obtener el valor '0' debo arrancar desde el valor '-1' * * */ 

	int n,num,i,j,hastaRand,temp;
	int* vector = (int*) malloc(cantidad*sizeof(int));
	
	desde--;
	if((hasta-desde) < cantidad)
	{		
		printf("deben haber mas numeros que cantidades, %d es menor que %d\n",(hasta-desde),cantidad);
		free(vector);
		exit (0);
		    
	}
    

	hastaRand = (hasta-desde)/cantidad ;
   
	
	temp = desde;
	
	for (n=0 ; n < cantidad ; n++)
	{	
		num = (rand()%(hastaRand)) + 1;
		vector[n] = temp + num;
		//printf("el numero es %d: %d =%d \n", vector[n],hastaRand,num);	
     		temp = temp + hastaRand;
	}

	//printf("Reordeno---------\n");	
	for (i=cantidad-1 ; i > 0 ; i--)
	{
		num = rand()%(i);
	 	j = vector[i];
		vector[i] = vector[num];
		vector[num] = j;
	}

	return vector;

}


key_t creo_clave(int r_clave)
{
	// Igual que en cualquier recurso compartido (memoria compartida, semaforos
	// o colas) se obtien una clave a partir de un fichero existente cualquiera
	// y de un entero cualquiera. Todos los procesos que quieran compartir este
	// memoria, deben usar el mismo fichero y el mismo entero.
	key_t clave;
	clave = ftok ("/bin/ls", r_clave);	
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave para memoria compartida\n");
		exit(0);
	}
	return clave;
}

void* creo_memoria(int size, int* r_id_memoria, int clave_base)
{
	void* ptr_memoria;
	int id_memoria;
	id_memoria = shmget (creo_clave(clave_base), size, 0777 | IPC_CREAT); 

	if (id_memoria == -1)
	{

		printf("No consigo id para memoria compartida\n");
		exit (0);
	}

	ptr_memoria = (void *)shmat (id_memoria, (char *)0, 0);

	if (ptr_memoria == NULL)
	{
		printf("No consigo memoria compartida\n");

		exit (0);
	}
	*r_id_memoria = id_memoria;
	return ptr_memoria;
}

//funcion que crea el semaforo
int creo_semaforo()
{
  key_t clave = creo_clave(CLAVE_BASE);
  int id_semaforo = semget(clave, 1, 0600|IPC_CREAT); 
  //PRIMER PARAMETRO ES LA CLAVE, EL SEGUNDO CANT SEMAFORO, EL TERCERO 0600 LO UTILIZA CUALQUIERA, IPC ES CONSTANTE (VEA SEMAFORO)
  if(id_semaforo == -1)
  {
      printf("Error: no puedo crear semaforo\n");
      exit(0);
  }
  return id_semaforo;
}

//inicia el semaforo
void inicia_semaforo(int id_semaforo, int valor)
{
	semctl(id_semaforo, 0, SETVAL, valor);
}

//levanta el semaforo
void levanta_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Levanta SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = 1; //incrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);
}

//espera semaforo
void espera_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Espera SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = -1; //decrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);

}

void llega_auto(int colas[],int vias)
{

	int agregado = 0;
	int cola_menor = 0;
	int index =0;	

	while(!agregado && index <vias )
	{
		index ++;

		if(colas[cola_menor] > colas[index])
		{
			cola_menor = index;
		}

		if(colas[cola_menor]==0)
		{
			agregado=1;
		}
	}

	colas[cola_menor] ++;

}



int main(int argc,char *argv[])
{
	srand(time(NULL));
	//juego *memoria = NULL;
	int id_memoria;
	int id_semaforo;
	int acerto = 0;
	int* vectorRandom; 
	int cantInt = 0;
 
	id_semaforo = creo_semaforo();
	int *vehiculos_en_cola = NULL;
	int cantidad_vias_disponibles =atoi(argv[1]);
	vehiculos_en_cola = (int*)creo_memoria(sizeof(int)*cantidad_vias_disponibles, &id_memoria, CLAVE_BASE);
	//vectorRandom = generarRandom(DESDE,HASTA,99);
	//printf("the time %d \n",time(NULL));

	//memoria = (juego*)creo_memoria(sizeof(juego)*CANTIDAD, &id_memoria, CLAVE_BASE);
	
	while(1)
	{
		espera_semaforo(id_semaforo);			
		llega_auto(vehiculos_en_cola,cantidad_vias_disponibles);

		int i;
		for(i = 0;i<cantidad_vias_disponibles;i++){

			printf("en la cola %d hay %d vehiculos \n ",i,vehiculos_en_cola[i]);
			sleep (1);
		}

		levanta_semaforo(id_semaforo);

	}

	shmdt ((char *)vehiculos_en_cola);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
