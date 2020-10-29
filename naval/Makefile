CC 		= g++ 

all : barcos jugadores

jugadores : jugadores.c funciones.h definiciones.h funciones.o
	cc -o jugadores jugadores.c funciones.o -pthread

barcos : barcos.c funciones.h definiciones.h funciones.o
	cc -o barcos barcos.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o barcos jugadores *~
