/*Molina Alejandro*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CANT_FILAS 4
#define CANT_COLUMNAS 2
#define CANT 5


//unsigned char 	8  0 <= X <= 255            			Numeros pequenios y juego caracteres del PC.
//char (signed)  	8  -128 <= X <= 127       				Numeros muy pequenios y juego de caracteres ASCII
//short (signed) 	16 -32,768 <= X <= 32,767  				Numeros muy pequenios, control de bucles pequenios
//unsigned short 	16 0 <= X <= 65,535      				Numeros muy pequenios, control de bucles pequenios
//unsigned (int) 	32 0 <= X <= 4,294,967,295.         	Numeros grandes
//int  (signed) 	32 -2,147,483,648 <= X <= 2,147,483,647 Numeros pequenios, control de bucles
//unsigned long 	32 0 <= X <= 4,294,967,295          	Distancias astronómicas
//enum 				32 -2,147,483,648 <= X <= 2,147,483,647 Conjuntos de valores ordenados
//long (int) 		32 -2,147,483,648 <= X <= 2,147,483,647 Numeros grandes
//float 			32 1.18e-38 <= |X| <= 3.40e38           Precision cientifica ( 7-digitos)
//double 			64 2.23e-308 <= |X| <= 1.79e308      	Precision cientifica (15-digitos)
//long double 		80 3.37e-4932 <= |X| <= 1.18e4932    	Precision cientifica (18-digitos)


int main(int argc, char* argv[])
{

	int i, j, c=0;

	int* ptr_int; //puntero a un entero.

	char* ptr_char; //puntero a un char.

	int* ptr_int_aux; //puntero a un entero.

	char* ptr_char_aux; //puntero a un entero..

	int** matriz_entera; //puntero a una matriz entera.

	//Toda variable estatica que definamos tiene 4 propiedades basicas.
	// Un nombre, es el que le dimos al definirla y de esta forma podemos acceder a lo que tiene almacenado.
	// Un tipo, define el tipo de dato, puede ser primitivo (entero, char, etc) o abstracto (estructuras).
	// Una direccion, es la direccion inicial donde esta almacenada esa variable.
	// Un largo, dependiendo el tipo de datos cada variable va ocupar n bytes en memoria.

	// Un puntero como toda variable tiene estas 4 propiedades. Es una variable que guarda una direccion de memoria.
	// Por ejemplo ptr_int tiene un nombre (ptr_int), un tipo de dato (int*), 
	// Una direccion (espacio de memoria en donde puede almacenar una direccion de memoria).
	// Un largo (un puntero para poder almacenar una direccion necesita de 4bytes).
	  

	//malloc reserva un espacio de memoria en este caso de 5 enteros y devuelve la direccion de inicio de este. Esto lo hace
	//en tiempo de ejecucion es decir en forma dinamica. Como la direccion es del tipo void* 
	//es necesario realizar un cast (int*) para poder guardar esta direccion en una variable del tipo int*

	ptr_int = (int*) malloc(sizeof(int)*CANT);   //ptr_int tiene la direccion de inicio del espacion reservado por malloc.

	//Veamos que la direccion de la variable ptr_int no es la misma que la direccion que tiene almacenada ptr_int.
	//Porque un puntero es una variable que almacena una direccion, pero como es una variable tiene su propia direccion.
	printf("direccion de ptr_int 0x%X\n", &ptr_int);
	printf("direccion que tiene almacenda ptr_int 0x%X\n", ptr_int);

	//Un entero ocupa 4bytes--> -2.147.483.648 <= X <= 2.147.483.647
	//2^33 = 2.147.483.647, uno lo usa para el signo (- o +)
	printf("Largo de un entero %d bytes\n", sizeof(int)); //esto nos demuestra que un entero tiene 4bytes.

	//utilizando aritmetica de punteros es posible acceder a este espacio de memoria, separandolos de a 4bytes (largo de un entero).
	// Lo que estamos haciendo en realidad es acceder a las direcciones sumandole 4bytes a la inicial.

	*(ptr_int+0)=0; 
	*(ptr_int+1)=1; //cuando sumamos 1 lo que hace en realidad es sumar un entero (4 bytes) a la direccion.
	*(ptr_int+2)=2;
	*(ptr_int+3)=3;
	*(ptr_int+4)=4;

	//ahora para demostrar como podemos accedar a cada direccion guardamos la direccion inicial en una variable auxiliar
	ptr_int_aux = ptr_int; 

	printf("Accediendo con un puntero auxiliar\n");
	for(i=0; i<CANT; i++)
	{
		printf("[0x%X]:%d\n", ptr_int_aux, *ptr_int_aux); //ptr_int_aux va tamando la direccion de a 4bytes, pero en cada paso pierde la anterior.
		ptr_int_aux++;
	}

	printf("Con aritmetica de punteros\n");
	for(i=0; i<CANT; i++)
	{
		printf("[0x%X]:%d\n", ptr_int+i, *(ptr_int+i)); //En este caso le estamos sumando 4bytes * i a la direccion inicial.
	}

	printf("Como si fuera un vector\n");
	for(i=0; i<CANT; i++)
	{
		printf("[0x%X]:%d\n", &ptr_int[i], ptr_int[i] ); //Aqui lo mismo utilizando indices (internamente el compilador utiliza aritmetica de punteros.)
	}

	//Aqui vemos algo similar con un char. (punteros a char)

	ptr_char = (char *) malloc(sizeof(char)*CANT);

	//Recordemos que a pesar de que el tipo de datos es un char en realidad se guarda en memoria como una serie de bits que obviamente
	//forman un byte. Un char ocupa un byte. Por este es posible cargar el valor como un caracter o un numero (en decimal, hexa, etc).

	*(ptr_char+0)='0'; 
	*(ptr_char+1)=0x31;
	*(ptr_char+2)='2';
	*(ptr_char+3)=51;
	*(ptr_char+4)='4';

	printf("\n");

	//Un char ocupa 1byte--> -128 <= X <= 127  Numeros muy pequenios y juego de caracteres ASCII
	printf("Largo de un char %d byte\n", sizeof(char)); //esto nos demuestra que un char tiene 1byte.

	//Notar que el largo del puntero char* es 4bytes, porque para grabar una direccion necesita 4 bytes, 
	//el tipo de dato char*, int* solo sirve para que el compilador sepa el tipo de dato que tiene lo que esta almacenado
	//en la direccion que apunta el puntero.
	printf("Largo de un char* (ptr) %d byte\n", sizeof(char*)); 


	ptr_char_aux = ptr_char;
	for(i=0; i<CANT; i++)
	{
		printf("[0x%X]:0x%X %c\n", ptr_char_aux, *ptr_char_aux, *ptr_char_aux); //imprimo las direcciones. Notar que estan a 1byte una de otras.
		ptr_char_aux++;
	}

	ptr_int_aux = (int*) ptr_char; //Veamos que sucede cuando utilizamos la direccion (char*) pero con un puntero (int *)

	printf("\nUtilizando un puntero int* \n");
	//00110000 00110001 00110010 0011001 ¿Que pasa aca?
	printf("[0x%X]:0x%X\n", ptr_int_aux, *ptr_int_aux);  //Para debatir en clase.

	//Veamos que pasa con una matriz.

	printf("\nMatriz de %dx%d\n", CANT_FILAS, CANT_COLUMNAS);

	matriz_entera =  (int **) malloc(sizeof(int*)*CANT_FILAS); //Veamos que aqui es sizeof(int*) ¿Por que? para debatir.

	for(i=0; i<CANT_FILAS; i++)
		matriz_entera[i]= (int *) malloc(sizeof(int)*CANT_COLUMNAS);


	ptr_int_aux = *matriz_entera; //Utilicemos un puntero int*

	c=0;
	for(i=0; i<CANT_FILAS; i++)
	for(j=0; j<CANT_COLUMNAS; j++)
	   matriz_entera[i][j]=c++;

	for(i=0; i<CANT_FILAS; i++)
	{
		for(j=0; j<CANT_COLUMNAS; j++)
		{
			printf("[0x%X] %02d ", ptr_int_aux++, matriz_entera[i][j]); //Veamos como las posiciones de una matriz son contiguas todas como si fuera un vector.
		}
		printf("\n");
	}
	
	//getch();
	return 0;
}
