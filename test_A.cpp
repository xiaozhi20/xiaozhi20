#include <stdio.h>
#include <stdlib.h>
#include "test.h"


//����ԱA�Ĵ���


int main(void){
	struct _pos  pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	pos.w = 0;
	
	printf("kkk: %d\n", kkk);

	test_A();
	test_B();
	system("pause");
}


void test_A(){
	printf("����test_A.cpp => test_A() \n");
	{
		static int time=0;
		if(++time>5)return ;
	}
	test_B();
}