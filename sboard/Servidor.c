#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_CHAR_SEND 100

#define MAX_MENU 5


typedef struct tipo_cliente tcliente;
struct tipo_cliente
{
	int  nro_socket;
};

typedef struct tipo_tarea ttarea;
struct tipo_tarea
{
	int  nro_tarea;
	char *descripcion;
};

ttarea *tareas[100];

char* generar_menu()
{

	//char* menu = "\n\nMenu \n\n 1.\tConsulta\n 2.\tDeposito\n 3.\tExtraccion\n 0.\tSalir\n\nElija opcion: ";
	char* menu = "\nConectado a Servidor";

	return menu;

}

void mostrarTareas(ttarea* tareas){

	printf("Mostrando tareas guardadas \n");

	int i;

	for(i=0;i<2;i++){

		printf("Tareas numero: %d descripcion: %s \n",i,tareas[i].descripcion);

	}

}

void agregar_tarea(int Socket_Cliente)
{
	char *Cadena;
	ttarea nueva_tarea;

	strcpy (Cadena, "Envie informacion de la tarea");
	Escribe_Socket (Socket_Cliente, Cadena, MAX_CHAR_SEND + 1);

	Lee_Socket (Socket_Cliente, Cadena, MAX_CHAR_SEND);

	nueva_tarea.descripcion = Cadena;

	for(int i = 0; i < 15 ; i++) 
	{ 
		if(!tareas[i])
		{
			nueva_tarea.nro_tarea = i;
			tareas[i]= &nueva_tarea;
			break;

		}

	}
	

}

void operar_tareas(int opcion_elegida,int Socket_Cliente)
{
	switch (opcion_elegida)
	{
		case 1:
			mostrarTareas(tareas);
			break;
		case 2:
			agregar_tarea(Socket_Cliente);
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
	char Cadena[100];

	tcliente *datos_cliente = (tcliente*) parametro;
	Socket_Cliente = datos_cliente->nro_socket;

	while(opcion_elegida !=0)
	{
		// lee info cliente 15 caracteres.
		Lee_Socket (Socket_Cliente, Cadena, MAX_CHAR_SEND);

		// Se escribe en pantalla la info  que se ha de cliente
		printf ("Soy Servior, he recibido : %s\n", Cadena);
		opcion_elegida = atoi(Cadena);
		operar_tareas(opcion_elegida,Socket_Cliente);

		// Cadena para enviar a Cliente long es 15 + \0 al final
		strcpy (Cadena, generar_menu());
		Escribe_Socket (Socket_Cliente, Cadena, MAX_CHAR_SEND + 1);

	}

	close (Socket_Cliente);

	pthread_exit ((void *)"Listo");
}

int main ()
{
	// Descriptores de socket servidor y de socket con el cliente
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena[100];

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
