#include "funciones.h"
#include "definiciones.h"

#define INTERVALO_DESDE 100
#define INTERVALO_HASTA 500
#define TIEMPO_ESPERA 500

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 5
#define CANT_TIROS 5

typedef struct tipo_tiro tiro;

struct tipo_tiro
{
  int numero_jugador;
  int nurmero_tiro;
  int resultado;
};

int obtener_numero_aleatorio(int desde, int hasta)
{

	return (rand() % (hasta - desde + 1)) + desde;
}

void mostrarTiros(int* datos_tiros)
{
	int i;
	int goles_recibidos = 0;

	for (i = 0; i < CANT_TIROS; i++)
	{
		if (datos_tiros[i] == 2)
		{
			goles_recibidos ++;
		}
		
		printf("El jugador %d,obtuvo %d \n"
		,i
		,datos_tiros[i]);
	}
		printf("El arquero recibio %d goles \n",goles_recibidos);
}

void procesar_evento(int id_cola_mensajes, mensaje msg, int* datos_tiros)
{
	char 	cadena[LARGO_TMENSAJE];
	int resultado  = 0;

	printf("------------------------------\n");
	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	printf("------------------------------\n");
	switch (msg.int_evento)
	{
		case EVT_TIRO:
				usleep(1000*TIEMPO_ESPERA);
				resultado = obtener_numero_aleatorio(EVT_GOL,EVT_FUERA);
				printf("Patea el jugador %d\n", msg.int_rte);
				printf("Resultado del disparo fue  %d\n", resultado);
				datos_tiros[msg.int_rte - 2] = resultado;
				sprintf(cadena, "%d", resultado);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_ARQUERO, resultado, cadena);
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

	srand(time(NULL));
	int* datos_tiros = (int* ) malloc(sizeof(int)*CANT_TIROS);	
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);

	for(j=0; j<CANT_TIROS; j++)
	{
		recibir_mensaje(id_cola_mensajes, MSG_ARQUERO, &msg);
		procesar_evento(id_cola_mensajes,msg,datos_tiros);
	}

	mostrarTiros(datos_tiros);
	
	return 0;
}

    
