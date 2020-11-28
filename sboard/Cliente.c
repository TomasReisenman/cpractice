#include <stdio.h>
#include <Socket_Cliente.h>
#include <Socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CHAR_SEND 100
#define MAX_MENU 5

int mostrar_menu()
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tConsulta\n");
    printf("2.\tAgregar nueva tarea\n");
    //printf("3.\tExtraccion\n");
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

void realizar_operacion(int opcion_elegida,int Socket_Con_Servidor)
{
	char Cadena[100];

	printf("Se eligio %d \n",opcion_elegida); 

	sprintf(Cadena,"%d",opcion_elegida);
	switch (opcion_elegida)
	{
		case 1:
			Escribe_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND);
			break;
		case 2:
			//printf(" Here we are \n");
			Escribe_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND);
			Lee_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND + 1);
			printf("El servidor dice  %s \n",Cadena); 
			scanf("%s",Cadena);
			Escribe_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND);
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
	// Descriptor del socket y buffer para datos
	int Socket_Con_Servidor;
	char Cadena[100];
	int opcion_elegida = 1;

	//  Abre la conexion con el servidor, (nombre del ordenador,servicio solicitado) 
	//  "localhost"  dado de alta en /etc/hosts
	//  "cpp_java" es un servicio dado de alta en /etc/services
	Socket_Con_Servidor = Abre_Conexion_Inet ("localhost", "cpp_java");
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}

	opcion_elegida = mostrar_menu();
	while(opcion_elegida != 0)

	{

		// Prepara cadena con 15 caracteres y se envia, 14 letras +  \0 que indica fin de cadena en C
		//strcpy (Cadena, "Hola");
		//scanf("%s",Cadena);
		//sprintf(Cadena,"%d",opcion_elegida);
		//printf("Se eligio %d \n",opcion_elegida); 
		//Escribe_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND);

		// Se lee la informacion enviada por el servidor, que se supone es  una cadena de 6 caracteres.
		//Lee_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND + 1);
		realizar_operacion(opcion_elegida,Socket_Con_Servidor);
		// Se escribe en pantalla la informacion recibida del servidor
		//printf ("Soy cliente, He recibido : %s\n", Cadena);
		opcion_elegida = mostrar_menu();
	}
	sprintf(Cadena,"%d",opcion_elegida);
	printf("Se eligio %d \n",opcion_elegida); 
	Escribe_Socket (Socket_Con_Servidor, Cadena, MAX_CHAR_SEND);

	close (Socket_Con_Servidor);
}
