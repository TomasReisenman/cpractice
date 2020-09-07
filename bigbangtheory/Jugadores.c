#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <time.h>
#include <string.h>

#include <sys/sem.h>
#define ROJO 0
#define VERDE 1

#define CANTIDAD 3
#define CANTIDAD_TOTAL 10
#define DESDE 0
#define HASTA 10
#define LARGO_NOMBRE 100

#define CLAVE_BASE 40

typedef struct tipo_panel panel;

struct tipo_panel
{
  int jugador1;
  int jugador2;
  int estado; // 0 = no jugo nadie, 1 = gano 1 , 2 = gano 2 
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

int decidir_ganador(int primer_jugada,int segunda_jugada)
{

	int resultado = 0;


	switch(primer_jugada)
	{

		//Piedra
		case 1:
			switch(segunda_jugada)
			{

				//Piedra
				case 1:
					resultado = 0;
					break;
				//Papel
				case 2:
					resultado = 2;
					break;
				//Tijeras
				case 3:
					resultado = 1;
					break;
				//Lagarto
				case 4:
					resultado = 1;
					break;
				//Spock
				case 5:
					resultado = 2;
					break;


			}	

			break;
		//Papel
		case 2:
			switch(segunda_jugada)
			{

				//Piedra
				case 1:
					resultado = 1;
					break;
				//Papel
				case 2:
					resultado = 0;
					break;
				//Tijeras
				case 3:
					resultado = 2;
					break;
				//Lagarto
				case 4:
					resultado = 2;
					break;
				//Spock
				case 5:
					resultado = 1;
					break;


			}	

			break;
		//Tijeras
		case 3:
			switch(segunda_jugada)
			{

				//Piedra
				case 1:
					resultado = 2;
					break;
				//Papel
				case 2:
					resultado = 1;
					break;
				//Tijeras
				case 3:
					resultado = 0;
					break;
				//Lagarto
				case 4:
					resultado = 1;
					break;
				//Spock
				case 5:
					resultado = 2;
					break;


			}	

			break;
		//Lagarto
		case 4:
			switch(segunda_jugada)
			{

				//Piedra
				case 1:
					resultado = 2;
					break;
				//Papel
				case 2:
					resultado = 1;
					break;
				//Tijeras
				case 3:
					resultado = 2;
					break;
				//Lagarto
				case 4:
					resultado = 0;
					break;
				//Spock
				case 5:
					resultado = 1;
					break;


			}	

			break;
		//Spock
		case 5:
			switch(segunda_jugada)
			{

				//Piedra
				case 1:
					resultado = 1;
					break;
				//Papel
				case 2:
					resultado = 2;
					break;
				//Tijeras
				case 3:
					resultado = 1;
					break;
				//Lagarto
				case 4:
					resultado = 2;
					break;
				//Spock
				case 5:
					resultado = 0;
					break;


			}	

			break;
	

	}
	return resultado;
}



void  inicializar_paneles(panel paneles[],int cantidad)
{
	int i;
	for(i = 0;i<cantidad;i++){

		paneles[i].jugador1 = 0;	
		paneles[i].jugador2 = 0;	
		paneles[i].estado = 0;	
	}

}

//int primer_panel_sin_juego(panel paneles[],int cantidad)
//{
//	int encontrado  = 0;
//	int count = 0;
//
//	while(encotrado = 0 && count < cantidad)
//	{
//
//		if(paneles[count].estado == 0)
//		{
//			encontrado = 1;
//			return count;
//		}
//		else
//		{
//			count ++;
//		}
//	}
//
//	return -1;
//
//}


//int main()
int main(int argc,char *argv[])
{
	srand(time(NULL));
	
	int id_memoria;
	int id_semaforo;
	panel *paneles = NULL;
	char jugadas[][100] = {"NADA","PIEDRA","PAPEL","TIJERAS","LAGARTO","SPOCK"};
	int resultado;
	id_semaforo = creo_semaforo();
	int panel_actual = 0;
	int jugada = 0;
	int numero_jugador = atoi(argv[1]);

	paneles = (panel*)creo_memoria(sizeof(panel)*CANTIDAD, &id_memoria, CLAVE_BASE);

	if(numero_jugador == 1)
	{
		inicia_semaforo(id_semaforo, VERDE);
		inicializar_paneles(paneles,CANTIDAD);
	}


	while(panel_actual <3)
	{
		espera_semaforo(id_semaforo);			


		if(numero_jugador == 1 && paneles[panel_actual].jugador1  == 0)
		{
			jugada = obtener_numero_aleatorio(1,5); 
			printf("Jugador %d eligio %s \n",numero_jugador,jugadas[jugada]);
			paneles[panel_actual].jugador1  = jugada;	
		}

		if(numero_jugador == 2 && paneles[panel_actual].jugador2  == 0)
		{
			jugada = obtener_numero_aleatorio(1,5); 
			printf("Jugador %d eligio %s \n",numero_jugador,jugadas[jugada]);
			paneles[panel_actual].jugador2  = jugada;	
		}

		if(paneles[panel_actual].jugador1 != 0 && paneles[panel_actual].jugador2 != 0  )
		{
			paneles[panel_actual].estado  = decidir_ganador(paneles[panel_actual].jugador1, paneles[panel_actual].jugador2);
			printf("Resultado %d \n",paneles[panel_actual].estado);	

			if(paneles[panel_actual].estado == 0)  
			{
				paneles[panel_actual].jugador1 = 0; 
				paneles[panel_actual].jugador2 = 0;  

			}
		}

		int i;
		for(i = 0;i<CANTIDAD;i++)
		{
			
			printf("Panel %d \n",i);
			printf("Jugador 1  %d \n",paneles[i].jugador1);
			printf("Jugador 2  %d \n",paneles[i].jugador2);
			printf("Estado   %d \n",paneles[i].estado);
		}

		if(paneles[panel_actual].estado != 0)
		{
			panel_actual ++;
			printf("Pasar a siguiente panel \n");
		}

		levanta_semaforo(id_semaforo);
		usleep(1500*1000);

		

	}



	int gano1 = 0;
	int gano2 = 0;
	int j;

	for(j = 0;j<CANTIDAD;j++)
	{
		if(paneles[j].estado == 1)
		{
			gano1 ++;
		}	
		if(paneles[j].estado == 2)
		{
			gano2 ++;
		}	
	}

	if(gano1 > gano2) {printf("Gano el 1 con %d  victorias \n",gano1);}
	if(gano1 < gano2) {printf("Gano el 2 con %d  victorias \n",gano2);}
	if(gano1 == gano2) {printf("????");}

	shmdt ((panel *)paneles);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
