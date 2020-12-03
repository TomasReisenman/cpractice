#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <Board.h>

#define MAX_CHAR_SEND 2048

#define MAX_MENU 5


typedef struct tipo_cliente tcliente;
struct tipo_cliente
{
	int  nro_socket;
};

Columna *head = NULL;	
int cantTareas = 0;
int cantColumnas = 0;
int cantClientes = 0;


char *client_interaction(int Socket,char *message)
{

	char *Cadena;

	send_message(Socket,message);
	Cadena = get_message(Socket);
	printf("El cliente dice:\n%s \n",Cadena); 

	return Cadena;

}
void mostrarBoard(int Socket_Cliente)
{

	Columna *current_node = head;
	char *temp;
	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);

	printf("Mostrando Board\n");
	strcat(result,printColumna(head));
	strcat(result,"|-----------------------|\n");

	for(int i = 0; i < 10; i++) { 
		while ( current_node != NULL) {
			temp = printTarea(i,current_node);
			temp = shortenString(temp,12);
			strcat(result,temp);
			current_node = current_node->next;
		}
		current_node = head;
		strcat(result,"\n"); 

	}
	printf("Se envio al cliente:\n%s",result);
	sprintf(temp,"%d",strlen(result));
	send_message(Socket_Cliente,result);

}

void verTarea(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;
	Tarea *tarea;

	printf("Se eligio ver tarea\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{

		sprintf(result,"Se eligio columna %s Indique nuemro de tarea \n ",temp);
		temp = client_interaction(Socket_Cliente,result);
		printf("Se eligio tarea %s\n",temp);
		tarea  = findTarea(atoi(temp),found);
		if(tarea != NULL)
		{
			send_message(Socket_Cliente,tarea->descripcion);
		}else
		{
			send_message(Socket_Cliente,"0");

		}


	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}


}

void borrarTarea(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;
	Tarea *tarea;

	printf("Se eligio ver tarea\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{

		sprintf(result,"Se eligio columna %s Indique nuemro de tarea \n ",temp);
		temp = client_interaction(Socket_Cliente,result);
		printf("Se eligio tarea %s\n",temp);
		tarea  = findTarea(atoi(temp),found);
		if(tarea != NULL)
		{
			removeTarea(tarea->numero,found);
			send_message(Socket_Cliente,"Tarea borrada\n");
		}else
		{
			send_message(Socket_Cliente,"0");

		}


	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}


}


void modificarTarea(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;
	Tarea *tarea;

	printf("Se eligio ver tarea\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{

		sprintf(result,"Se eligio columna %s Indique nuemro de tarea \n ",temp);
		temp = client_interaction(Socket_Cliente,result);
		printf("Se eligio tarea %s\n",temp);
		tarea  = findTarea(atoi(temp),found);
		if(tarea != NULL)
		{
			sprintf(result,"Se eligio tarea %s Indique nuevo texto \n ",temp);
			temp = client_interaction(Socket_Cliente,result);
			editTarea(tarea,temp);
			send_message(Socket_Cliente,"Tarea modificada\n");
		}else
		{
			send_message(Socket_Cliente,"0");

		}


	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}


}

void moverTarea(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;
	Columna *to;
	Tarea *tarea;

	printf("Se eligio ver tarea\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{

		sprintf(result,"Se eligio columna %s Indique nuemro de tarea \n ",temp);
		temp = client_interaction(Socket_Cliente,result);
		printf("Se eligio tarea %s\n",temp);
		tarea  = findTarea(atoi(temp),found);
		if(tarea != NULL)
		{
			sprintf(result,"Se eligio tarea %s Indique columna destino \n ",temp);
			temp = client_interaction(Socket_Cliente,result);
			printf("Se eligio Columna %s\n",temp);
			to = findColumna(atoi(temp),head);
			if(to != NULL)
			{
				moveTarea(found,to,tarea->numero);
				send_message(Socket_Cliente,"Tarea movida\n");
			}else
			{
				send_message(Socket_Cliente,"0");

			}
		}else
		{
			send_message(Socket_Cliente,"0");

		}


	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}


}
void agregarTarea(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;
	Tarea *tarea;

	printf("Se eligio agregar  tarea\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{

		sprintf(result,"Se eligio columna %s Indique Descipcion de Tarea \n ",temp);
		temp = client_interaction(Socket_Cliente,result);
		printf("Descripcion %s\n",temp);
		cantTareas ++;
		appendTarea(cantTareas,temp,found);	
		send_message(Socket_Cliente,"Tarea Agregada");

	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}


}


