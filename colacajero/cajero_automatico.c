#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 2
#define MAX_LIBERAR 10
#define MAX_MENU 3
//pthread_mutex_t mutex;

//typedef struct tipo_jugador tjugador;
//struct tipo_jugador
//{
//	int  id_colamensaje;
//	int  nro_jugador;
//	int  *vector_tambor;
//
//};

void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	char cadena[LARGO_TMENSAJE];
	int nro_recibido = atoi(msg.char_mensaje);
	char *token;
	char *mensaje_error;
	int count = 0;
	int saldo = 0;
	int codigo = 0;
	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);

	switch (msg.int_evento)
	{
		case EVT_RTA_SALDO:
			printf("Rta saldo\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						codigo = atoi(token);
						printf("COD de cliente:%d \n", codigo);
					break;
					case 1:
						codigo = atoi(token);
						printf("El saldo resultante es:%d \n", saldo);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
		break;
		case EVT_RTA_SALDO_NOK:
			printf("Rta saldo not ok\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						codigo = atoi(token);
						printf("COD de cliente:%d \n", codigo);
					break;
					case 1:
						mensaje_error = token;
						printf("Ocurrio un error :%s \n", mensaje_error);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
		break;
		case EVT_RTA_DEPOSITO_OK:
			printf("Rta deposito \n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						codigo = atoi(token);
						printf("COD de cliente:%d \n", codigo); //CODIGO
					break;
					case 1:
						codigo = atoi(token);
						printf("El saldo resultante es:%d \n", saldo);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
		break;
		case EVT_RTA_DEPOSITO_NOK:
			printf("Rta deposito not ok\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						codigo = atoi(token);
						printf("COD de cliente:%d \n", codigo); //CODIGO
					break;
					case 1:
						mensaje_error = token;
						printf("Ocurrio un error :%s \n", mensaje_error);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
		break;
		case EVT_RTA_EXTRACCION_OK:
			printf("Rta extraccion\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						codigo = atoi(token);
						printf("COD de cliente:%d \n", codigo); //CODIGO
					break;
					case 1:
						codigo = atoi(token);
						printf("El saldo resultante es:%d \n", saldo);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
		break;
		case EVT_RTA_EXTRACCION_NOK:
			printf("Rta extraccion not ok\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						codigo = atoi(token);
						printf("COD de cliente:%d \n", codigo);
					break;
					case 1:
						mensaje_error = token;
						printf("Ocurrio un error :%s \n", mensaje_error);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
		break;

		default:
			printf("\nEvento sin definir\n");
		break;
	}

	printf("------------------------------\n");
}

//void *ThreadJugador (void *parametro)
//{
//	int 			nro_jugador;
//	int 			id_cola_mensajes;
//	int 			done=0;
//	char 	cadena[LARGO_TMENSAJE];
//	int             busqueda = 0;
//	int             found = 0;
//	mensaje		msg;
//
//	tjugador *datos_thread = (tjugador*) parametro;
//	nro_jugador = datos_thread->nro_jugador;
//	id_cola_mensajes = datos_thread->id_colamensaje;
//	int *vector_tambor = datos_thread->vector_tambor;
//
//	while(done==0)
//	{
//		recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);	//bloqueate
//
//		printf("Remitente %d \n", msg.int_rte);
//		printf("Destino   %d\n", (int) msg.long_dest);
//		printf("Evento    %d \n", msg.int_evento);
//		//printf("Mensaje   %s \n", msg.char_mensaje);
//		printf("------------------------------\n");
//
//		switch (msg.int_evento)
//		{
//			case EVT_INICIO:
//				pthread_mutex_lock (&mutex);
//				printf("Soy el jugador %d y voy a dispararme \n",nro_jugador);
//
//				while (found == 0 )
//				{
//					if (vector_tambor[busqueda] == 0)
//					{
//						found = 1;
//						vector_tambor[busqueda] = 1;
//					}else {
//						busqueda ++;
//					}
//				}
//				sprintf(cadena, "%d", busqueda);
//				sleep(1);
//				pthread_mutex_unlock (&mutex);
//				enviar_mensaje(id_cola_mensajes , MSG_REVOLVER , MSG_JUGADOR+nro_jugador ,EVT_DISPARO, cadena);
//				printf("Soy el jugador %d y la posicion del tambor es %d \n",nro_jugador,busqueda );
//				break;
//			case EVT_FIN:
//				printf("Jugador eliminado %d \n",nro_jugador);
//				done=1;
//				break;
//			case EVT_SALVADO:
//				done=1;
//				break;
//			default:
//				printf("Jugador %d Evento sin definir\n", nro_jugador);
//				break;
//		}
//	};
//	pthread_exit ((void *)"Listo");
//}

int mostrar_menu()
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tConsula\n");
    printf("2.\tDeposito\n");
    printf("3.\tExtraccion\n");
    printf("0.\tSalir\n\n");
    printf("Elija opcion: ");

    while( (scanf(" %d", &opcion) != 1)
          || (opcion < 0)
          || (opcion > MAX_MENU))
    {
      fflush(stdin);
      printf("No valido\n\n");
      printf("Elija opcion: ");
    }
    return opcion;
	
}
		
//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int saldo = 0;
	char cadena[LARGO_TMENSAJE];
	int opcion_elegida = 1;
	mensaje		msg;
	int codigo_cliente = 0;
	//int cantidad_jugadores = 6;
	//srand(time(NULL));
		
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	//int vector_tambor[] = {0,0,0,0,0,0};
	//
	//
	printf("Por favor ingresar codigo de cliente ");
	scanf("%d",&codigo_cliente);

	while (opcion_elegida != 0)
	{
		mostrar_menu();
		//pthread_mutex_init (&mutex, NULL);
		switch (opcion_elegida)
		{
			case 1:
				printf("Se eligio consulta saldo \n");
				sprintf(cadena, "%d", codigo_cliente);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO , MSG_BANCO ,EVT_CONSULTA_SALDO, cadena);
				break;
			case 2:
				printf("Se eligio deposito \n");
				printf("Ingresar saldo a depositar \n");
				scanf("%d",&saldo);
				sprintf(cadena, "%d|%d",codigo_cliente, saldo);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO , MSG_BANCO ,EVT_DEPOSITO, cadena);
				break;
			case 3:
				printf("Se eligio extraccion \n");
				printf("Ingresar saldo a extraer \n");
				scanf("%d",&saldo);
				sprintf(cadena, "%d|%d",codigo_cliente, saldo);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO , MSG_BANCO ,EVT_EXTRACCION, cadena);
				break;
			default:
				printf("Opcion desconocida \n");
		}

		recibir_mensaje(id_cola_mensajes, MSG_CAJERO_AUTOMATICO, &msg);	//bloqueate
		procesar_evento(id_cola_mensajes,msg);
}
	//pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_jugadores);
	//pthread_attr_t 	atributos;
	//pthread_attr_init (&atributos);
	//pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	//tjugador *datos_jugador;
	//datos_jugador = (tjugador*) malloc(sizeof(tjugador)*cantidad_jugadores);
	
	//for(i=0; i<cantidad_jugadores; i++)
	//{
	//	datos_jugador[i].id_colamensaje = id_cola_mensajes;
	//	datos_jugador[i].nro_jugador = i;
	//	datos_jugador[i].vector_tambor = vector_tambor;
	//	pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_jugador[i]);
	//	sleep(1);
	//}

	//for(j=0; j<cantidad_jugadores; j++)
	//{
	//	pthread_join (idHilo[j], NULL);
	//}
	return 0;
}



