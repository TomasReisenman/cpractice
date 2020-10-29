#include "funciones.h"
#include "definiciones.h"

#define INTERVALO_DESDE 100
#define INTERVALO_HASTA 500

#define BARCOS_DESDE 0
#define BARCOS_HASTA 10

typedef struct tipo_hundimiento hundimiento;

struct tipo_hundimiento
{
  int numero_jugador;
  int fila;
  int columna;
};

int obtener_numero_aleatorio(int desde, int hasta)
{

	return (rand() % (hasta - desde + 1)) + desde;
}

int *generarRandom(int desde, int hasta, int cantidad)
{
	/* * * El 'desde' no es incluido en la seleccion del numero aleatorio. Ejemplo: para obtener el valor '0' debo arrancar desde el valor '-1' * * */

	int n, num, i, j, hastaRand, temp;
	int *vector = (int *)malloc(cantidad * sizeof(int));

	desde--;
	if ((hasta - desde) < cantidad)
	{
		printf("deben haber mas numeros que cantidades, %d es menor que %d\n", (hasta - desde), cantidad);
		free(vector);
		exit(0);
	}

	hastaRand = (hasta - desde) / cantidad;

	temp = desde;

	for (n = 0; n < cantidad; n++)
	{
		num = (rand() % (hastaRand)) + 1;
		vector[n] = temp + num;
		//printf("el numero es %d: %d =%d \n", vector[n],hastaRand,num);
		temp = temp + hastaRand;
	}

	//printf("Reordeno---------\n");
	for (i = cantidad - 1; i > 0; i--)
	{
		num = rand() % (i);
		j = vector[i];
		vector[i] = vector[num];
		vector[num] = j;
	}

	return vector;
}

void inicializarTablero(int barcos[10][10])
{
	int i;
	int j;
	int fila;
	int columna;
	int barcos_agregados = 0;

	for (i = BARCOS_DESDE; i < BARCOS_HASTA; i++)
	{
		for (j = BARCOS_DESDE; j < BARCOS_HASTA; j++)
		{
			barcos[i][j] = 0;
		}
	}

	while (barcos_agregados < 10)
	{
		fila = obtener_numero_aleatorio(BARCOS_DESDE, BARCOS_HASTA);
		columna = obtener_numero_aleatorio(BARCOS_DESDE, BARCOS_HASTA);

		if (barcos[fila][columna] == 0)
		{
			barcos[fila][columna] = 1;
			barcos_agregados++;
		}
	}
}

void mostrarTablero(int barcos[10][10])
{
	int i;
	int j;

	for (i = BARCOS_DESDE; i < BARCOS_HASTA; i++)
	{
		for (j = BARCOS_DESDE; j < BARCOS_HASTA; j++)
		{
			printf("%d ", barcos[i][j]);
		}
		printf("\n");
	}
}
//void procesar_evento(int id_cola_mensajes, mensaje msg, int nro_elegido)
//{
//	char 	cadena[LARGO_TMENSAJE];
//	int nro_recibido = atoi(msg.char_mensaje);
//
//	printf("Destino   %d\n", (int) msg.long_dest);
//	printf("Remitente %d\n", msg.int_rte);
//	printf("Evento    %d\n", msg.int_evento);
//	//printf("Mensaje   %s\n", msg.char_mensaje);
//	switch (msg.int_evento)
//	{
//		case EVT_DISPARO:
//			if (nro_recibido == nro_elegido) {
//				sprintf(cadena, "%d", nro_recibido);
//				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_REVOLVER, EVT_FIN, cadena);
//			}
//			if (nro_recibido != nro_elegido) {
//				sprintf(cadena, "%d", nro_recibido);
//				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_REVOLVER, EVT_SALVADO, cadena);
//			}
//		break;
//		default:
//			printf("\nEvento sin definir\n");
//		break;
//	}
//
//	printf("------------------------------\n");
//}

void mostrarHundimientos(hundimiento* datos_hundimiento)
{
	int i;

	for (i = 0; i < BARCOS_HASTA; i++)
	{
		printf("El barco en posicion %d,%d fue hundido por jugador %d \n"
		,datos_hundimiento[i].fila
		,datos_hundimiento[i].columna
		,datos_hundimiento[i].numero_jugador);
	}
}
//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int i, j;
	int cantidad_jugadores = 4;
	int nro_elegido = 0;
	char cadena[LARGO_TMENSAJE];
	mensaje msg;
	int barcos[10][10];
	int count;
	char *token;
	int barcos_undidos = 0;
	int fila = 0;
	int columna = 0;

	hundimiento *datos_hundimiento;
	datos_hundimiento = (hundimiento*) malloc(sizeof(hundimiento)*BARCOS_HASTA);
	printf("%d\n", cantidad_jugadores);
	srand(time(NULL));
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	//nro_elegido = rand()%(cantidad_jugadores-0)+0;
	//printf("El numero elegido es %d\n", nro_elegido);

	borrar_mensajes(id_cola_mensajes);
	inicializarTablero(barcos);
	mostrarTablero(barcos);

	//for(i = 0;i<cantidad_jugadores;i++ )
	//{
	//	enviar_mensaje(id_cola_mensajes , MSG_JUGADOR+i, MSG_REVOLVER, EVT_INICIO, cadena);
	//}
	while (barcos_undidos < 10)
	{
		recibir_mensaje(id_cola_mensajes, MSG_BARCOS, &msg);
		//procesar_evento(id_cola_mensajes,msg,nro_elegido);
		printf("--------------------\n");
		printf("Destino   %d\n", (int)msg.long_dest);
		printf("Remitente %d\n", msg.int_rte);
		printf("Evento    %d\n", msg.int_evento);
		printf("Mensaje   %s\n", msg.char_mensaje);
		printf("--------------------\n");

		sprintf(cadena,"%d \n", 0);	
		switch (msg.int_evento)
		{
		case EVT_MISIL:
			printf("Se recibio un Misil\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
				case 0:
					fila = atoi(token);
					printf("fila objetibo :%d \n", fila);
					break;
				case 1:
					columna = atoi(token);
					printf("columna objetivo:%d\n \n", columna);
					break;
				}
				token = strtok(NULL, "|");
				count++;
			}

			if(barcos[fila][columna] == 1)
			{
				printf("Barco hundido \n");				
				barcos[fila][columna]= 0;
				datos_hundimiento[barcos_undidos].numero_jugador = msg.int_rte -2;
				datos_hundimiento[barcos_undidos].fila = fila;
				datos_hundimiento[barcos_undidos].columna = columna;
				barcos_undidos ++;
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BARCOS, EVT_HUNDIDO, cadena);
			} else
			{
				printf("Barco no hundido \n");				
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BARCOS, EVT_AGUA, cadena);
			}
			
			break;

		default:
			printf("\nEvento sin definir\n");
			break;
		}

		mostrarTablero(barcos);
	}

	for(j=0; j<cantidad_jugadores; j++)
	{
		sprintf(cadena, "%d", 0);
		enviar_mensaje(id_cola_mensajes , MSG_JUGADOR+j, MSG_BARCOS, EVT_JUEGO_TERMINADO, cadena);
	}

	//enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BARCOS, EVT_HUNDIDO, cadena);

	mostrarHundimientos(datos_hundimiento);

	return 0;
}
