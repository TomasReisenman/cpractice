#include "funciones.h"
#include "definiciones.h"

#define INTERVALO_DESDE 100
#define INTERVALO_HASTA 500

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 5


void procesar_evento(int id_cola_mensajes, mensaje msg, int nro_elegido)
{
	char 	cadena[LARGO_TMENSAJE];
	int nro_recibido = atoi(msg.char_mensaje);

	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	//printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_DISPARO:
			if (nro_recibido == nro_elegido) {
				sprintf(cadena, "%d", nro_recibido);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_REVOLVER, EVT_FIN, cadena);
			}
			if (nro_recibido != nro_elegido) {
				sprintf(cadena, "%d", nro_recibido);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_REVOLVER, EVT_SALVADO, cadena);
			}
		break;
		default:
			printf("\nEvento sin definir\n");
		break;
	}

	printf("------------------------------\n");
}

//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int i, j;
	int cantidad_jugadores=6;
	int nro_elegido=0;
	char cadena[100];
	mensaje		msg;
	
	printf("%d\n", cantidad_jugadores);
	srand(time(NULL));
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	nro_elegido = rand()%(cantidad_jugadores-0)+0;
	printf("El numero elegido es %d\n", nro_elegido);

	borrar_mensajes(id_cola_mensajes);

	for(i = 0;i<cantidad_jugadores;i++ )
	{
		enviar_mensaje(id_cola_mensajes , MSG_JUGADOR+i, MSG_REVOLVER, EVT_INICIO, cadena);
	}
	for(j=0; j<cantidad_jugadores; j++)
	{
		recibir_mensaje(id_cola_mensajes, MSG_REVOLVER, &msg);	//bloqueate
		procesar_evento(id_cola_mensajes,msg,nro_elegido);
	}
	
	return 0;
}

    
