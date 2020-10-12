#include "funciones.h"
#include "definiciones.h"
#define INTERVALO_PEDIDOS 10000
 
char* leer_codigos(codigos *ptr_codigos, int codigo)
{
	static char descripcion[LARGO_DESCRIPCION];
	strcpy(descripcion, ptr_codigos[codigo-1].descripcion);
	return descripcion;
}

void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	//int count = 0;
	//int codigo;
	//int cantidad;
	//char *token;
	//codigos*	memoria_codigos = ptr_codigos;
	printf("\n------------------------------\n");
	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_RESULTADO:
			printf("Resultado es %s",msg.char_mensaje);
		break;

		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printf("------------------------------\n");
}


int main(int argc,char *argv[])
//int main()
{
	//codigos*		memoria_codigos = NULL;
	//int 			id_memoria_codigos;
	int 			id_cola_mensajes;
	mensaje			msg;
	//int 			codigo;
	char 			cadena[LARGO_TMENSAJE];
	int primer_val = atoi(argv[1]);
	int segundo_val = atoi(argv[2]);
	int opcion = atoi(argv[3]);
	//int cantidad;

	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	//memoria_codigos 	= (codigos*) creo_memoria(id_memoria_codigos, &id_memoria_codigos, CLAVE_BASE);
	
	//printf("%s\n", leer_codigos(memoria_codigos, 2));
	
	//while(1)
	//{
		//codigo = rand()%(HASTA_CODIGO-DESDE_CODIGO+1)+DESDE_CODIGO; 		//UN CODIGO ALEATORIO
		//cantidad = rand()%(HASTA_CANTIDAD-DESDE_CANTIDAD+1)+DESDE_CANTIDAD;	//UNA CANTIDAD ALEATORIA
		
		sprintf(cadena, "%d|%d", primer_val, segundo_val);	//armo CODIGO|CANTIDAD
		//printf("Agrego al COD: %d (%s) CANT: %d\n", codigo, leer_codigos(memoria_codigos, codigo), cantidad);

		if (opcion == 1 ) {
			enviar_mensaje(id_cola_mensajes , MSG_CALCULADOR, MSG_SOLICITANTE, EVT_SUMA, cadena); //Envio para que sume
		}

		if (opcion == 2 ) {
			enviar_mensaje(id_cola_mensajes , MSG_CALCULADOR, MSG_SOLICITANTE, EVT_PRODUCTO, cadena); //Envio para que sume
		}
		//sprintf(cadena, "%d", codigo);
		//printf("Consulto COD: %d (%s) \n", codigo, leer_codigos(memoria_codigos, codigo));
		//enviar_mensaje(id_cola_mensajes , MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_CONSULTA_STOCK, cadena); //Consulto stock.

		recibir_mensaje(id_cola_mensajes, MSG_SOLICITANTE, &msg); //espero respuesta.
		procesar_evento(id_cola_mensajes, msg);
		
		usleep (INTERVALO_PEDIDOS*1000);
	//};
	
	return 0;
}
