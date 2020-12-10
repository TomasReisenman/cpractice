#include "Board.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


void setMessegeSize(char *message)
{
	char *temp = (char *) malloc(sizeof(char)*5);
	memset(temp,0,sizeof temp);

	if(strlen(message) < 5)
	{
		for(int i = 0; i < 5 - strlen(message) ; i++)  
		{
			strcat(temp,"0");	
		}
	}

	strcat(temp,message);	

	strcpy(message,temp);

}

void send_message(int Socket_Cliente,char* message)
{

	char *temp = (char *) malloc(sizeof(char)*2048);
	memset(temp,0,sizeof temp);

	sprintf(temp,"%d",strlen(message));
	setMessegeSize(temp);
	write (Socket_Cliente, temp, 5);
	write (Socket_Cliente,message,strlen(message));

}

char *get_message(int Socket)
{
	char *temp = (char *) malloc(sizeof(char)*2048);
	char *help = (char *) malloc(sizeof(char)*2048);
	memset(temp,0,sizeof temp);
	memset(help,0,sizeof help);

	read (Socket,temp,5);
	read (Socket,help, atoi(temp));

	return help;

}

void  addTarea(int num,char* descripcion, Columna *columna)
{
	Tarea *head_tarea = columna->head_tarea;
	Tarea  *new_node;
	new_node = (Tarea *) malloc(sizeof(Tarea));
	new_node->numero = num;
	new_node->descripcion = malloc(strlen(descripcion) + 1);
	strcpy(new_node->descripcion,descripcion);
	new_node->next= head_tarea;
	columna->head_tarea = new_node;
}

void  appendTarea(int num,char* descripcion, Columna *columna) {
	Tarea *head_tarea = columna->head_tarea;
	Tarea  *new_node;
	new_node = (Tarea *) malloc(sizeof(Tarea));
	new_node->numero = num;
	new_node->descripcion = malloc(strlen(descripcion) + 1);
	strcpy(new_node->descripcion,descripcion);

	Tarea *current_node = head_tarea;

	if(head_tarea == NULL)
	{
		columna->head_tarea = new_node;

	}else{

		while ( current_node->next != NULL) {
			current_node = current_node->next;
		}

		current_node->next = new_node;	
	}

}

char *printTarea(int rowNum,Columna *columna)
{
	int count = 0;
	int printed = 0;

	Tarea  *current_node = columna->head_tarea;
	char *result = (char *) malloc(sizeof(char)*100);

	while ( current_node != NULL && printed == 0) {
		if(count == rowNum)
		{
			sprintf(result,"| %d %s ", current_node->numero, current_node->descripcion);
			printed = 1;
		}
		current_node = current_node->next;
		count ++;
	}

	if(printed == 0)
	{
		sprintf(result,"|...");
	}

	return result;

}

Tarea *  removeTarea(int num, Columna *columna) {
	Tarea *current_node = columna->head_tarea;
	Tarea *prev_node;
	Tarea *removed = NULL;
	int cnt = 0;
	while ( current_node != NULL) {
		if (current_node->numero == num) {
			removed = current_node;
			if (current_node == columna->head_tarea) {
				columna->head_tarea = current_node->next;
			} else {
				prev_node->next = current_node->next;
			}
		} 
		//printf("found here %d \n",current_node->numero);
		prev_node = current_node;
		current_node = current_node->next;
	}
	return(removed);
}



Tarea * findTarea(int num, Columna *columna) {
	Tarea *current_node = columna->head_tarea;
	Tarea *found = NULL;
	while ( current_node != NULL) {
		if (current_node->numero == num) {
			found = current_node;
		} 
		current_node = current_node->next;
	}
	
	return(found);
}


Columna * addColumna(int num,char *nombre, Columna *head) {
	Columna *new_node;
	new_node = (Columna *) malloc(sizeof(Columna));
	new_node->numero = num;
	new_node->nombre = malloc(strlen(nombre) + 1);
	strcpy(new_node->nombre,nombre);
	new_node->next= head;
	head = new_node;
	return head;
}

Columna * appendColumna(int num,char *nombre, Columna *head) {
	Columna *new_node;
	new_node = (Columna *) malloc(sizeof(Columna));
	new_node->numero = num;
	new_node->nombre = malloc(strlen(nombre) + 1);
	strcpy(new_node->nombre,nombre);

	Columna *current_node = head;

	if(current_node == NULL)
	{
		head = new_node;	

	}else {

		while ( current_node->next != NULL) {
			current_node = current_node->next;
		}

		current_node->next = new_node;	

	}

	return head;
}
char * printColumna(Columna *head) {

	char *result = (char *) malloc(sizeof(char)*100);
	char *temp = (char *) malloc(sizeof(char)*100);
	Columna *current_node = head;
	while ( current_node != NULL) {
		sprintf(temp,"| %d %s ", current_node->numero, current_node->nombre);
		strcat(result,temp);
		current_node = current_node->next;
	}
	strcat(result,"\n");
	return result;

}

