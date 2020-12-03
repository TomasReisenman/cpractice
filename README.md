# cpractice
c Practice from colleage Lab 3

Resume for test :joy:

## Running the gcc

```shell

gcc ejemplo_thread_mutex.c -o threads -pthread

```
## Makefile

```Makefile

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

```
## Shared Memory 

```c
key_t creo_clave(int r_clave)
{
	key_t clave;
	clave = ftok ("/bin/ls", r_clave);	
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave para memoria compartida\n");
		exit(0);
	}
	return clave;
}


int creo_id_memoria(int size, int clave)
{
	int id_memoria;

	id_memoria = shmget (creo_clave(clave), size, 0777 | IPC_CREAT);//crea memoria x 50 byte, 

	if (id_memoria == -1)
	{

		printf("No consigo id para memoria compartida\n");

		exit (0);

	}

	return id_memoria;
}

void* creo_memoria(int id_memoria)
{
	void* ptr_memoria;

	ptr_memoria = (void *)shmat (id_memoria, (char *)0, 0);

	if (ptr_memoria == NULL)
	{
		printf("No consigo memoria compartida\n");

		exit (0);
	}
	return ptr_memoria;
}


``` 

## Semaphore

```c 
int creo_semaforo(int cuantos)
{
  key_t clave = creo_clave(CLAVE_BASE);
  int id_semaforo = semget(clave,cuantos,0600|IPC_CREAT); 
  if(id_semaforo == -1)
  {
      printf("Error: no puedo crear semaforo\n");
      exit(0);
  }
  return id_semaforo;
}

void inicio_semaforo(int id_semaforo, int cual,int valor)
{
	semctl(id_semaforo,cual,SETVAL,valor);
}

void levanta_semaforo(int id_semaforo,int cual)
{
	struct sembuf operacion;
	operacion.sem_num = cual;
	operacion.sem_op = 1; //incrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);
}

void espera_semaforo(int id_semaforo,int cual)
{
	struct sembuf operacion;
	operacion.sem_num = cual;
	operacion.sem_op = -1; //decrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);

}

```

##  Message Queue

```c
int creo_id_cola_mensajes(int clave)
{
	int id_cola_mensajes = msgget (creo_clave(clave), 0600 | IPC_CREAT);
	if (id_cola_mensajes == -1)
	{
		printf("Error al obtener identificador para cola mensajes\n");
		exit (-1);
	}
	return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg)
{
	mensaje msg;
	msg.long_dest 	= rLongDest;
	msg.int_rte    	= rIntRte;
	msg.int_evento 	= rIntEvento;
	strcpy(msg.char_mensaje, rpCharMsg);
	return msgsnd (id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), IPC_NOWAIT);
}		

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg)
{
	mensaje msg;
	int res;
	res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg,  sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), 	rLongDest, 0);
	
	rMsg->long_dest 	    = msg.long_dest;
	rMsg->int_rte    	= msg.int_rte;
	rMsg->int_evento 	= msg.int_evento;
	strcpy(rMsg->char_mensaje, msg.char_mensaje);
	return res;
}

int borrar_mensajes(int id_cola_mensajes)
{
	mensaje msg;
	int res;
	do
	{
		res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg,  sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), 	0, IPC_NOWAIT);
	}while(res>0);
	return res;
}


```

## Info on Shared resources 

```shell
ipcs -q #For queues
ipcs -m #For shared memory
ipcs -s #For semaphores

ipcrm -s #For removing ipc resources

```

## Threads 

```c

//Creating threads 
pthread_t* idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_jugadores);
pthread_attr_t 	atributos;
pthread_attr_init (&atributos);
pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

// Then ThreadJugador uses void* as parameter
pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_jugador[i]);

// At the end of ThreadJugador method
pthread_exit ((void *)"Listo");

//Mutex 
pthread_mutex_t mutex;

pthread_mutex_init (&mutex, NULL);

pthread_mutex_lock (&mutex);
pthread_mutex_unlock (&mutex);

// Wait for thread to end
*pthread_join (idHilo[j], NULL);



```

## Socket Server

