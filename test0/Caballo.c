#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <time.h>

#include <sys/sem.h>
#define ROJO 0
#define VERDE 1

#define MIN_CONT_CABALLO 100
#define MAX_CONT_CABALLO 300
#define MIN_AV_CABALLO 10
#define MAX_AV_CABALLO 50

#define CLAVE_BASE 40


typedef struct tipo_pista pista;

struct tipo_pista
{
  int numeroCaballo;
  int metrosRecorridos;
  int metrosAlDisco;
  int accion; // 0 a evaluar , 1- siga corriendo 2 cruzo el disco inicia 1
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

void espera_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Espera SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = -1; //decrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);

}

void mostrar_pistas(pista pistas[],int cantidad)
{
	int i;
	for(i = 0;i<cantidad;i++){

		printf("Caballo numero %d \n",pistas[i].numeroCaballo);
		printf("Metros Recorridos  %d \n",pistas[i].metrosRecorridos);
		printf("Metros a Disco  %d \n",pistas[i].metrosAlDisco);
		printf("Accion  %d \n",pistas[i].accion);
		printf("///////////////////////// \n");
		//usleep(1000*1000);
	}
}

void avanza_caballo(pista pistas[],int numero_caballo)
{	
	int avance = 0;

	if(pistas[numero_caballo - 1].accion == 1)
	{
		avance = obtener_numero_aleatorio(MIN_AV_CABALLO,MAX_AV_CABALLO);
		printf("Caballo %d avanza %d \n",pistas[numero_caballo - 1].numeroCaballo,avance);
		pistas[numero_caballo -1].metrosRecorridos += avance; 
		pistas[numero_caballo -1].accion = 0;
	}

}


int  verificar_estado_caballos(pista pistas[],int cantidad)
{
	int ganador = 0;
	int i;

	for(i = 0;i<cantidad;i++){

		if(pistas[i].accion == 2)
		{
			ganador = pistas[i].numeroCaballo + 1;
			break;

		}

	}

	return ganador;

}

int main(int argc,char *argv[])
{
	srand(time(NULL));
	int id_memoria;
	int id_semaforo;
	pista *pistas = NULL;
	int cantidad_caballos = atoi(argv[1]);
	int numero_caballo = atoi(argv[2]);
	int hay_ganador = 0;
 
	id_semaforo = creo_semaforo();
	pistas  = (pista*)creo_memoria(sizeof(pista)*cantidad_caballos, &id_memoria, CLAVE_BASE);

	
	while(!hay_ganador)
	{
		espera_semaforo(id_semaforo);			
		avanza_caballo(pistas,numero_caballo);

		hay_ganador = verificar_estado_caballos(pistas,cantidad_caballos);
		mostrar_pistas(pistas,cantidad_caballos);
		levanta_semaforo(id_semaforo);

		usleep(1000*obtener_numero_aleatorio(MIN_CONT_CABALLO,MAX_CONT_CABALLO));

	}


	shmdt ((pista *)pistas);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
