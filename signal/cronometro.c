#include <unistd.h>
#include <signal.h>
#include <stdio.h>
 
// Esta es la función que se va a ejecutar cada vez que se reciba la
// señal SIGALRM
void contar_segundos() {
	// Usamos static para que se conserve el valor de "segundos"
	// entre cada llamada a la función
	static int segundos=0;
 
	segundos++;
	printf("Han pasado %d segundos.\n", segundos);
}
 
int main() {
	// Asociamos la señal SIGALRM a la función contar_segundos
	signal(SIGALRM, contar_segundos);
 
	// Ponemos en marcha un bucle
	while(1) 
	{
		// Establecemos una alarma para dentro de un segundo
		alarm(1);
		// Pausamos la ejecución del programa para que 
		// se quede esperando a recibir una señal.
		pause();
	}
}