#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>


typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int  id_colamensaje;
	int  nro_jugador;
	int  puntos_obtenidos;
	
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
	int puntos_obtenidos = 0;

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
		
	
		printf("------------------------------\n");
		printf("Remitente %d \n", msg.int_rte);
		printf("Destino   %d\n", (int) msg.long_dest);
		printf("Evento    %d \n", msg.int_evento);
		printf("Mensaje   %s \n", msg.char_mensaje);
		printf("------------------------------\n");
	
		switch (msg.int_evento)
		{
			case EVT_INICIO:
				printf("Soy el jugador %d y voy a tirar \n",nro_jugador);
				enviar_mensaje(id_cola_mensajes , MSG_BOLERA , MSG_JUGADOR+nro_jugador ,EVT_TIRO, cadena);
				break;
			case EVT_RESULTADO:
				enviar_mensaje(id_cola_mensajes , MSG_BOLERA , MSG_JUGADOR+nro_jugador ,EVT_TIRO, cadena);
				printf("Soy el jugador %d y tire %s bolos \n",nro_jugador,msg.char_mensaje);
				break;
			case EVT_FIN:
				printf("Jugador %d recibi el evento fin \n",nro_jugador);
				printf("Soy el jugador %d y obtuve %s puntos \n",nro_jugador,msg.char_mensaje);
				puntos_obtenidos = atoi(msg.char_mensaje);
				datos_thread->puntos_obtenidos = puntos_obtenidos;
				done=1;
				break;
			default:
				printf("Jugador %d Evento sin definir\n", nro_jugador);
				break;
		}
	};
	usleep(1000 * 300);
	pthread_exit ((void *)"Listo");
}

void mostrarPuntos(tjugador* datos_jugadores){
	printf("Mostrando datos de jugadores \n");

	int i;

	for(i=0;i<2;i++){

		printf("El jugador %d obtuvo %d \n",i,datos_jugadores[i].puntos_obtenidos);

	}

}
		
int main()
{
	int id_cola_mensajes;
	int i, j = 0;
	int cantidad_jugadores = 2;
	srand(time(NULL));
		
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);

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
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_jugador[i]);
	}

	for(j=0; j<cantidad_jugadores; j++)
	{
		pthread_join (idHilo[j], NULL);
	}

	mostrarPuntos(datos_jugador);
	return 0;
}



