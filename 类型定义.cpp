#include <stdio.h>
#include <stdlib.h>

typedef char * STRING;
#define  STR   char *


int main(void){
	STRING s1, s2;  //µÈÍ¬ÓÚ char *s1; char *s2;
	char name[] = "Martin";
	s1 =  name;
	s2 = name;

	STR  s3, s4; //  char *  s3, s4;
	s3 = name;
	s4 = name[0];

	system("pause");
    return 0;
}


