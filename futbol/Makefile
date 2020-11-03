CC 		= g++ 

all : arquero pateadores

pateadores : pateadores.c funciones.h definiciones.h funciones.o
	cc -o pateadores pateadores.c funciones.o -pthread

arquero : arquero.c funciones.h definiciones.h funciones.o
	cc -o arquero arquero.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o arquero pateadores *~
