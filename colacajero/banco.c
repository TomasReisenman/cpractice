#include "funciones.h"
#include "definiciones.h"

#define INTERVALO_DESDE 100
#define INTERVALO_HASTA 500

//#define VEHICULOS_DESDE 1
//#define VEHICULOS_HASTA 5
#define CANTIDAD_CUENTAS 100
#define DESDE 2500
#define HASTA 3500


void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	char cadena[LARGO_TMENSAJE];
	//int nro_recibido = atoi(msg.char_mensaje);
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
		case EVT_CONSULTA_SALDO:
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
		case EVT_DEPOSITO:
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
		case EVT_EXTRACCION:
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
		default:
			printf("\nEvento sin definir\n");
		break;
	}

	printf("------------------------------\n");
}

void inicializar_cuentas(int cuentas[]){

  int i;
  for(i = 0;i<CANTIDAD_CUENTAS;i++){

    cuentas[i] = (rand()%(HASTA-DESDE+1))+DESDE;
  }

}
//int main(int argc, char *argv[])
int main()
{
	int id_cola_mensajes;
	int i, j;
	//int cantidad_jugadores=6;
	//int nro_elegido=0;
	int cantidad = 100;
	char cadena[100];
	mensaje		msg;
	int* cuentas = (int*) malloc(cantidad*sizeof(int));
	inicializar_cuentas(cuentas);
	
	//printf("%d\n", cantidad_jugadores);
	//srand(time(NULL));
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	//nro_elegido = rand()%(cantidad_jugadores-0)+0;
	//printf("El numero elegido es %d\n", nro_elegido);

	borrar_mensajes(id_cola_mensajes);

	//for(i = 0;i<cantidad_jugadores;i++ )
	//{
	//	enviar_mensaje(id_cola_mensajes , MSG_JUGADOR+i, MSG_REVOLVER, EVT_INICIO, cadena);
	//}
	//for(j=0; j<cantidad_jugadores; j++)
	//{
	//	recibir_mensaje(id_cola_mensajes, MSG_REVOLVER, &msg);	//bloqueate
	//	procesar_evento(id_cola_mensajes,msg,nro_elegido);
	//}
	while (1) {
		recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);	//bloqueate
		procesar_evento(id_cola_mensajes,msg);
	}

	return 0;
}

    
