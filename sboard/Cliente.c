#include <Socket.h>
#include <Socket_Cliente.h>
#include <Socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <Board.h>

#define MAX_CHAR_SEND 2048
#define MAX_MENU 5

int mostrar_menu()
{
    int opcion;

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
	scanf("%s", Cadena); 
	Cadena = server_interaction(Socket,Cadena);
	if(strcmp(Cadena,"0") != 0)
	{
		printf("El servidor dice:\n%s \n",Cadena); 
		scanf("%s", Cadena); 
		Cadena = server_interaction(Socket,Cadena);
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
			Cadena = server_interaction(Socket_Con_Servidor,Cadena);
			printf("El servidor dice:\n%s \n",Cadena); 
			scanf("%s", Cadena); 
			Cadena = server_interaction(Socket_Con_Servidor,Cadena);
			if(strcmp(Cadena,"0") != 0)
			{
				printf("El servidor dice:\n%s \n",Cadena); 
				scanf("%s", Cadena); 
				Cadena = server_interaction(Socket_Con_Servidor,Cadena);
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
			break;
		case 3:
			agregar_tarea(Socket_Con_Servidor,Cadena);
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
