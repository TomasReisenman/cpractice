#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 2
#define MAX_LIBERAR 10
#define CANT_TIROS 5

pthread_mutex_t mutex;

typedef struct tipo_pateador tpateador;
struct tipo_pateador
{
	int  id_colamensaje;
	int  nro_pateador;
	int  resultado;
	
};

void mostrarPateadores(tpateador* datos_tiros)
{
	int i;
	int goles_realizados = 0;

	for (i = 0; i < CANT_TIROS; i++)
	{

		switch (datos_tiros[i].resultado)
		{
			case EVT_GOL:
				printf("El pateador %d,logro un gol \n", datos_tiros[i].nro_pateador);
				break;
			case EVT_PALO:
				printf("El pateador %d, le pego en el palo \n", datos_tiros[i].nro_pateador);
				break;
			case EVT_TRAVESA:
				printf("El pateador %d, le pego en el travesa \n", datos_tiros[i].nro_pateador);
				break;
			case EVT_FUERA:
				printf("El pateador %d, le erro\n", datos_tiros[i].nro_pateador);
				break;
			default:
				printf("Pateador no definido \n");
				break;
		}

			if (datos_tiros[i].resultado == 2)
			{
				goles_realizados++;
			}
	}
	printf("Los jugadores realizaron %d goles \n", goles_realizados);
}

void *ThreadJugador (void *parametro)
{
	int 			nro_pateador;
	int 			id_cola_mensajes;
	int 			done=0;
	char 	cadena[LARGO_TMENSAJE];
	int             busqueda = 0;
	int             found = 0;
	mensaje		msg;
	
	tpateador *datos_pateador = (tpateador*) parametro;
	nro_pateador = datos_pateador->nro_pateador;
	id_cola_mensajes = datos_pateador->id_colamensaje;

	pthread_mutex_lock (&mutex);

		enviar_mensaje(id_cola_mensajes , MSG_ARQUERO , MSG_PATEADOR+nro_pateador ,EVT_TIRO, cadena);
	
		recibir_mensaje(id_cola_mensajes, MSG_PATEADOR+nro_pateador, &msg);

		printf("------------------------------\n");
		printf("Remitente %d \n", msg.int_rte);
		printf("Destino   %d\n", (int) msg.long_dest);
		printf("Evento    %d \n", msg.int_evento);
		printf("Mensaje   %s \n", msg.char_mensaje);
		printf("------------------------------\n");

		switch (msg.int_evento)
		{
			case EVT_GOL:
				printf("GOOOOOOL \n");
				printf("Soy el pateador %d y acabo de hacer un gol \n",nro_pateador);
				datos_pateador->resultado = EVT_GOL;
				break;
			case EVT_PALO:
				printf("Uffff ");
				printf("Soy el pateador %d y acabo de fallar \n",nro_pateador);
				datos_pateador->resultado = EVT_PALO;
				break;
			case EVT_TRAVESA:
				printf("Uffff ");
				printf("Soy el pateador %d y acabo de fallar \n",nro_pateador);
				datos_pateador->resultado = EVT_TRAVESA;
				break;
			case EVT_FUERA:
				printf("Uffff ");
				printf("Soy el pateador %d y acabo de fallar \n",nro_pateador);
				datos_pateador->resultado = EVT_FUERA;
				break;
			default:
				printf("Pateador %d Evento sin definir\n", nro_pateador);
				break;
		}
	pthread_mutex_unlock (&mutex);
	pthread_exit ((void *)"Listo");
}
		
//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int i, j = 0;
	int cantidad_jugadores = 5;
	srand(time(NULL));
		
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);

	pthread_mutex_init (&mutex, NULL);

	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_jugadores);
	pthread_attr_t 	atributos;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	tpateador *datos_pateador;
	datos_pateador = (tpateador*) malloc(sizeof(tpateador)*cantidad_jugadores);
	
	for(i=0; i<cantidad_jugadores; i++)
	{
		datos_pateador[i].id_colamensaje = id_cola_mensajes;
		datos_pateador[i].nro_pateador = i;
		datos_pateador[i].resultado = 0;
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_pateador[i]);
	}

	for (j = 0; j < cantidad_jugadores; j++)
	{
		pthread_join(idHilo[j], NULL);
	}
	mostrarPateadores(datos_pateador);

	return 0;

}



