#include "funciones.h"
#include "definiciones.h"
#include <pthread.h>

#define VEHICULOS_DESDE 1
#define VEHICULOS_HASTA 2
#define MAX_LIBERAR 10
#define MAX_MENU 3

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
						saldo = atoi(token);
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
						saldo = atoi(token);
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
						saldo = atoi(token);
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

int mostrar_menu()
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tConsulta\n");
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

	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	printf("Por favor ingresar codigo de cliente ");
	scanf("%d",&codigo_cliente);

	opcion_elegida = mostrar_menu();
	while (opcion_elegida != 0)
	{
		switch (opcion_elegida)
		{
			case 1:
				printf("Se eligio consulta saldo \n");
				sprintf(cadena, "%d", codigo_cliente);
				enviar_mensaje(id_cola_mensajes , MSG_BANCO , MSG_CAJERO_AUTOMATICO ,EVT_CONSULTA_SALDO, cadena);
				break;
			case 2:
				printf("Se eligio deposito \n");
				printf("Ingresar saldo a depositar \n");
				scanf("%d",&saldo);
				sprintf(cadena, "%d|%d",codigo_cliente, saldo);
				enviar_mensaje(id_cola_mensajes , MSG_BANCO , MSG_CAJERO_AUTOMATICO ,EVT_DEPOSITO, cadena);
				break;
			case 3:
				printf("Se eligio extraccion \n");
				printf("Ingresar saldo a extraer \n");
				scanf("%d",&saldo);
				sprintf(cadena, "%d|%d",codigo_cliente, saldo);
				enviar_mensaje(id_cola_mensajes , MSG_BANCO , MSG_CAJERO_AUTOMATICO ,EVT_EXTRACCION, cadena);
				break;
			default:
				printf("Opcion desconocida \n");
		}

		recibir_mensaje(id_cola_mensajes, MSG_CAJERO_AUTOMATICO, &msg);	//bloqueate
		procesar_evento(id_cola_mensajes,msg);

		opcion_elegida = mostrar_menu();
}
	return 0;
}



