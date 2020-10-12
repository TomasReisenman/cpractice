#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H
 
#define LARGO_DESCRIPCION 100
#define CANT_SEMAFORO 1
#define DESDE_CODIGO 1
#define HASTA_CODIGO 4
#define CANTIDAD_TOTAL (HASTA_CODIGO-DESDE_CODIGO+1)
#define DESDE_CANTIDAD 1
#define HASTA_CANTIDAD 10 

typedef struct tipo_codigos codigos;
struct tipo_codigos
{
	int codigo;
   	char descripcion[LARGO_DESCRIPCION];
};

typedef struct tipo_stock stock;
struct tipo_stock
{
	int codigo;
	int cantidad;
};


typedef enum
{
	MSG_NADIE,				
	MSG_SOLICITANTE,
	MSG_CALCULADOR,
	MSG_CLIENTE	
}Destinos;

typedef enum
{
	EVT_NINGUNO,
	EVT_SUMA, //Consulta el stock, lleva como parametro el codigo
	EVT_PRODUCTO,
	EVT_RESULTADO,
}Eventos;


#endif
