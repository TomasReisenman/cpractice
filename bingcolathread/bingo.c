#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define INTERVALO_DESDE 500
#define INTERVALO_HASTA 5000

#define BOLILLAS_DESDE 1
#define BOLILLAS_HASTA 99


typedef struct tipo_bolillero tbolillero;
struct tipo_bolillero
{
	int  id_colamensaje;
	int  cantidad_jugadores;
	
};

int obtener_numero_aleatorio(int desde,int hasta)
{
	return  (rand()%(hasta-desde+1))+desde;
}
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
void *ThreadBolillero (void *parametro)
{
	int bolilla_elegida=0;
	char cadena[100];
	int i ;
	int j = 0;
	int id_cola_mensajes = 0;
	int cantidad_jugadores = 0;

	tbolillero *datos_bolillero = (tbolillero*) parametro;
	cantidad_jugadores = datos_bolillero->cantidad_jugadores;
	id_cola_mensajes = datos_bolillero->id_colamensaje;
	int *bolillas = generarRandom(BOLILLAS_DESDE -1,BOLILLAS_HASTA,99);

	while (1)
	{
		bolilla_elegida = bolillas[j];
		printf("El numero elegido es %d\n", bolilla_elegida);
		sprintf(cadena, "%d", bolilla_elegida);

		for (i = 0; i < cantidad_jugadores; i++)
		{
			enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_BINGO, EVT_BOLILLA, cadena);
		}

		usleep(100*obtener_numero_aleatorio(INTERVALO_DESDE, INTERVALO_HASTA));
		j++;
	}
	
	pthread_exit ((void *)"Listo");
}
void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	char 	cadena[LARGO_TMENSAJE];
	int nro_recibido = atoi(msg.char_mensaje);

	printf("------------------------------\n");
	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_CARTON_LLENO:
			printf("El jugador ganador es %s",msg.char_mensaje);
		break;
		default:
			printf("\nEvento sin definir\n");
		break;
	}

	printf("------------------------------\n");
}


int main(int argc, char *argv[])
//int main()
{
	int id_cola_mensajes;
	int i, j;
	int cantidad_jugadores= atoi(argv[1]);
	char cadena[100];
	mensaje		msg;
	
	srand(time(NULL));
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*1);
	pthread_attr_t 	atributos;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	tbolillero *datos_bolillero;
	datos_bolillero = (tbolillero*) malloc(sizeof(tbolillero)*1);
	datos_bolillero->cantidad_jugadores = cantidad_jugadores;
	datos_bolillero->id_colamensaje = id_cola_mensajes;
	pthread_create (idHilo, &atributos, ThreadBolillero, datos_bolillero);

	while(1)
	{
		recibir_mensaje(id_cola_mensajes, MSG_BINGO, &msg);	
		procesar_evento(id_cola_mensajes,msg);
		printf("Fin del Juego \n");
		break;
	}
	
	printf("------------------------------\n");
	printf("Main Bingo thread ends \n");
	return 0;
}

    
