#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define BARCOS_DESDE 0
#define BARCOS_HASTA 10
#define MAX_LIBERAR 10

pthread_mutex_t mutex;

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int  id_colamensaje;
	int  nro_jugador;
	int barcos_derribados;
//	int  *vector_tambor;
	
};

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

void *ThreadJugador (void *parametro)
{
	int 			nro_jugador;
	int 			id_cola_mensajes;
	int 			done=0;
	char 	cadena[LARGO_TMENSAJE];
	int             busqueda = 0;
	int             found = 0;
	mensaje		msg;
	int  barcos_hundidos = 0;

	int fila;
	int columna;
	int fila_obtener = 0;
	int columna_obtener = 0;
	int *posibles_filas = generarRandom(BARCOS_DESDE,BARCOS_HASTA,10);
	int *posibles_columnas = generarRandom(BARCOS_DESDE,BARCOS_HASTA,10);
	
	tjugador *datos_thread = (tjugador*) parametro;
	nro_jugador = datos_thread->nro_jugador;
	id_cola_mensajes = datos_thread->id_colamensaje;
//	int *vector_tambor = datos_thread->vector_tambor;

	while(done==0)
	{
	
		fila = posibles_filas[fila_obtener];
		columna = posibles_columnas[columna_obtener];

		printf("El jugador %d dispara en %d,%d \n",nro_jugador,fila,columna);

		sprintf(cadena, "%d|%d", fila,columna);
		enviar_mensaje(id_cola_mensajes , MSG_BARCOS , MSG_JUGADOR+nro_jugador ,EVT_MISIL, cadena);

		recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);	//bloqueate
		printf("------------------------------\n");
		printf("Remitente %d \n", msg.int_rte);
		printf("Destino   %d\n", (int) msg.long_dest);
		printf("Evento    %d \n", msg.int_evento);
		printf("Mensaje   %s \n", msg.char_mensaje);
		printf("------------------------------\n");

	
		switch (msg.int_evento)
		{
			case EVT_HUNDIDO:
				//pthread_mutex_lock (&mutex);
				printf("Soy el jugador %d y acabo de hundir un barco \n",nro_jugador);
				barcos_hundidos ++;

				//while (found == 0 )
				//{
				//	if (vector_tambor[busqueda] == 0)
				//	{
				//		found = 1;
				//		vector_tambor[busqueda] = 1;
				//	}else {
				//		busqueda ++;
				//	}
				//}
				//sprintf(cadena, "%d", busqueda);
				//sleep(1);
				//pthread_mutex_unlock (&mutex);
				//enviar_mensaje(id_cola_mensajes , MSG_REVOLVER , MSG_JUGADOR+nro_jugador ,EVT_DISPARO, cadena);
				//printf("Soy el jugador %d y la posicion del tambor es %d \n",nro_jugador,busqueda );
				break;
			case EVT_AGUA:
				printf("Jugador %d no hundio nada \n",nro_jugador);
				break;
			case EVT_JUEGO_TERMINADO:
				printf("Termina el jugador %d \n",nro_jugador);
				done=1;
				break;
			default:
				printf("Jugador %d Evento sin definir\n", nro_jugador);
				break;
		}
		usleep(1000 * 500);

		columna_obtener ++;
		if(columna_obtener == 10)
		{
			columna_obtener = 0;
			fila_obtener ++;	
		}
	};
	//sprintf(cadena, "%d", barcos_hundidos);
	//pthread_exit ((void *)cadena);
	datos_thread->barcos_derribados = barcos_hundidos;
	pthread_exit ((void *)"Listo");
}
		
//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int i, j = 0;
	int cantidad_jugadores = 4;
	//char *valorDevuelto = NULL;
	srand(time(NULL));
		
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	//int vector_tambor[] = {0,0,0,0,0,0};

	pthread_mutex_init (&mutex, NULL);

	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_jugadores);
	pthread_attr_t 	atributos;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	tjugador *datos_jugador;
	datos_jugador = (tjugador*) malloc(sizeof(tjugador)*cantidad_jugadores);
	
	for(i=0; i<cantidad_jugadores; i++)
	{
		datos_jugador[i].id_colamensaje = id_cola_mensajes;
		datos_jugador[i].nro_jugador = i;
		//datos_jugador[i].vector_tambor = vector_tambor;
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_jugador[i]);
		sleep(1);
	}

	for(j=0; j<cantidad_jugadores; j++)
	{
	//	pthread_join (idHilo[j], (void **)&valorDevuelto);
		pthread_join (idHilo[j], NULL);
		printf("El jugador %d obtuvo %d \n",j,datos_jugador[j].barcos_derribados);
	}
	return 0;
}



