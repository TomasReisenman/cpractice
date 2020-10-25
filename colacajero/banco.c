#include "funciones.h"
#include "definiciones.h"

#define INTERVALO_DESDE 100
#define INTERVALO_HASTA 500

#define CANTIDAD_CUENTAS 100
#define DESDE 2500
#define HASTA 3500


void procesar_evento(int id_cola_mensajes, mensaje msg,int* cuentas)
{
	char cadena[LARGO_TMENSAJE];
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
			codigo = atoi(msg.char_mensaje);
			saldo = cuentas[codigo];
			printf("COD de cliente:%d \n", codigo);
			printf("El saldo del cliente es %d \n",saldo);
			sprintf(cadena, "%d", saldo);
			enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO, MSG_BANCO , EVT_RTA_SALDO, cadena);
		break;
		case EVT_DEPOSITO:
			printf("Se recibio pedido de deposito\n");
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
						//mensaje_error = token;
						saldo = atoi(token);
						printf("Saldo para deposito es :%d \n", saldo);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			if (saldo > 0) {
				printf("Saldo acceptado");
				cuentas[codigo] += saldo;
				saldo = cuentas[codigo];
				sprintf(cadena, "%d|%d",codigo, saldo);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO, MSG_BANCO , EVT_RTA_DEPOSITO_OK, cadena);
			}
			else {
				mensaje_error = "El saldo debe ser mayor a 0";
				printf("Ocurrio un error en deposito");
				sprintf(cadena, "%d|%s",codigo, mensaje_error);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO, MSG_BANCO , EVT_RTA_DEPOSITO_NOK, cadena);
			}

		break;
		case EVT_EXTRACCION:
			printf("Rta extraccion \n");
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
						printf("Saldo para extraccion es :%d \n", saldo);
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			if (saldo > 0 && cuentas[codigo] >= saldo) {
				printf("Saldo acceptado");
				cuentas[codigo] -= saldo;
				saldo = cuentas[codigo];
				sprintf(cadena, "%d|%d",codigo, saldo);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO, MSG_BANCO , EVT_RTA_SALDO, cadena);
			}
			else {
				mensaje_error = "El saldo debe ser mayor a 0 y menor a la cantidad en cuenta";
				printf("Ocurrio un error en extraccion");
				sprintf(cadena, "%d|%s",codigo, mensaje_error);
				enviar_mensaje(id_cola_mensajes , MSG_CAJERO_AUTOMATICO, MSG_BANCO , EVT_RTA_SALDO_NOK, cadena);
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
	int cantidad = 100;
	char cadena[100];
	mensaje		msg;
	int* cuentas = (int*) malloc(cantidad*sizeof(int));
	inicializar_cuentas(cuentas);
	
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);

	while (1) {
		recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);	//bloqueate
		procesar_evento(id_cola_mensajes,msg,cuentas);
	}

	return 0;
}

    
