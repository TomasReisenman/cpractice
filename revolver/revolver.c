#include "funciones.h"
#include "definiciones.h"

#define INTERVALO_DESDE 100
#define INTERVALO_HASTA 500

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 5


void procesar_evento(int id_cola_mensajes, mensaje msg, int nro_elegido)
{
	char 	cadena[LARGO_TMENSAJE];
	int 	count = 0;
	int		codigo=0;
	int 	cantidad=0;
	char 	*token;
	int	i;
	int nro_recibido = atoi(msg.char_mensaje);

	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
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
	int intervalo=0;
	//int total_vehiculos=0;
	int vehiculos=0;
	int nro_via=0;
	int nro_elegido=0;
	char cadena[100];
	mensaje		msg;
	
	//if (argc>2)
	//{
	//	cantidad_jugadores = atoi(argv[1]);
	//	total_vehiculos = atoi(argv[2]);
	//}
	printf("%d\n", cantidad_jugadores);
	srand(time(NULL));
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	nro_elegido = rand()%(cantidad_jugadores-0)+0;

	borrar_mensajes(id_cola_mensajes);

	//while(total_vehiculos>0)
	for(i = 0;i<cantidad_jugadores;i++ )
	{
		//intervalo = rand()%(INTERVALO_HASTA+1-INTERVALO_DESDE)+INTERVALO_DESDE;
		//vehiculos = rand()%(VEHICULOS_HASTA+1-VEHICULOS_DESDE)+VEHICULOS_DESDE;
		//nro_via = rand()%(cantidad_jugadores-0)+0;
		
		printf("VIA:%d VEHICULOS:%d INTERVALO:%d\n", nro_via, vehiculos, intervalo);
		
		//sprintf(cadena, "%d", vehiculos);
		enviar_mensaje(id_cola_mensajes , MSG_JUGADOR+i, MSG_REVOLVER, EVT_INICIO, cadena);
		//total_vehiculos-=vehiculos;
		//printf("Quedan %d vehiculos\n", total_vehiculos);
		//usleep(1000*intervalo);
	}
	recibir_mensaje(id_cola_mensajes, MSG_REVOLVER, &msg);	//bloqueate
	procesar_evento(id_cola_mensajes,msg,nro_elegido);
	//for(i=0; i<cantidad_jugadores; i++)
	//{
	//	enviar_mensaje(id_cola_mensajes , MSG_VIAS+i, MSG_AUTOS, EVT_FINALIZAR, "FINALIZAR");
	//}
	
	return 0;
}

    
