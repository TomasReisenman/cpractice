#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <sys/time.h>


typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	int	primer_val;
	int segundo_val;
	int suma;
	int producto;
};
		  

void *funcionSumaThread (void *parametro)
{

	mensaje* ptr = (mensaje*) parametro; //recibo el parametro y lo casteo como int *;

	mensaje n= *ptr;


	printf("Sumando valores dentro de mensaje %d %d \n",n.primer_val,n.segundo_val);

	//*ptr = total; //utilizo *ptr para cargar el parametro de entrada el dato de salida.
	ptr->suma = n.primer_val + n.segundo_val;

	pthread_exit ((void*)0); //Esto solo puedo utilizarlo para devolver valores de status, no puedo devolver valores creados en la propia funcion thread.
}

void *funcionProductoThread (void *parametro)
{

	mensaje* ptr = (mensaje*) parametro;

	mensaje n= *ptr;


	printf("Multiplicando valores dentro de mensaje %d %d \n",n.primer_val,n.segundo_val);

	ptr->producto = n.primer_val * n.segundo_val;

	pthread_exit ((void*)0);
}
int difMilli(struct timeval tiempo_start, struct timeval tiempo_end)
{
	int sec_start, micro_start;
	int start;
	int sec_end, micro_end;
	int end;

	sec_start   = tiempo_start.tv_sec & 0xFFF;
	micro_start = tiempo_start.tv_usec;
	start = (sec_start *1000) + (micro_start/1000);

	sec_end   = tiempo_end.tv_sec & 0xFFF;
	micro_end = tiempo_end.tv_usec;
	end = (sec_end *1000) + (micro_end/1000);
	return end - start;
}

int main (int argc, char *argv[])
{
	//char con_thread = 's';
	//int i, total=0;
	int cantidad = 2;
	//int* num = (int*) malloc(sizeof(int)*(argc-1));
	int primer_val = atoi(argv[1]);
	int segundo_val = atoi(argv[2]);
	
	struct timeval 	t_inicio;
	struct timeval 	t_final;

	mensaje mensaje;
	mensaje.primer_val =  primer_val;
	mensaje.segundo_val =  segundo_val;
	
	pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad);
	pthread_attr_t 	atributos;
	
	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	//printf("PPAL: Cantidad = %d\n", cantidad);
	
	//printf("PPAL: Con thread (s/n)");
	//scanf(" %c", &con_thread);

	//if (con_thread=='s')
	//	printf("\nPPAL: CON THREAD\n");
	//else
	//	printf("\nPPAL: SIN THREAD\n");
	//gettimeofday(&t_inicio, 0);


	//for(i=0; i<cantidad; i++)
	//{
	//	num[i]=atoi(argv[i+1]);
	//	if (con_thread=='s')
	//		pthread_create (&idHilo[i], &atributos, funcionPrimosThread, &num[i]);
	//	else
	//		total +=funcionPrimos(num[i]);
	//}

	pthread_create (&idHilo[0], &atributos, funcionSumaThread, &mensaje);
	pthread_create (&idHilo[1], &atributos, funcionProductoThread, &mensaje);
	
	//if (con_thread=='s')
	//{
	//	for(i=0; i<cantidad; i++)
	//	{
	//		printf("PPAL: Voy a esperar al thread %d\n", i);
	//		pthread_join (idHilo[i], NULL);
	//		printf("PPAL: Recibi: %d\n", num[i]);
	//		total +=num[i];
	//	}
	//}
	pthread_join (idHilo[0], NULL);
	pthread_join (idHilo[1], NULL);
	
	printf("La suma es %d \n", mensaje.suma);
	printf("El producto es %d \n", mensaje.producto);
	printf("La resolucion final  es %d \n", mensaje.suma + mensaje.producto);
	
	//gettimeofday(&t_final, 0);

	//printf("PPAL: Tiemplo empleado %dms\n", difMilli(t_inicio, t_final));
	free(idHilo);
    return 0;
}
