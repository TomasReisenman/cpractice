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
		//temp = client_interaction(Socket_Cliente,result);
		send_message(Socket_Cliente,"0");
	
	}

	//send_message(Socket_Cliente,result);

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
		//tarea  = findTarea(atoi(temp),found);
		cantTareas ++;
		appendTarea(cantTareas,temp,found);	
		send_message(Socket_Cliente,"Tarea Agregada");

	}
	else{
		sprintf(result,"0");
		//temp = client_interaction(Socket_Cliente,result);
		send_message(Socket_Cliente,"0");
	
	}

	//send_message(Socket_Cliente,result);

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
		// lee info cliente 15 caracteres.
		printf("Leeyendo info de Cliente\n");
		//Lee_Socket (Socket_Cliente, Cadena, 1);
		Cadena = get_message(Socket_Cliente);	

		// Se escribe en pantalla la info  que se ha de cliente
		printf ("Soy Servior, he recibido : %s\n", Cadena);
		opcion_elegida = atoi(Cadena);
		operar_tareas(opcion_elegida,Socket_Cliente);

		// Cadena para enviar a Cliente long es 15 + \0 al final
		//strcpy (Cadena, generar_menu());
		//Escribe_Socket (Socket_Cliente, Cadena, MAX_CHAR_SEND + 1);

	}

	close (Socket_Cliente);

	pthread_exit ((void *)"Listo");
}

void inicilalizarBoard()
{

	head = appendColumna(0,"Para Hacer",head);
	head = appendColumna(1,"En Progreso",head);
	head = appendColumna(2,"Haciendo",head);

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
	// Descriptores de socket servidor y de socket con el cliente
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena[MAX_CHAR_SEND];
	printf("Iniciando Server\n");

	inicilalizarBoard();

	//agregarColumna("Para hacer");
	//agregarColumna("En progreso");
	//agregarColumna("Terminadas");
	//mostrarColumnas();
	//borrarColumna(1);
	//mostrarColumnas();

	//agregarTareaAColumna(0,"cosas");
	//agregarTareaAColumna(0,"mas cosas");
	//mostrarColumnaCompleta(columnas[0]);

	//tareas = (ttarea*) malloc(sizeof(ttarea)*2);
	//  Se abre el socket servidor, con el servicio "cpp_java" dado de  alta en /etc/services.
	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}


	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*2);
	pthread_attr_t 	atributos;
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	tcliente *datos_cliente;
	datos_cliente = (tcliente*) malloc(sizeof(tcliente)*2);


	
	while(1)
	{
		// Se espera un cliente que quiera conectarse
		Socket_Cliente = Acepta_Conexion_Cliente (Socket_Servidor);
		if (Socket_Servidor == -1)
		{
			printf ("No se puede abrir socket de cliente\n");
			exit (-1);
		}

		datos_cliente[0].nro_socket = Socket_Cliente;

		pthread_create (&idHilo[0], &atributos, ThreadCliente, &datos_cliente[0]);
	}
	close (Socket_Servidor);
}
