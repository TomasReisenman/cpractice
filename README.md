# cpractice
c Practice from colleage Lab 3

Resume for test :joy:

## Shared Memomory 

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
