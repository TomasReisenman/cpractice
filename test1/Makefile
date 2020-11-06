CC 		= g++ 

all : bolera jugadores

jugadores : jugadores.c funciones.h definiciones.h funciones.o
	cc -o jugadores jugadores.c funciones.o -pthread

bolera : bolera.c funciones.h definiciones.h funciones.o
	cc -o bolera bolera.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o bolera jugadores *~
