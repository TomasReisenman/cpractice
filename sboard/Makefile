all : Socket.o Socket_Servidor.o Socket_Cliente.o Board.o Servidor Cliente

CPPFLAGS = -g -I.

Servidor : Servidor.c
	cc -g -I. Socket.o Socket_Servidor.o Board.o  Servidor.c -o Servidor -pthread

Cliente : Cliente.c
	cc -g -I. Socket.o Socket_Cliente.o Cliente.c Board.o -o Cliente

clean :
	rm *.o Cliente Servidor