int countColumna(Columna *head) {
	int cnt = 0;
	Columna *current_node = head;
	while ( current_node != NULL) {
		cnt++;
		current_node = current_node->next;
	}
	return(cnt);
}

Columna * removeColumna(int num, Columna *head) {
	Columna *current_node = head;
	Columna *prev_node;
	int cnt = 0;
	while ( current_node != NULL) {
		if (current_node->numero == num) {
			if (current_node == head) {
				head = current_node->next;
			} else {
				prev_node->next = current_node->next;
			}
		} 
		prev_node = current_node;
		current_node = current_node->next;
	}
	return(head);
}

Columna * findColumna(int num, Columna *head) {
    Columna *current_node = head;
    Columna *found = NULL;
    int cnt = 0;
    while ( current_node != NULL) {
        if (current_node->numero == num) {
		found = current_node;
        } 
        current_node = current_node->next;
    }
return(found);
}

void moveTarea(Columna *from,Columna *to,int numero)
{

	Tarea *found = removeTarea(numero,from);

	if(found != NULL)
	{
		appendTarea(found->numero,found->descripcion,to);

	}


}

void editTarea(Tarea *tarea,char *nueva_descripcion)
{

	strcpy(tarea->descripcion,nueva_descripcion);

}
//int  showMenu()
//{
//    Columna *head = NULL;
//    int num;
//    int option;
//    char * temp;
//
//    while(1) {
//
//        printf("\n ******************************************\n");
//        printf("\n *  Linked list operations:               *\n");
//        printf("\n *    1. Add                              *\n");
//        printf("\n *    2. Remove                           *\n");
//        printf("\n *    3. Count                            *\n");
//        printf("\n *    4. Print                            *\n");    
//        printf("\n *    5. Quit                             *\n");    
//        printf("\n ******************************************\n");
//        printf("\n Choose an option [1-5] : ");
//        if (scanf("%d", &option) != 1) {
//            printf(" *Error: Invalid input. Press try again.\n");
//            scanf("%s", &temp); /*this will clear the input buffer */
//            continue;
//        }
//
//        switch (option) {
//            case 1:        /* Add */
//                printf(" Enter a number to add : ");
//                if (scanf("%d", &num) != 1) {
//                    printf(" *Error: Invalid input. Only integer numbers are allowed\n");
//                    scanf("%s", &temp);    /*this will clear the input buffer */
//                    continue;
//                }
//                head = addColumna(num, head);
//                printf("Number %d is now added to the list", num);
//                printf("\nPress any key to continue...");
//                //getch();
//                break;
//
//            case 2:    /* Remove */
//                printf(" Enter a number to remove : ");
//                if (scanf("%d", &num) != 1) {
//                    printf(" *Error: Invalid input. Only integer numbers are allowed\n");
//                    scanf("%s", &temp);    /*this will clear the input buffer */
//                    continue;
//                }
//                head = removeColumna(num, head);
//                printf("Number %d is now removed from the list", num);
//                printf("\nPress any key to continue...");
//                //getch();
//                break;
//
//            case 3:    /* Count */
//                printf("\nYour linked list contains %d nodes", countColumna(head));
//                printf("\nPress any key to continue...");
//                break;
//
//            case 4: /* Print */
//                printf("\nYour linked list contains the following values: \n [ ");
//                printColumna(head);
//                printf("]\n\nPress any key to continue...");
//                break;
//
//            case 5:    /* Exit */
//                return(0);
//                break;
//
//            default:
//                printf("Invalid Option. Please Try again.");
//                //getch();
//
//            } 
//    } 
//
//}

char *shortenString(char *word,int num)
{
	char *result = (char *) malloc(sizeof(char)*100);

	if(strlen(word) > num)
	{
		strncpy(result,word,num);
		strcat(result,"..");	
	}

	if(strlen(word) < num)
	{
		strcpy(result,word);

		for(int i = 0; i < 2 + num - strlen(word) ; i++)  
		{
			strcat(result," ");	
		}
	}

	if(strlen(word) ==  num)
	{
		strcpy(result,word);

	}

	return result;
}