void verColumna(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;

	printf("Se eligio ver tarea\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{
		printf("here we are%s \n",found->nombre); 
		sprintf(result,"Mostrando Columna \n%s",found->nombre);
		send_message(Socket_Cliente,result);
	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}

}


void agregarColumna(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;

	printf("Se eligio agregar Columna\n");
	strcpy(result,"Ingrese nombre de Columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Nombre ingresado %s\n",temp);

	findColumna(atoi(temp),head);
	cantColumnas ++;
	head = appendColumna(cantColumnas,temp,head);
	send_message(Socket_Cliente,"Columna agregada");

}

void borrarColumna(int Socket_Cliente)
{

	char *result = (char *) malloc(sizeof(char)*MAX_CHAR_SEND);
	char *temp;
	Columna *found;
	Tarea *tarea;

	printf("Se eligio borrar columna\n");
	strcpy(result,"Indique nuemro de columna");
	temp = client_interaction(Socket_Cliente,result);
	printf("Se eligio columna %s\n",temp);

	found = findColumna(atoi(temp),head);

	if(found != NULL)
	{

		head = removeColumna(found->numero,head);	
		send_message(Socket_Cliente,"Columna borrada\n");

	}
	else{
		sprintf(result,"0");
		send_message(Socket_Cliente,"0");
	
	}


}

void operar_tareas(int opcion_elegida,int Socket_Cliente)
{
	switch (opcion_elegida)
	{
		case 1:
			mostrarBoard(Socket_Cliente);
			break;
		case 2:
			verTarea(Socket_Cliente);
			break;
		case 3:
			agregarTarea(Socket_Cliente);
			break;
		case 4:
			borrarTarea(Socket_Cliente);
			break;
		case 5:
			modificarTarea(Socket_Cliente);
			break;
		case 6:
			moverTarea(Socket_Cliente);
			break;
		case 7:
			verColumna(Socket_Cliente);
			break;
		case 8:
			agregarColumna(Socket_Cliente);
			break;
		case 9:
			borrarColumna(Socket_Cliente);
			break;
		case 0:
			printf("Cliente se desconecta\n" );
			break;
		default:
			printf("Evento sin definir\n" );
			break;
	}

}

void *ThreadCliente (void *parametro)
{
	int opcion_elegida = 1;
	int Socket_Cliente;
	char *Cadena;

	tcliente *datos_cliente = (tcliente*) parametro;
	Socket_Cliente = datos_cliente->nro_socket;

	while(opcion_elegida !=0)
	{
		printf("Leeyendo info de Cliente\n");
		Cadena = get_message(Socket_Cliente);	
		printf ("Soy Servior, he recibido : %s\n", Cadena);
		opcion_elegida = atoi(Cadena);
		operar_tareas(opcion_elegida,Socket_Cliente);


	}

	close (Socket_Cliente);

	pthread_exit ((void *)"Listo");
}

void inicilalizarBoard()
{

	head = appendColumna(cantColumnas,"Para Hacer",head);
	cantColumnas ++;
	head = appendColumna(cantColumnas,"En Progreso",head);
	cantColumnas ++;
	head = appendColumna(cantColumnas,"Haciendo",head);

	cantTareas ++;	
	appendTarea(cantTareas,"Diagrama",head);
	cantTareas ++;	
	appendTarea(cantTareas,"Base de Datos",head);

	Columna *found = findColumna(1,head);
	cantTareas ++;	
	appendTarea(cantTareas,"Gant",found);
	cantTareas ++;	
	appendTarea(cantTareas,"Org app ex",found);

}

int main ()
{
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena[MAX_CHAR_SEND];
	printf("Iniciando Server\n");

	inicilalizarBoard();

	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}


	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*10);
	pthread_attr_t 	atributos;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	tcliente *datos_cliente;
	datos_cliente = (tcliente*) malloc(sizeof(tcliente)*2);


	
	while(1)
	{
		Socket_Cliente = Acepta_Conexion_Cliente (Socket_Servidor);
		if (Socket_Servidor == -1)
		{
			printf ("No se puede abrir socket de cliente\n");
			exit (-1);
		}

		datos_cliente[cantClientes].nro_socket = Socket_Cliente;
		pthread_create (&idHilo[cantClientes], &atributos, ThreadCliente, &datos_cliente[cantClientes]);
		cantClientes ++;
	}
	close (Socket_Servidor);
}
