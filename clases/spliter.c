#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** separar(char *mensaje, char *caracter){
   
    int count = 0; 

    //creo este temp para poder primero contar la cantidad de iteraciones
    char *temp=malloc(strlen(mensaje));
    char *token;
    token = NULL;
    sprintf(temp,"%s\n",mensaje);
    token = strtok(temp, caracter);
 
    //Cuento las iteraciones (asi se el tamaño del array que necesito)
    while (token != NULL)
    {
        token = strtok(NULL,caracter);
        count++;
    }
    //una vez que tengo el tamaño del array creo el array con un maloc
    char** array=(char**)malloc(sizeof(char*)*count);

    //empiezo a iterar por el texto
    count = 0;
    token = strtok(mensaje, caracter);
    while (token != NULL)
    {
        //le asigno su tamaño
        array[count]= (char*)malloc(sizeof(char)*strlen(token));
        //le paso al vector el dato 
        sprintf(array[count],"%s\n", token);
        //printf("pasando a %d: %s\n",count,array[count]);
        token = strtok(NULL,caracter);
        count++;
    }
    
  
return array;
}

int main(int argc, char *argv[])
{

char test[100];
//Hago estoy porque no le gusta al strtok si mando de una el string.
sprintf(test,"Esto:es:test");

//No le encontre la vuelta mas que usando un char ** (otra que pense fue en crear una estructura asi de paso me queda el largo del array)
    char **array  = separar(test,":");

    int i;
    for(i=0;i<3;i++){
     printf("dato %d: %s\n",i,array[i]);
    }
}

