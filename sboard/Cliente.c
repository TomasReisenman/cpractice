#include <Socket.h>
#include <Socket_Cliente.h>
#include <Socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <Board.h>

#define MAX_CHAR_SEND 2048
#define MAX_MENU 10

int mostrar_menu()
{
	int opcion;
	char resp[1000];
	

	printf("Menu\n\n");
	printf("1.\tMostrar Board\n");
	printf("2.\tVer tarea\n");
	printf("3.\tAgregar nueva tarea\n");
	printf("4.\tBorrar tarea\n");
	printf("5.\tModificar tarea\n");
	printf("6.\tMover tarea\n");
	printf("7.\tVer columna\n");
	printf("8.\tAgregar nueva columna\n");
	printf("9.\tBorrar Columna\n");
	printf("0.\tSalir\n\n");
	printf("Elija opcion: ");

	fgets(resp,1000,stdin);
	resp[strcspn(resp,"\n")]=0;
	return atoi(resp);

}

void read_input(char* resp)
{
	fgets(resp,1000,stdin);
	resp[strcspn(resp,"\n")]=0;
}

char *server_interaction(int Socket,char *message)
{

	char *Cadena;

	send_message(Socket,message);
	Cadena = get_message(Socket);

	return Cadena;

}

void agregar_tarea(int Socket,char *Cadena)
{

	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena);
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
		read_input(Cadena);
		Cadena = server_interaction(Socket,Cadena);
		printf("El servidor dice:\n%s \n",Cadena); 

	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}

void borrar_tarea(int Socket,char *Cadena)
{
	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
		read_input(Cadena); 
		Cadena = server_interaction(Socket,Cadena);
		if(strcmp(Cadena,"0") != 0)
		{

			printf("El servidor dice:\n%s \n",Cadena); 
		}else
		{
			printf("Tarea  no encontrado\n"); 
		}	
	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}


void modificar_tarea(int Socket,char *Cadena)
{
	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
		read_input(Cadena); 
		Cadena = server_interaction(Socket,Cadena);
		if(strcmp(Cadena,"0") != 0)
		{
			printf("El servidor dice:\n%s \n",Cadena); 
			read_input(Cadena); 
			Cadena = server_interaction(Socket,Cadena);
			printf("El servidor dice:\n%s \n",Cadena); 
		}else
		{
			printf("Tarea  no encontrado\n"); 
		}	
	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}



void mover_tarea(int Socket,char *Cadena)
{
	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
		read_input(Cadena); 
		Cadena = server_interaction(Socket,Cadena);
		if(strcmp(Cadena,"0") != 0)
		{
			printf("El servidor dice:\n%s \n",Cadena); 
			read_input(Cadena); 
			Cadena = server_interaction(Socket,Cadena);
			if(strcmp(Cadena,"0") != 0)
			{
				printf("El servidor dice:\n%s \n",Cadena); 
			}else
			{
				printf("Columna  no encontrado\n"); 
			}	
		}else
		{
			printf("Tarea  no encontrado\n"); 
		}	
	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}


void ver_tarea(int Socket,char *Cadena)
{

	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
		read_input(Cadena); 
		Cadena = server_interaction(Socket,Cadena);
		if(strcmp(Cadena,"0") != 0)
		{

			printf("El servidor dice:\n%s \n",Cadena); 
		}else
		{
			printf("Tarea  no encontrado\n"); 
		}	
	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}


void ver_columna(int Socket,char *Cadena)
{

	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}

void agregar_columna(int Socket,char *Cadena)
{

	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
}


void borrar_columna(int Socket,char *Cadena)
{
	Cadena = server_interaction(Socket,Cadena);
	printf("El servidor dice:\n%s \n",Cadena); 
	read_input(Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
	}else
	{
		printf("Columna no encontrado\n"); 
	}	
}


void realizar_operacion(int opcion_elegida,int Socket_Con_Servidor)
{
	char *Cadena = (char *) malloc(sizeof(char)*2048);

	printf("Se eligio %d \n",opcion_elegida); 

	sprintf(Cadena,"%d",opcion_elegida);
	switch (opcion_elegida)
	{
		case 1:
			Cadena = server_interaction(Socket_Con_Servidor,Cadena);
			printf("El servidor dice:\n%s \n",Cadena); 
			break;
		case 2:
			ver_tarea(Socket_Con_Servidor,Cadena);
			break;
		case 3:
			agregar_tarea(Socket_Con_Servidor,Cadena);
			break;
		case 4:
			borrar_tarea(Socket_Con_Servidor,Cadena);
			break;
		case 5:
			modificar_tarea(Socket_Con_Servidor,Cadena);
			break;
		case 6:
			mover_tarea(Socket_Con_Servidor,Cadena);
			break;
		case 7:
			ver_columna(Socket_Con_Servidor,Cadena);
			break;
		case 8:
			agregar_columna(Socket_Con_Servidor,Cadena);
			break;
		case 9:
			borrar_columna(Socket_Con_Servidor,Cadena);
			break;
		case 0:
			printf("Cliente se desconecta\n" );
			break;
		default:
			printf("Evento sin definir\n" );
			break;
	}

}

int main ()
{
	int Socket_Con_Servidor;
	char Cadena[MAX_CHAR_SEND];
	int opcion_elegida = 1;

	Socket_Con_Servidor = Abre_Conexion_Inet ("localhost", "cpp_java");
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}

	opcion_elegida = mostrar_menu();
	while(opcion_elegida != 0)

	{
		realizar_operacion(opcion_elegida,Socket_Con_Servidor);
		opcion_elegida = mostrar_menu();
	}
	sprintf(Cadena,"%d",opcion_elegida);
	printf("Se eligio %d \n",opcion_elegida); 
	Escribe_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND);

	close (Socket_Con_Servidor);
}
