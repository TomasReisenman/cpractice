CC 		= g++ 

all : banco cajero_automatico

cajero_automatico : cajero_automatico.c funciones.h definiciones.h funciones.o
	cc -o cajero_automatico cajero_automatico.c funciones.o -pthread

banco : banco.c funciones.h definiciones.h funciones.o
	cc -o banco banco.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:
	rm -rf *o banco cajero_automatico *~
