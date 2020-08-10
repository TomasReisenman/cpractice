#include <stdio.h>

int main(){


int number[10];


number[0]= 10;
number[1]= 20;
number[2]= 30;
number[3]= 40;
number[4]= 50;
number[5]= 60;
number[6]= 70;

int  total = 0;
for(int i =0;i<7;i++){

printf("%d\n",i);
printf("%d\n",total);
total= total + number[i];

}

printf("%d\n",total);
return 0;
}

