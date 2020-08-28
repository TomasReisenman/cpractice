#include<stdio.h>
#define CANTIDAD 10

/* 
	Ejemplo debugger: 

		1) complilar: gcc -o largo -g largo.c
			// compila perfectamente... no tiene errores de compilacion

		2) ejecutar: ./largo

		3) Error en tiempo de ejecucion: segmentation fault

		4) ejecutar: gdb largo

		5) en gdb ejecutar: run
			// nos indica donde esta el error, en que linea y el tipo de error.

		6) salir del gdb con ctrl-z		
		 
*/

int main()
{
	int i;
	int *a = NULL;
	for (i=0; i<CANTIDAD; i++){
		printf("%d, ",i);
	}
	printf("\n");
	
	*a=3;
	return 0;
}

