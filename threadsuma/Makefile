CC 		= g++ 

all : thread_suma ejemplo_thread_mutex

ejemplo_thread_mutex : ejemplo_thread_mutex.c funciones.h definiciones.h funciones.o
	cc -o ejemplo_thread_mutex ejemplo_thread_mutex.c funciones.o -pthread

thread_suma : thread_suma.c funciones.h definiciones.h funciones.o
	cc -o thread_suma thread_suma.c funciones.o -pthread

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o ejemplo_thread_mutex thread_suma
