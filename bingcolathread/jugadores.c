#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 2
#define CANTIDAD_BOLILLAS 5

#define BOLILLAS_DESDE 1
#define BOLILLAS_HASTA 99

pthread_mutex_t mutex;

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int  id_colamensaje;
	int  nro_jugador;
	int  cantidad_jugadores;
	
};

int obtener_numero_aleatorio(int desde,int hasta)
{
	return  (rand()%(hasta-desde+1))+desde;
}

int* obtener_carton()
{
	int i;
	int* carton = (int*) malloc(CANTIDAD_BOLILLAS*sizeof(int));

	for (i = 0; i < CANTIDAD_BOLILLAS; i++)
	{
		carton[i] = obtener_numero_aleatorio(BOLILLAS_DESDE, BOLILLAS_HASTA);
	}

	return carton;
}

int buscar_en_carton(int bolilla,int* carton)
{
	int encontrado = 0;	
	int i = 0;

	while (encontrado == 0 && i < CANTIDAD_BOLILLAS)
	{
		if (carton[i] == bolilla)
		{
			encontrado = 1;
		}
		
		i ++;
	}
	return encontrado;	

}
void *ThreadJugador (void *parametro)
{
	int 			nro_jugador;
	int 			id_cola_mensajes;
	int 			done=0;
	char 	cadena[LARGO_TMENSAJE];
	int             cantidad_jugadores = 0;
	int             found = 0;
	int 			j;
	mensaje		msg;
	
	tjugador *datos_thread = (tjugador*) parametro;
	nro_jugador = datos_thread->nro_jugador;
	id_cola_mensajes = datos_thread->id_colamensaje;
	cantidad_jugadores = datos_thread->cantidad_jugadores;
	int *carton = obtener_carton();
	int cant_aciertos = 0;
	int bolilla = 0;

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);	//bloqueate
	
		printf("Remitente %d \n", msg.int_rte);
		printf("Destino   %d\n", (int) msg.long_dest);
		printf("Evento    %d \n", msg.int_evento);
		printf("Mensaje   %s \n", msg.char_mensaje);
		printf("------------------------------\n");

		bolilla = atoi(msg.char_mensaje);
	
		switch (msg.int_evento)
		{
			case EVT_BOLILLA:
				//pthread_mutex_lock (&mutex);
				printf("Soy el jugador %d y reviso mi carton \n",nro_jugador);

				cant_aciertos += buscar_en_carton(bolilla,carton);

				printf("Soy el jugador %d y tengo %d aciertos \n",nro_jugador,cant_aciertos);
				//sprintf(cadena, "%d", busqueda);
				//sleep(1);
				//pthread_mutex_unlock (&mutex);
				if (cant_aciertos == CANTIDAD_BOLILLAS)
				{
					printf("Jugador %d completo el carton \n", nro_jugador);
					sprintf(cadena, "%d", nro_jugador);
					enviar_mensaje(id_cola_mensajes , MSG_BINGO , MSG_JUGADOR+nro_jugador ,EVT_CARTON_LLENO, cadena);

					for (j = 0; j < cantidad_jugadores; j++)
					{
						printf("Enviando mensaje fin a otros \n");
						enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + j,MSG_JUGADOR+nro_jugador, EVT_CARTON_LLENO, cadena);
					}
					return 0;
				}
				
				//printf("Soy el jugador %d y la posicion del tambor es %d \n",nro_jugador,busqueda );
				break;
			case EVT_CARTON_LLENO:
				printf("Jugador %d recibe fin del juego y obtubo %d \n",nro_jugador,cant_aciertos);
				done=1;
				break;
			default:
				printf("Jugador %d Evento sin definir\n", nro_jugador);
				break;
		}
	};
	pthread_exit ((void *)"Listo");
}
		


int main(int argc, char *argv[])
//int main()
{
	int id_cola_mensajes;
	int i, j = 0;
	int cantidad_jugadores = atoi(argv[1]);
	srand(time(NULL));
		
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

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
		datos_jugador[i].cantidad_jugadores = cantidad_jugadores;
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_jugador[i]);
		sleep(1);
	}

	for(j=0; j<cantidad_jugadores; j++)
	{
		pthread_join (idHilo[j], NULL);
	}
	return 0;
}



