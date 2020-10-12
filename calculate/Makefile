CC 		= g++ 

all : solicitante calculador

calculador : calculador.c funciones.h definiciones.h funciones.o
	cc -o calculador calculador.c funciones.o

solicitante : solicitante.c funciones.h definiciones.h funciones.o
	cc -o solicitante solicitante.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o calculador solicitante
