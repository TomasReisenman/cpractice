#include <stdio.h>

void swap(int* num1, int* num2){

int aux;

aux = *num1;

*num1=*num2;

*num2=aux;

}
int main(){

int num1 = 10, num2 =20;

swap(&num1,&num2);
printf("%d\n",num1);
printf("%d\n",num2);

return 0;
}

