#ifndef _BOARD_H
#define _BOARD_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Socket.h"


typedef struct node_tarea Tarea;
struct node_tarea {
	int numero;
	struct node_tarea *next;
	char *descripcion;
} ;

typedef struct node_columna Columna;
struct node_columna {
	int numero;
	struct node_columna *next;
	Tarea *head_tarea;
	char *nombre;

} ;

void  addTarea(int num,char* descripcion, Columna *columna);  
void  appendTarea(int num,char* descripcion, Columna *columna);  
char *printTarea(int rowNum,Columna *columna);
Tarea * removeTarea(int num, Columna *columna);  
Tarea * findTarea(int num, Columna *columna);
Columna * addColumna(int num,char *nombre, Columna *head);
Columna * appendColumna(int num,char *nombre, Columna *head);
char * printColumna(Columna *head);
int countColumna(Columna *head);
Columna * removeColumna(int num, Columna *head);
Columna * findColumna(int num, Columna *head);
void moveTarea(Columna *from,Columna *to,int numer);
void editTarea(Tarea *tarea,char *nueva_descripcion);
char* shortenString(char *word,int num);
char *get_message(int Socket);
void send_message(int Socket_Cliente,char* message);

#endif
