#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 2
#define MAX_LIBERAR 10

pthread_mutex_t mutex;

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int  id_colamensaje;
	int  nro_jugador;
	int  *vector_tambor;
	
};

void *ThreadJugador (void *parametro)
{
	int 			nro_jugador;
	int 			id_cola_mensajes;
	int 			done=0;
	char 	cadena[LARGO_TMENSAJE];
	int             busqueda = 0;
	int             found = 0;
	mensaje		msg;
	
	tjugador *datos_thread = (tjugador*) parametro;
	nro_jugador = datos_thread->nro_jugador;
	id_cola_mensajes = datos_thread->id_colamensaje;
	int *vector_tambor = datos_thread->vector_tambor;

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);	//bloqueate
	
		printf("Remitente %d \n", msg.int_rte);
		printf("Destino   %d\n", (int) msg.long_dest);
		printf("Evento    %d \n", msg.int_evento);
		//printf("Mensaje   %s \n", msg.char_mensaje);
		printf("------------------------------\n");
	
		switch (msg.int_evento)
		{
			case EVT_INICIO:
				pthread_mutex_lock (&mutex);
				printf("Soy el jugador %d y voy a dispararme \n",nro_jugador);

				while (found == 0 )
				{
					if (vector_tambor[busqueda] == 0)
					{
						found = 1;
						vector_tambor[busqueda] = 1;
					}else {
						busqueda ++;
					}
				}
				sprintf(cadena, "%d", busqueda);
				sleep(1);
				pthread_mutex_unlock (&mutex);
				enviar_mensaje(id_cola_mensajes , MSG_REVOLVER , MSG_JUGADOR+nro_jugador ,EVT_DISPARO, cadena);
				printf("Soy el jugador %d y la posicion del tambor es %d \n",nro_jugador,busqueda );
				break;
			case EVT_FIN:
				printf("Jugador eliminado %d \n",nro_jugador);
				done=1;
				break;
			case EVT_SALVADO:
				done=1;
				break;
			default:
				printf("Jugador %d Evento sin definir\n", nro_jugador);
				break;
		}
	};
	pthread_exit ((void *)"Listo");
}
		
//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int i, j = 0;
	int cantidad_jugadores = 6;
	srand(time(NULL));
		
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	int vector_tambor[] = {0,0,0,0,0,0};

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
		datos_jugador[i].vector_tambor = vector_tambor;
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_jugador[i]);
		sleep(1);
	}

	for(j=0; j<cantidad_jugadores; j++)
	{
		pthread_join (idHilo[j], NULL);
	}
	return 0;
}



