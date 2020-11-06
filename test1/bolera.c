#include "funciones.h"
#include "definiciones.h"

#define CANT_PINOS 10
#define VEHICULOS_HASTA 5
#define INTENTOS 3

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int pinos_disponibles;
	int intentos;
	
};

int obtener_numero_aleatorio(int desde,int hasta)
{

	return  (rand()%(hasta-desde+1))+desde;

}


int main()
{
	int id_cola_mensajes;
	int i, j;
	int cantidad_jugadores=2;
	char cadena[100];
	int jugadores_completados = 0;
	mensaje		msg;
	int pinos_tirados = 0;
	
	srand(time(NULL));
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);

	tjugador *datos_jugador;
	datos_jugador = (tjugador*) malloc(sizeof(tjugador)*cantidad_jugadores);

	for(i = 0;i<cantidad_jugadores;i++ )
	{
		datos_jugador[i].pinos_disponibles = CANT_PINOS;
		datos_jugador[i].intentos = 0;
		enviar_mensaje(id_cola_mensajes , MSG_JUGADOR+i, MSG_BOLERA, EVT_INICIO, cadena);
	}
	while(jugadores_completados < 2)
	{
		printf("Jugadores completados %d \n", jugadores_completados);
		recibir_mensaje(id_cola_mensajes, MSG_BOLERA, &msg);

		printf("-----------------\n");
		printf("Destino   %d\n", (int)msg.long_dest);
		printf("Remitente %d\n", msg.int_rte);
		printf("Evento    %d\n", msg.int_evento);
		printf("Mensaje   %s\n", msg.char_mensaje);
		printf("-----------------\n");

		switch (msg.int_evento)
		{
		case EVT_TIRO:
			pinos_tirados = obtener_numero_aleatorio(1, datos_jugador[msg.int_rte - 2].pinos_disponibles);
			printf("El jugador %d derribo %d pinos \n", msg.int_rte - 2, pinos_tirados);

			datos_jugador[msg.int_rte - 2].pinos_disponibles -= pinos_tirados;
			datos_jugador[msg.int_rte - 2].intentos++;

			printf("Al jugador %d le quedan %d pinos y esta en su intento %d \n", msg.int_rte - 2,datos_jugador[msg.int_rte - 2].pinos_disponibles,datos_jugador[msg.int_rte - 2].intentos);
			if (datos_jugador[msg.int_rte - 2].pinos_disponibles == 0 && datos_jugador[msg.int_rte - 2].intentos == 1)
			{
				printf("CHUZA del jugador  %d\n", msg.int_rte - 2);
				sprintf(cadena, "%d", 20);
				jugadores_completados++;
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_FIN, cadena);
			}
			if (datos_jugador[msg.int_rte - 2].pinos_disponibles == 0 && datos_jugador[msg.int_rte - 2].intentos > 1 && datos_jugador[msg.int_rte - 2].intentos < INTENTOS)
			{
				sprintf(cadena, "%d", 10);
				jugadores_completados++;
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_FIN, cadena);
			}
			if (datos_jugador[msg.int_rte - 2].pinos_disponibles > 0 && datos_jugador[msg.int_rte - 2].intentos < INTENTOS)
			{
				sprintf(cadena, "%d", pinos_tirados);
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_RESULTADO, cadena);
			}
			if (datos_jugador[msg.int_rte - 2].pinos_disponibles >= 0 && datos_jugador[msg.int_rte - 2].intentos == INTENTOS)
			{
				sprintf(cadena, "%d", 10 - datos_jugador[msg.int_rte - 2].pinos_disponibles);
				jugadores_completados++;
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_FIN, cadena);
			}
			break;
		default:
			printf("\nEvento sin definir\n");
			break;
		}

		printf("------------------------------\n");
	}

	return 0;
}

    
