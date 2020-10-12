#include "funciones.h"
#include "definiciones.h"
 
#define INTERVALO_PEDIDOS 5000

//stock	inventario[CANTIDAD_TOTAL];

//int	cargar_codigos(codigos *ptr_codigos)
//{
//	ptr_codigos[0].codigo = 1;
//	strcpy(ptr_codigos[0].descripcion, "LECHE");
//
//	ptr_codigos[1].codigo = 2;
//	strcpy(ptr_codigos[1].descripcion, "HUEVOS");
//
//	ptr_codigos[2].codigo = 3;
//	strcpy(ptr_codigos[2].descripcion, "MANTECA");
//
//	ptr_codigos[3].codigo = 4;
//	strcpy(ptr_codigos[3].descripcion, "AZUCAR");
//	return 0;
//}

void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	char 	cadena[LARGO_TMENSAJE];
	int 	count = 0;
	int		primer_val=0;
	int 	segundo_val=0;
	int     resultado=0;
	char 	*token;
	//int	i;

	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_SUMA:
			printf("Suma de Valores\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						primer_val=atoi(token);
						printf("primer valor :%d \n", primer_val); //PRIMER_VAL
					break; 
					case 1:
						segundo_val=atoi(token);
						printf("segundo valor :%d \n", segundo_val); //SEGUNDO_VAL
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			resultado = primer_val + segundo_val;
			sprintf(cadena, "%d", resultado);
			printf("Resultado es : %s",cadena);
			enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_CALCULADOR, EVT_RESULTADO, cadena);
			break;
		case EVT_PRODUCTO:
			printf("Producto de Valores\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						primer_val=atoi(token);
						printf("primer valor :%d \n", primer_val); //PRIMER_VAL
					break;
					case 1:
						segundo_val=atoi(token);
						printf("segundo valor :%d \n", segundo_val); //SEGUNDO_VAL
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			resultado = primer_val * segundo_val;
			sprintf(cadena, "%d", resultado);
			printf("Resultado es : %s",cadena);
			enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_CALCULADOR, EVT_RESULTADO, cadena);
			break;
		default:
			printf("\nEvento sin definir\n");
		break;
	}
	//printf("\nINVENTARIO\n");
	//for(i=0; i<CANTIDAD_TOTAL;i++)
	//	printf("COD: %d CANT: %d\n", inventario[i].codigo, inventario[i].cantidad);
	printf("------------------------------\n");
}

	
int main()
{
	//codigos*		memoria_codigos = NULL;
	//int 			id_memoria_codigos;
	int 			id_cola_mensajes;
	//int				i;
	mensaje			msg;

	
	//for(i=0;i<CANTIDAD_TOTAL; i++)
	//{
	//	inventario[i].codigo = i+1;
	//	inventario[i].cantidad = 0;
	//}

	//memoria_codigos 	= (codigos*) creo_memoria(id_memoria_codigos, &id_memoria_codigos, CLAVE_BASE );

	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	
	//cargar_codigos(memoria_codigos); //Carga los codigos en memoria compartida con la descripcion.
	
	while(1)
	{
		recibir_mensaje(id_cola_mensajes, MSG_CALCULADOR, &msg);
		procesar_evento(id_cola_mensajes, msg);
	};

	return 0;
}


