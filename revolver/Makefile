CC 		= g++ 

all : revolver jugadores

jugadores : jugadores.c funciones.h definiciones.h funciones.o
	cc -o jugadores jugadores.c funciones.o -pthread

revolver : revolver.c funciones.h definiciones.h funciones.o
	cc -o revolver revolver.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o revolver jugadores *~
