#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define CANTIDAD_PARTIDA 	10
#define INTERVALO_PRODUCTO 	500
#define INTERVALO_PARTIDA 	1000
#define ROJO  			0
#define VERDE 			1
#define LARGO 			100

typedef struct {

	int cantCheck;
	int totalCheck;
	int cantEffect;
	int totalEffect;

}Reporte;

//mostrarArray(Reserva reservas[]){
//
//	int i;
//
//	for(i=0;i<11;i++){
//
//		printf("%d %d \n",i,reservas[i]);
//
//	}
//
//}

Reporte analizar_documento_cajero(char nombreDocumento[])
{

	FILE *leedor = fopen(nombreDocumento, "r");
	char cadena[LARGO]; 
	int effectivo =0;
	int effecTipo =0;

	Reporte rep;
	rep.cantEffect = 0;
	rep.totalEffect = 0;
	rep.cantCheck = 0;
	rep.totalCheck = 0;

	if (leedor!=NULL)
	{
		printf("\nTesorero lee los datos \n");

		while (!feof(leedor))
		{
			fscanf(leedor,"%d-%d",&effectivo,&effecTipo);
			//fscanf(leedor,"%s",cadena);
			if(!feof(leedor))
			{
				printf("datos leidos %s %d %d \n",nombreDocumento, effectivo,effecTipo);
				//effectivo = atoi(cadena);
				if(effecTipo)
				{
					rep.cantEffect ++;	
					rep.totalEffect += effectivo;

				}else 
				{

					rep.cantCheck ++;
					rep.totalCheck += effectivo;	
				

				}	
				//printf("total effect is %d,%d \n",rep.totalEffect,rep.totalCheck);
				usleep(INTERVALO_PRODUCTO*1000);
				//cant_reserva++;
			}
		}
		//nro_partida++;
		//mostrarArray(reservas);
		fclose(leedor);
		if(rep.cantEffect>0 || rep.cantCheck>0)
		{
			printf("\nBORRAMOS\n");
			remove(nombreDocumento);
			//cant_reserva=0;
		}
	}
	else
		//perror ("Error al abrir %s",nombreDocumento);
		printf("Error al abrir %s \n",nombreDocumento);


	return rep;

}

key_t creo_clave()
{
	key_t clave;
	clave = ftok ("/bin/ls", 33);
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave de semáforo\n");
		exit(0);
	}
	return clave;
}

int creo_semaforo()
{
	key_t clave = creo_clave();
	int id_semaforo = semget(clave, 1, 0600|IPC_CREAT); 
	if(id_semaforo == -1)
	{
		printf("Error: no puedo crear semaforo\n");
		exit(0);
	}
	return id_semaforo;
}

void inicio_semaforo(int id_semaforo, int valor)
{
	semctl(id_semaforo, 0, SETVAL, valor);
}

void levanta_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Levanta SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = 1; 
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);
}

void espera_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Espera SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = -1; 
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);

}

int main()
{

	int id_semaforo;
	id_semaforo =  creo_semaforo();

	while(1)
	{
		espera_semaforo(id_semaforo);

		Reporte rep1 = analizar_documento_cajero("cajero1.dat"); 
		Reporte rep2 = analizar_documento_cajero("cajero2.dat"); 
		Reporte rep3 = analizar_documento_cajero("cajero3.dat"); 

		printf("datos de cajero1  cantChck %d totalCheck %d cantEfect %d totalEfect %d \n",rep1.cantCheck,rep1.totalCheck,rep1.cantEffect,rep1.totalEffect);
		printf("datos de cajero2  cantChck %d totalCheck %d cantEfect %d totalEfect %d \n",rep2.cantCheck,rep2.totalCheck,rep2.cantEffect,rep2.totalEffect);
		printf("datos de cajero3  cantChck %d totalCheck %d cantEfect %d totalEfect %d \n",rep3.cantCheck,rep3.totalCheck,rep3.cantEffect,rep3.totalEffect);

		int cantCheck = rep1.cantCheck +  rep2.cantCheck +  rep3.cantCheck;  
		int totalCheck = rep1.totalCheck +  rep2.totalCheck +  rep3.totalCheck;
		int cantEfect = rep1.cantEffect + rep2.cantEffect + rep3.cantEffect;    
		int totalEfect = rep1.totalEffect +  rep2.totalEffect +  rep3.totalEffect; 

		printf("total counted cantCheck %d totalCheck %d cantEfect %d totalEfect %d",cantCheck,totalCheck,cantEfect,totalEfect);


		printf("\nESPERAMOS\n");

		levanta_semaforo(id_semaforo);
		usleep(INTERVALO_PARTIDA*1000);
	};
	return 0;
}