```c

/*
 *	Abre socket servidor UNIX. Se le pasa el servicio que se desea atender y
 * que debe estar dado de alta en /etc/services. Deja el socket preparado
 * para aceptar conexiones de clientes.
 * Devuelve el descritor del socket servidor, que se debera pasar
 * a la funcion Acepta_Conexion_Cliente(). Devuelve -1 en caso de error
 */
int Abre_Socket_Unix (char *Servicio)
{
	struct sockaddr_un Direccion;
	int Descriptor;

	/*
	 * Se abre el socket
	 */
	Descriptor = socket (AF_UNIX, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;

	/*
	 * Se rellenan en la estructura Direccion los datos necesarios para
	 * poder llamar a la funcion bind()
	 */
	strcpy (Direccion.sun_path, Servicio);
	Direccion.sun_family = AF_UNIX;

	if (bind (
				Descriptor, 
				(struct sockaddr *)&Direccion, 
				strlen (Direccion.sun_path) + sizeof (Direccion.sun_family)) == -1)
	{
		/*
		 * En caso de error cerramos el socket y devolvemos error
		 */
		close (Descriptor);
		return -1;
	}

	/*
	 * Avisamos al sistema que comience a atender peticiones de clientes.
	 */
	if (listen (Descriptor, 1) == -1)
	{
		close (Descriptor);
		return -1;
	}

	/*
	 * Se devuelve el descriptor del socket servidor
	 */
	return Descriptor;
}

/*
 * Se le pasa un socket de servidor y acepta en el una conexion de cliente.
 * devuelve el descriptor del socket del cliente o -1 si hay problemas.
 * Esta funcion vale para socket AF_INET o AF_UNIX.
 */
int Acepta_Conexion_Cliente (int Descriptor)
{
	socklen_t Longitud_Cliente;
	struct sockaddr Cliente;
	int Hijo;

	/*
	 * La llamada a la funcion accept requiere que el parametro 
	 * Longitud_Cliente contenga inicialmente el tamano de la
	 * estructura Cliente que se le pase. A la vuelta de la
	 * funcion, esta variable contiene la longitud de la informacion
	 * util devuelta en Cliente
	 */
	Longitud_Cliente = sizeof (Cliente);
	Hijo = accept (Descriptor, &Cliente, &Longitud_Cliente);
	if (Hijo == -1)
		return -1;

	/*
	 * Se devuelve el descriptor en el que esta "enchufado" el cliente.
	 */
	return Hijo;
}

/*
 * Abre un socket servidor de tipo AF_INET. Devuelve el descriptor
 *	del socket o -1 si hay probleamas
 * Se pasa como parametro el nombre del servicio. Debe estar dado
 * de alta en el fichero /etc/services
 */
int Abre_Socket_Inet (char *Servicio)
{
	struct sockaddr_in Direccion;
	struct sockaddr Cliente;
	socklen_t Longitud_Cliente;
	struct servent *Puerto;
	int Descriptor;

	/*
	 * se abre el socket
	 */
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;

	/*
	 * Se obtiene el servicio del fichero /etc/services
	 */
	Puerto = getservbyname (Servicio, "tcp");
	if (Puerto == NULL)
		return -1;

	/*
	 * Se rellenan los campos de la estructura Direccion, necesaria
	 * para la llamada a la funcion bind()
	 */
	Direccion.sin_family = AF_INET;
	Direccion.sin_port = Puerto->s_port;
	Direccion.sin_addr.s_addr =INADDR_ANY;
	if (bind (
				Descriptor, 
				(struct sockaddr *)&Direccion, 
				sizeof (Direccion)) == -1)
	{
		close (Descriptor);
		return -1;
	}

	/*
	 * Se avisa al sistema que comience a atender llamadas de clientes
	 */
	if (listen (Descriptor, 1) == -1)
	{
		close (Descriptor);
		return -1;
	}

	/*
	 * Se devuelve el descriptor del socket servidor
	 */
	return Descriptor;
}

``` 
## Socket Cliente

```c

/*
* Conecta con un servidor Unix, en la misma maquina.
*	Devuelve descriptor de socket si todo es correcto, -1 si hay error.
*/
int Abre_Conexion_Unix (char *Servicio)
{
	struct sockaddr_un Direccion;
	int Descriptor;

	strcpy (Direccion.sun_path, Servicio);
	Direccion.sun_family = AF_UNIX;

	Descriptor = socket (AF_UNIX, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;

	/*
	* Devuelve 0 si todo va bien, -1 en caso de error
	*/
	if (connect (
			Descriptor, 
			(struct sockaddr *)&Direccion, 
			strlen (Direccion.sun_path) + sizeof (Direccion.sun_family)) == -1)
	{
		return -1;
	}
	else
	{
		return Descriptor;
	}
}

/*
/ Conecta con un servidor remoto a traves de socket INET
*/
int Abre_Conexion_Inet (
	char *Host_Servidor, 
	char *Servicio)
{
	struct sockaddr_in Direccion;
	struct servent *Puerto;
	struct hostent *Host;
	int Descriptor;

	Puerto = getservbyname (Servicio, "tcp");
	if (Puerto == NULL)
		return -1;

	Host = gethostbyname (Host_Servidor);
	if (Host == NULL)
		return -1;

	Direccion.sin_family = AF_INET;
	Direccion.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr;
	Direccion.sin_port = Puerto->s_port;
	
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;

	if (connect (
			Descriptor, 
			(struct sockaddr *)&Direccion, 
			sizeof (Direccion)) == -1)
	{
		return -1;
	}

	return Descriptor;
}

```

## Read and get messages from Sockets

```c

/*
* Lee datos del socket. Supone que se le pasa un buffer con hueco 
*	suficiente para los datos. Devuelve el numero de bytes leidos o
* 0 si se cierra fichero o -1 si hay error.
*/
int Lee_Socket (int fd, char *Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;

	/*
	* Comprobacion de que los parametros de entrada son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1)){
	printf(" here fd %d \n",fd); 
	printf(" here Datos %s \n",Datos); 
	printf(" here Long %d\n",Longitud); 
		return -1;}

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{
			/* 
			* Si hemos conseguido leer datos, incrementamos la variable
			* que contiene los datos leidos hasta el momento
			*/
			Leido = Leido + Aux;
		}
		else
		{
			/*
			* Si read devuelve 0, es que se ha cerrado el socket. Devolvemos
			* los caracteres leidos hasta ese momento
			*/
			if (Aux == 0) 
				return Leido;
			if (Aux == -1)
			{
				/*
				* En caso de error, la variable errno nos indica el tipo
				* de error. 
				* El error EINTR se produce si ha habido alguna
				* interrupcion del sistema antes de leer ningun dato. No
				* es un error realmente.
				* El error EGAIN significa que el socket no esta disponible
				* de momento, que lo intentemos dentro de un rato.
				* Ambos errores se tratan con una espera de 100 microsegundos
				* y se vuelve a intentar.
				* El resto de los posibles errores provocan que salgamos de 
				* la funcion con error.
				*/
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	/*
	* Se devuelve el total de los caracteres leidos
	*/
	return Leido;
}

/*
* Escribe dato en el socket cliente. Devuelve numero de bytes escritos,
* o -1 si hay error.
*/
int Escribe_Socket (int fd, char *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	/*
	* Comprobacion de los parametros de entrada
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Bucle hasta que hayamos escrito todos los caracteres que nos han
	* indicado.
	*/
	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
}





```
