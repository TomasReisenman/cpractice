int menu(void)
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tConsula\n");
    printf("2.\tDeposito\n");
    printf("3.\tExtraccion\n");
    printf("0.\tSalir\n\n");
    printf("Elija opcion: ");

    while( (scanf(" %d", &opcion) != 1)
          || (opcion < 0)            
          || (opcion > MAX_MENU))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Elija opcion: ");
    }
    return opcion;
}
