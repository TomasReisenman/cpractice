#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_tarea Tarea;
struct node_tarea {
	int data;
	struct node_tarea *next;
	char *descripcion;
} ;

typedef struct node_columna Columna;
struct node_columna {
	int data;
	struct node_columna *next;
	Tarea *head_tarea;
	char *nombre;

} ;


//Columna * add(int, Columna *);
//Columna * remove(int, Columna *);
//void print(Columna *);
//int count(Columna *);

void  addTarea(int num,char* descripcion, Columna *columna) {
	Tarea *head_tarea = columna->head_tarea;
	Tarea  *new_node;
	new_node = (Tarea *) malloc(sizeof(Tarea));
	new_node->data = num;
	new_node->descripcion = malloc(strlen(descripcion) + 1);
	strcpy(new_node->descripcion,descripcion);
	new_node->next= head_tarea;
	columna->head_tarea = new_node;
	//return head;
}

void  appendTarea(int num,char* descripcion, Columna *columna) {
	Tarea *head_tarea = columna->head_tarea;
	Tarea  *new_node;
	new_node = (Tarea *) malloc(sizeof(Tarea));
	new_node->data = num;
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

	//new_node->next= head_tarea;
	//columna->head_tarea = new_node;
}

void printTarea(int rowNum,Columna *columna)
{
	int count = 0;
	int printed = 0;

	Tarea  *current_node = columna->head_tarea;
	while ( current_node != NULL && printed == 0) {
		if(count == rowNum)
		{
			printf("numero:%d descripcion:%s", current_node->data, current_node->descripcion);
			printed = 1;
		}
		current_node = current_node->next;
		count ++;
	}

	if(printed == 0)
	{
		printf(".....");
	}

}

Tarea *  removeTarea(int num, Columna *columna) {
	Tarea *current_node = columna->head_tarea;
	Tarea *prev_node;
	Tarea *removed = NULL;
	int cnt = 0;
	while ( current_node != NULL) {
		if (current_node->data == num) {
			removed = current_node;
			if (current_node == columna->head_tarea) {
				columna->head_tarea = current_node->next;
			} else {
				prev_node->next = current_node->next;
			}
		} 
		//printf("found here %d \n",current_node->data);
		prev_node = current_node;
		current_node = current_node->next;
	}
	return(removed);
}



Tarea * findTarea(int num, Columna *columna) {
	Tarea *current_node = columna->head_tarea;
	Tarea *found = NULL;
	while ( current_node != NULL) {
		if (current_node->data == num) {
			found = current_node;
		} 
		current_node = current_node->next;
	}
	
	return(found);
}


Columna * addColumna(int num,char *nombre, Columna *head) {
	Columna *new_node;
	new_node = (Columna *) malloc(sizeof(Columna));
	new_node->data = num;
	new_node->nombre = malloc(strlen(nombre) + 1);
	strcpy(new_node->nombre,nombre);
	new_node->next= head;
	head = new_node;
	return head;
}

Columna * appendColumna(int num,char *nombre, Columna *head) {
	Columna *new_node;
	new_node = (Columna *) malloc(sizeof(Columna));
	new_node->data = num;
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
void printColumna(Columna *head) {

    Columna *current_node = head;
   	while ( current_node != NULL) {
        printf("numero:%d nombre:%s \n", current_node->data, current_node->nombre);
        current_node = current_node->next;
    }
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
        if (current_node->data == num) {
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
        if (current_node->data == num) {
		found = current_node;
        } 
        current_node = current_node->next;
    }
return(found);
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

int main()
{

	//showMenu();

    	Columna *head = NULL;
	head = appendColumna(1,"Para hacer",head);
	head = appendColumna(2,"Hecho",head);
	printColumna(head);

	addTarea(2,"list",head);	
	addTarea(3,"list",head);	


	
	Tarea *lost = removeTarea(3,head);
	printf(" %d \n",lost->data);
	addTarea(10,"esto",head);	
	printTarea(0,head);
	printTarea(1,head);
	printTarea(2,head);
	printTarea(3,head);

	printf("\n-----\n");

    	Columna *head2 = NULL;
	head2 = addColumna(11,"Done",head2);
	printColumna(head2);

	addTarea(1,"esto",head2);
	addTarea(5,"esto",head2);
	addTarea(20,"esto",head2);
	printTarea(0,head2);
	printTarea(1,head2);
	printTarea(2,head2);
	printTarea(3,head2);

	printf("\n //////////////////  \n");
	Columna	*foundC = findColumna(2,head);
	Tarea	*foundT = findTarea(2,head);
	
	printf("Found %d \n",foundC->data);
	printf("Found %d \n",foundT->data);

	printf("\n //////////////////  \n");

	appendTarea(2,"chchchch",foundC);	
	appendTarea(3,"ddddddd",foundC);	
	
	printTarea(0,foundC);
	printTarea(1,foundC);
	

return(0);
}
