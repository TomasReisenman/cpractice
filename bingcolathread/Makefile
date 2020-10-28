CC 		= g++ 

all : bingo jugadores

jugadores : jugadores.c funciones.h definiciones.h funciones.o
	cc -o jugadores jugadores.c funciones.o -pthread

bingo : bingo.c funciones.h definiciones.h funciones.o
	cc -o bingo bingo.c funciones.o -pthread

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o bingo jugadores *~
