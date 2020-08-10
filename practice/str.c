#include <stdio.h>
#include <string.h>

int main(){



char name[] = "John Smith";
int age = 27;

printf("%s is %d years old. \n",name,age);
printf(" name is %d charactes long\n",strlen(name));


if(strncmp(name,"John",4)==0){

	printf("Hello,John\n");

}else {
	printf("You are not John....\n");
}

char dec[]= "HI";
char sec[]= "Martin";

strncat(dec,sec,10);

printf("%s\n",dec);

return 0;
}

