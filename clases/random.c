#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CANTIDAD 10
#define DESDE 1
#define HASTA 20

int* generarRandom(int desde, int hasta, int cantidad){
	
	if((hasta-desde)< cantidad){		
			printf("deben haber mas numeros que cantidades, %d es menor que %d\n",(hasta-desde),cantidad);
		    exit (0);
		    
		    }
    int n,num,i,j,hastaRand;
    int* vector= (int*)malloc(cantidad*sizeof(int));

	hastaRand=(hasta-desde)/cantidad ;
   
	srand(time(NULL));
	int temp=desde;
	
	for (n=0; n<cantidad;n++)
	{	
		num = (rand()%(hastaRand))+1;
		vector[n]=temp+num;
	//	printf("el numero es %d: %d =%d \n", vector[n],hastaRand,num);	
     	temp=temp+hastaRand;
	}

//printf("Reordeno---------\n");	
   for (i= cantidad-1; i>0;i--)
	{
	 num=rand()%(i);
	 j= vector[i];
	 vector[i]=vector[num];
	 vector[num]=j;
	}

return vector;

	}




int main(int argc, char *argv[])
{	
	//cargo valores por defecto en caso de no pasarle por parametros
	int desde = DESDE;
	int hasta = HASTA;
	int cantidad=CANTIDAD;
	int n;
	
	if (argc > 3){
	desde = atoi(argv[1]);
	hasta = atoi(argv[2]);
    	cantidad = atoi(argv[3]);	
	}

    //Llamo a la funcion que me trae los numeros radom
    int* vector= generarRandom(desde,hasta,cantidad);
	
	
	for (n=0; n<cantidad;n++)
	{	
		printf("%d \n", vector[n]);	
	}


	return 0;
}
